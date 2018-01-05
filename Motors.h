// Motors.h

#ifndef _MOTORS_H_
#define _MOTORS_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ZumoMotors.h>
#include "Constants.h"

class MotorsClass
{
protected:


public:

	void init();

	static void Turn(const int direction, int delayMs, bool carryOn);
	static void Turn90(const int direction, bool carryOn);
	static void SetMotorSpeeds(int pLeftSpeed, int pRightSpeed);
	static void SetLeftMotorSpeed(int pLeftSpeed);
	static void SetRightMotorSpeed(int pRightSpeed);

	static int GetLeftMotorSpeed() { return m_iLeftMotorSpeed; };
	static int GetRightMotorSpeed() { return m_iRightMotorSpeed; };

private:
	static void ClampMotorSpeed(int& pSpeed);

private:

	static ZumoMotors motors;


	static int m_iLeftMotorSpeed;
	static int m_iRightMotorSpeed;

};

extern class MotorsClass Motors;


#endif

