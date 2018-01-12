#include "Motors.h"

int MotorsClass::m_iLeftMotorSpeed;
int MotorsClass::m_iRightMotorSpeed;

//Function to turn the robot by a slight amount
//Parameters:
//1. Direction in which to turn (-1 for left, 1 for right)
//2. Delay to add for turn (how long to turn for)
//3. Whether to carry on forward after turn or not
void MotorsClass::Turn(const int direction, int delayMs, bool carryOn)
{

	switch (direction)
	{
	case -1:
		SetMotorSpeeds(-MAX_SPEED, MAX_SPEED);
		break;

	case 1:
		SetMotorSpeeds(MAX_SPEED, -MAX_SPEED);
		break;
	}

	delay(delayMs);

	if (carryOn)
	{
		SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	}
	else
	{
		SetMotorSpeeds(0, 0);
	}
}

//Function to turn the robot by 90 degrees
//Parameters:
//1. Direction in which to turn (-1 for left, 1 for right)
//2. Whether to carry on forward after turn or not
void  MotorsClass::Turn90(const int direction, bool carryOn)
{
	switch (direction)
	{
	case -1:
		SetMotorSpeeds(-MAX_SPEED, MAX_SPEED);
		break;

	case 1:
		SetMotorSpeeds(MAX_SPEED, -MAX_SPEED);
		break;
	}

	delay(NINETY_DEGREE_TIME);

	if (carryOn)
	{
		SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	}
	else
	{
		SetMotorSpeeds(0, 0);
	}
}

//Set both motor speeds and clamp between max/min speed
//Parameters:
//1. Speed to set left motor
//2. Speed to set right motor
void  MotorsClass::SetMotorSpeeds(int pLeftSpeed, int pRightSpeed)
{
	ClampMotorSpeed(pLeftSpeed);
	ClampMotorSpeed(pRightSpeed);

#if PRINT_MOTOR_SPEED
	SPRINT(Changing motor speeds to : );
	Serial.print(pLeftSpeed);
	Serial.print("\t");
	Serial.print(pRightSpeed);
#endif

	motors.setSpeeds(pLeftSpeed, pRightSpeed);
	m_iLeftMotorSpeed = pLeftSpeed;
	m_iRightMotorSpeed = pRightSpeed;
}

//Set left motor independantly
//Parameters:
//1. Speed to set left motor
void MotorsClass::SetLeftMotorSpeed(int pLeftSpeed)
{
	ClampMotorSpeed(pLeftSpeed);

	motors.setSpeeds(pLeftSpeed, m_iRightMotorSpeed);
	m_iLeftMotorSpeed = pLeftSpeed;
}

//Set right motor independantly
//Parameters:
//1. Speed to set right motor
void  MotorsClass::SetRightMotorSpeed(int pRightSpeed)
{
	ClampMotorSpeed(pRightSpeed);

	motors.setSpeeds(m_iLeftMotorSpeed, pRightSpeed);
	m_iRightMotorSpeed = pRightSpeed;
}

//Clamps the motor speed between it's minimum and maximum value
//Parameters:
//1. Speed to be clamped
void  MotorsClass::ClampMotorSpeed(int& pSpeed)
{
	if (pSpeed > MAX_SPEED)
	{
		pSpeed = MAX_SPEED;
	}
	else if (pSpeed < -MAX_SPEED)
	{
		pSpeed = -MAX_SPEED;
	}
}

MotorsClass Motors;

