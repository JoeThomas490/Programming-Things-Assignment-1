#include "Compass.h"

CompassClass::CompassClass()
{
}

CompassClass::~CompassClass()
{
}

void CompassClass::Init()
{
	SPRINT(Try init compass..);
	m_compass.init();
	m_compass.enableDefault();
	m_compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
	m_compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ);    // 220 Hz compass update rate

	SPRINT(Compass initialised..);

}

void CompassClass::Calibrate()
{

	float runningMinX, runningMinY;
	float runningMaxX, runningMaxY;
	// To calibrate the magnetometer, the Zumo spins to find the max/min
	// magnetic vectors. This information is used to correct for offsets
	// in the magnetometer data.
	SPRINT(Calibrating compass..);

	//MotorsClass::GetMotorInstance().SetMotorSpeeds(RUN_SPEED, -RUN_SPEED);

	for (int index = 0; index < 70; index++)
	{
		// Take a reading of the magnetic vector and store it in compass.m
		m_compass.read();

		runningMinX = min(runningMinX, m_compass.m.x);
		runningMinY = min(runningMinY, m_compass.m.y);

		runningMaxX = max(runningMaxX, m_compass.m.x);
		runningMaxY = max(runningMaxY, m_compass.m.y);

		delay(50);
	}

	//MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);

	m_compass.m_max.x = runningMaxX;
	m_compass.m_max.y = runningMaxY;
	m_compass.m_min.x = runningMinX;
	m_compass.m_min.y = runningMinY;

	SPRINT(Finished calibrating compass..);

}

float CompassClass::GetAngle()
{
	return AverageHeading();
}

float CompassClass::Heading(LSM303::vector<long> v)
{
	float x_scaled = 2.0*(float)(v.x - m_compass.m_min.x) / (m_compass.m_max.x - m_compass.m_min.x) - 1.0;
	float y_scaled = 2.0*(float)(v.y - m_compass.m_min.y) / (m_compass.m_max.y - m_compass.m_min.y) - 1.0;

	float angle = atan2(y_scaled, x_scaled) * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	return angle;
}

float CompassClass::AverageHeading()
{
	LSM303::vector<long> avg = { 0, 0, 0 };

	for (int i = 0; i < 10; i++)
	{
		m_compass.read();
		avg.x += m_compass.m.x;
		avg.y += m_compass.m.y;
	}
	avg.x /= 10.0;
	avg.y /= 10.0;

	// avg is the average measure of the magnetic vector.
	return Heading(avg);
}

// Yields the angle difference in degrees between two 
float CompassClass::RelativeHeading(float mHeadingFrom, float mHeadingTo)
{
	float relativeHeading = mHeadingTo - mHeadingFrom;

	// constrain to -180 to 180 degree range
	if (relativeHeading > 180)
		relativeHeading -= 360;
	if (relativeHeading < -180)
		relativeHeading += 360;

	return relativeHeading;
}

CompassClass Compass;
