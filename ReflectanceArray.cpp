#include "ReflectanceArray.h"

ReflectanceArrayClass::~ReflectanceArrayClass()
{
}

//Initialises the reflectance array object
void ReflectanceArrayClass::Init()
{
	m_reflectanceSensors.init();

	//Set all members in sensorArray to 0
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		m_aSensorArray[i] = 0;
	}
}

//Starts the calibration process for the reflectance array.
//Spins around getting data from array for 2 seconds
void ReflectanceArrayClass::Calibrate()
{
	// Wait 1 second and then begin automatic sensor calibration
	// by rotating in place to sweep the sensors over the line
	delay(1000);

	//Turn the LED on pin 13 on
	digitalWrite(13, HIGH);

	MotorsClass motors;

	//SPRINT(Calibrating Reflectance Array...);
	int i;
	for (i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			motors.SetMotorSpeeds(-SCAN_SPEED, SCAN_SPEED);
		else
			motors.SetMotorSpeeds(SCAN_SPEED, -SCAN_SPEED);
		m_reflectanceSensors.calibrate();

		// Since our counter runs to 80, the total delay will be
		// 80*20 = 1600 ms.
		delay(20);
	}

	// Turn off LED to indicate we are through with calibration
	digitalWrite(13, LOW);

	//Set motors to not move
	motors.SetMotorSpeeds(0, 0);

	//SPRINT(Finished calibrating...);
}

//Main function to get reflectance array collision data
//Returns:
//ReflectanceData structure holding relevant collision data
ReflectanceData ReflectanceArrayClass::HandleReflectanceArray()
{
	//Collect new sensor data
	ReadSensorData();

	//Create a new reflectance data object
	ReflectanceData hitData;

	//Check to see if we've hit a wall
	int wallHitCounter = 0;
	//Loop through all the sensors
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		//If they have a slight bit of darkness we will count that as a hit
		if (m_aSensorArray[i] > 100)
		{
			//Increment counter
			wallHitCounter++;
		}
	}

	//If all the sensors bar 1 have been hit then stop
	if (wallHitCounter == NUM_SENSORS / 2)
	{
		//We've hit a wall
		//Stop moving and tell user
		//MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
#if PRINT_WALL_HIT_DATA
		SPRINT(Wall hit!);
#endif
		//Switch to USER state
		//m_eZumoState = ZState::ZUMO_STATES::USER;

		hitData.m_bHit = true;
		hitData.m_iDirection = 0;
		hitData.m_iSensorsHit = wallHitCounter;

		return hitData;
	}

	//If we detect darkness on the left two sensors then turn right
	//Need to make these values variables for easier calibration
	//Maybe use calibrated sensor value instead?

	if (m_aSensorArray[0] > 300 || m_aSensorArray[1] > 150)
	{
		//Turn right away from wall
#if PRINT_WALL_HIT_DATA
		SPRINT(Wall hit on left!);
#endif

		hitData.m_bHit = true;
		hitData.m_iDirection = -1;
		hitData.m_iSensorsHit = 1;
		//m_gMotors.Turn(1, 50, true);

		return hitData;
	}
	//If we detect darkness on the right two sensors then turn left
	else if (m_aSensorArray[NUM_SENSORS - 1] > 300 || m_aSensorArray[NUM_SENSORS - 2] > 150)
	{
		//Turn left away from wall
#if PRINT_WALL_HIT_DATA
		SPRINT(Wall hit on right!);
#endif

		hitData.m_bHit = true;
		hitData.m_iDirection = 1;
		hitData.m_iSensorsHit = 1;

		return hitData;
		//m_gMotors.Turn(-1, 50, true);
	}

	return hitData;
}

//Function to populate the sensor array with new values (called every frame)
void ReflectanceArrayClass::ReadSensorData()
{
	//Get new data from reflectance sensors and put in array
	m_reflectanceSensors.readLine(m_aSensorArray);

#if PRINT_ARRAY_DATA
	DisplayArrayData();
#endif
}

//Debug function to display the data gathered by the reflectance array
void ReflectanceArrayClass::DisplayArrayData()
{
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		Serial.print(m_aSensorArray[i]);
		Serial.print("\t");
	}
	Serial.print("\n");
}

ReflectanceArrayClass ReflectanceArray;

