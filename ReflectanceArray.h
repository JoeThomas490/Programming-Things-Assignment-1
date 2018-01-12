#ifndef _REFLECTANCEARRAY_H_
#define _REFLECTANCEARRAY_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ZumoReflectanceSensorArray.h>

#include "Constants.h"
#include "HelperMacros.h"

#include "Motors.h"


//*********************************************************************************************
// File:			ReflectanceArray.h
// Description:		Class to hold all data to do with the building the robot is currently in
//					such as corridors (with their lengths in time) and all rooms associated
//					with that corridor.
// Notes:			
// Todo:			
//*********************************************************************************************


//Struct to hold relevant data to do with reflectance array "collision"
struct ReflectanceData
{
	//Whether the reflectance array has detected a "hit"
	bool m_bHit;
	//Direction in which the "collision" is
	int m_iDirection;
	//How many sensors have been hit
	int m_iSensorsHit;

	ReflectanceData() : m_bHit(false), m_iDirection(0), m_iSensorsHit(0)
	{
	}
};

class ReflectanceArrayClass
{
public:

	~ReflectanceArrayClass();

	//Initialises the reflectance array object
	void Init();

	//Starts the calibration process for the reflectance array.
	//Spins around getting data from array for 2 seconds
	void Calibrate();

	//Main function to get reflectance array collision data
	//Returns:
	//ReflectanceData structure holding relevant collision data
	ReflectanceData HandleReflectanceArray();

private:

	//Reflectance sensor array
	ZumoReflectanceSensorArray m_reflectanceSensors;
	//Values assigned to by reflectance array object
	unsigned int m_aSensorArray[NUM_SENSORS];

private:

	//Function to populate the sensor array with new values (called every frame)
	void ReadSensorData();

	//Debug function to display the data gathered by the reflectance array
	void DisplayArrayData();

public:

	//Static function to get a reference to the current reflectance
	//array instance as this is a singleton class.
	//Returns:
	//Reference to current reflectance array instance
	static ReflectanceArrayClass& GetReflectanceArrayInstance()
	{
		//Create a new static pointer of the ReflectanceArrayClass
		//(Only one will be created as it's a static pointer)
		static ReflectanceArrayClass* instance = new ReflectanceArrayClass();
		
		//Return dereferenced pointer
		return *instance;
	}

};

extern ReflectanceArrayClass ReflectanceArray;

#endif

