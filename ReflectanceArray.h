// ReflectanceArray.h

#ifndef _REFLECTANCEARRAY_h
#define _REFLECTANCEARRAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ZumoReflectanceSensorArray.h>

#include "Constants.h"
#include "HelperMacros.h"

#include "Motors.h"

struct ReflectanceData
{
	bool hit;
	int direction;

	int sensorsHit;

	ReflectanceData()
	{
		hit = false;
		direction = 0;
		sensorsHit = 0;
	}
};

class ReflectanceArrayClass
{
 public:


	 static ReflectanceArrayClass& GetMotorInstance()
	 {
		 static ReflectanceArrayClass* instance = new ReflectanceArrayClass();

		 return *instance;
	 }

	 ~ReflectanceArrayClass();

	void Init();
	void Calibrate();

	ReflectanceData HandleReflectanceArray();

private:

	ZumoReflectanceSensorArray reflectanceSensors;

	unsigned int m_aSensorArray[NUM_SENSORS];

private:

	void ReadSensorData();

};

extern ReflectanceArrayClass ReflectanceArray;

#endif

