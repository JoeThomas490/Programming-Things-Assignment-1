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

	void Turn(const int direction, int delayMs, bool carryOn);
	void Turn90(const int direction, bool carryOn);
	void SetMotorSpeeds(int pLeftSpeed, int pRightSpeed);
	void SetLeftMotorSpeed(int pLeftSpeed);
	void SetRightMotorSpeed(int pRightSpeed);

	int GetLeftMotorSpeed() { return m_iLeftMotorSpeed; };
	int GetRightMotorSpeed() { return m_iRightMotorSpeed; };



private:
	void ClampMotorSpeed(int& pSpeed);



private:

	ZumoMotors motors;


	int m_iLeftMotorSpeed = 0;
	int m_iRightMotorSpeed = 0;

};

extern class MotorsClass Motors;


#endif

