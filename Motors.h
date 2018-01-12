#ifndef _MOTORS_H_
#define _MOTORS_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ZumoMotors.h>
#include "Constants.h"


//*********************************************************************************************
// File:			Motors.h
// Description:		Wrapper class for ZumoMotors. Has some helper functions for turning 90 
//					degrees and stores current speeds of both motors.
// Notes:			
// Todo:			
//*********************************************************************************************

class MotorsClass
{
protected:


public:

	//Function to turn the robot by a slight amount
	//Parameters:
	//1. Direction in which to turn (-1 for left, 1 for right)
	//2. Delay to add for turn (how long to turn for)
	//3. Whether to carry on forward after turn or not
	void Turn(const int direction, int delayMs, bool carryOn);

	//Function to turn the robot by 90 degrees
	//Parameters:
	//1. Direction in which to turn (-1 for left, 1 for right)
	//2. Whether to carry on forward after turn or not
	void Turn90(const int direction, bool carryOn);

	//Set both motor speeds and clamp between max/min speed
	//Parameters:
	//1. Speed to set left motor
	//2. Speed to set right motor
	void SetMotorSpeeds(int pLeftSpeed, int pRightSpeed);

	//Set left motor independantly
	//Parameters:
	//1. Speed to set left motor
	void SetLeftMotorSpeed(int pLeftSpeed);

	//Set right motor independantly
	//Parameters:
	//1. Speed to set right motor
	void SetRightMotorSpeed(int pRightSpeed);

	//Get the current speed of the left motor
	//Return:
	//Integer of left motor speed
	static int GetLeftMotorSpeed() { return m_iLeftMotorSpeed; };

	//Get the current speed of the right motor
	//Return:
	//Integer of right motor speed
	static int GetRightMotorSpeed() { return m_iRightMotorSpeed; };

private:
	
	//Clamps the motor speed between it's minimum and maximum value
	//Parameters:
	//1. Speed to be clamped
	static void ClampMotorSpeed(int& pSpeed);

private:

	static ZumoMotors motors;

	static int m_iLeftMotorSpeed;
	static int m_iRightMotorSpeed;

};

extern class MotorsClass Motors;


#endif

