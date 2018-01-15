#ifndef _COMPASS_H_
#define _COMPASS_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <LSM303.h>

#include "Constants.h"
#include "HelperMacros.h"
#include "Motors.h"

class CompassClass
{
public:

	static CompassClass& GetCompassInstance()
	{
		static CompassClass* instance = new CompassClass();

		return *instance;
	}

	CompassClass();
	~CompassClass();

	void Init();
	void Calibrate();

	float GetAngle();

private:

	// Converts x and y components of a vector to a heading in degrees.
	// This function is used instead of LSM303::heading() because we don't
	// want the acceleration of the Zumo to factor spuriously into the
	// tilt compensation that LSM303::heading() performs. This calculation
	// assumes that the Zumo is always level.
	float Heading(LSM303::vector<long> v);

	float AverageHeading();
	float RelativeHeading(float mHeadingFrom, float mHeadingTo);

private:

	LSM303 m_compass;

};

extern CompassClass Compass;

#endif