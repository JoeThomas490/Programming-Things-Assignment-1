#include "ZStateRoom.h"

ZStateRoom::~ZStateRoom()
{
}

void ZStateRoom::InitState()
{
	m_motors = MotorsClass::GetMotorInstance();

	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	delay(75);

	m_motors.SetMotorSpeeds(0, 0);

	m_bScanFinished = false;
	m_bScanningRoom = false;

	m_bStateFinished = false;
}

void ZStateRoom::UpdateState()
{
	if (m_bScanningRoom == false)
	{
		ScanRoom();
	}
	
	if (m_bScanFinished == true)
	{
		m_eNextState = ZUMO_STATES::USER;
		m_bStateFinished = true;
	}
}

void ZStateRoom::StopState()
{
}

void ZStateRoom::ScanRoom()
{
	// Wait 1 second and then begin automatic sensor calibration
	// by rotating in place to sweep the sensors over the line
	delay(1000);

	digitalWrite(13, HIGH);

	SPRINT(Scanning room....);
	m_bScanningRoom = true;

	int i;
	for (i = 0; i < 100; i++)
	{
		if ((i > 20 && i <= 40) || (i > 60 && i <= 80))
			m_motors.SetMotorSpeeds(-SCAN_SPEED, SCAN_SPEED);
		else
			m_motors.SetMotorSpeeds(SCAN_SPEED, -SCAN_SPEED);

		// Since our counter runs to 80, the total delay will be
		// 80*30 = 2400ms
		delay(30);
	}

	// Turn off LED to indicate we are through with calibration
	digitalWrite(13, LOW);

	//Set motors to not move
	m_motors.SetMotorSpeeds(0, 0);

	SPRINT(Finished scanning...);

	m_motors.SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);

	delay(75);

	m_motors.SetMotorSpeeds(0, 0);

	m_bScanFinished = true;

}
