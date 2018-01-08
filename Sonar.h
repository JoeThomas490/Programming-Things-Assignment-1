// Sonar.h

#ifndef _SONAR_h
#define _SONAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NewPing.h>

#include "HelperMacros.h"
#include "Constants.h"

class SonarClass
{
public:

	SonarClass();

	float PingCm();

private:

	NewPing m_sonarSensor;
};

extern SonarClass Sonar;

#endif

