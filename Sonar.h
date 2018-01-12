#ifndef _SONAR_H_
#define _SONAR_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NewPing.h>

#include "HelperMacros.h"
#include "Constants.h"

//*********************************************************************************************
// File:			Sonar.h
// Description:		Class to handle any functionality to do with the Ultra-Sonic sensor on the
//					robot. 
// Notes:			
// Todo:			
//*********************************************************************************************

class SonarClass
{
public:

	//Constructor to initialise the NewPing sensor object
	SonarClass();

	//Get a ping from the sonar and return distance
	//Returns:
	//Distance of ping in CM (0 cm if no hit)
	float PingCm();

private:

	NewPing m_sonarSensor;
};

extern SonarClass Sonar;

#endif

