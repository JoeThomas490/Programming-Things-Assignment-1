#include "../Motors.h"

int MotorsClass::m_iLeftMotorSpeed;
int MotorsClass::m_iRightMotorSpeed;

//A function to handle turning the Zumo left or right
//Parameters : 
//1.Pass it -1 for left, 1 for right. 
//2.How long to turn for. 
//3.Whether to carry on straight after turn.
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

//A function to handle turning the Zumo left or right 90 degrees
//Parameters : 
//1.Pass it -1 for left, 1 for right. 
//3.Whether to carry on straight after turn.
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

	delay(300);

	if (carryOn)
	{
		SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	}
	else
	{
		SetMotorSpeeds(0, 0);
	}
}

//Function to set speeds of both motors independantly
//Parameters :
//1.Left motor speed
//2.Right motor speed
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

//Function to set left motor speed only
//Parameters: 
//1.Left motor speed
void MotorsClass::SetLeftMotorSpeed(int pLeftSpeed)
{
	ClampMotorSpeed(pLeftSpeed);

	motors.setSpeeds(pLeftSpeed, m_iRightMotorSpeed);
	m_iLeftMotorSpeed = pLeftSpeed;
}

//Function to set right motor speed only
//Parameters: 
//2.Right motor speed
void  MotorsClass::SetRightMotorSpeed(int pRightSpeed)
{
	ClampMotorSpeed(pRightSpeed);

	motors.setSpeeds(m_iLeftMotorSpeed, pRightSpeed);
	m_iRightMotorSpeed = pRightSpeed;
}

//Function to clamp any motor speed between it's maximum value (MAX_SPEED)
//Paramaters : Reference to speed being clamped
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

