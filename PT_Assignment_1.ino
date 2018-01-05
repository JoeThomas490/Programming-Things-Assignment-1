#include "Motors.h"
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#include "HelperMacros.h"
#include "Constants.h"

MotorsClass m_gMotors;
ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
Pushbutton button(ZUMO_BUTTON);

bool runMotors = true;
bool runReflectanceArray = true;


int printCounter = 0;

unsigned int sensorArray[NUM_SENSORS];


//Different behaviour states for robot
enum ZUMO_STATES
{
	INIT,
	USER,
	CORRIDOR,
	ROOM,
	JUNTION,
	RETURN
};

ZUMO_STATES m_eZumoState;


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									ARDUINO FUNCTIONS													//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
	//Initialise sensor array to 0
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		sensorArray[i] = 0;
	}

	//Set start state as init state
	m_eZumoState = INIT;

	//Begin Serial communication
	Serial.begin(9600);

	// Play a little welcome song
	buzzer.play(">g32>>c32");

	// Initialize the reflectance sensors module
	reflectanceSensors.init();

	// Wait for the user button to be pressed and released
	button.waitForButton();

	// Turn on LED to indicate we are in calibration mode
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);

	// Wait 1 second and then begin automatic sensor calibration
	// by rotating in place to sweep the sensors over the line
	delay(1000);
	SPRINT("Calibrating Reflectance Array...");
	int i;
	for (i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			m_gMotors.SetMotorSpeeds(-200, 200);
		else
			m_gMotors.SetMotorSpeeds(200, -200);
		reflectanceSensors.calibrate();

		// Since our counter runs to 80, the total delay will be
		// 80*20 = 1600 ms.
		delay(20);
	}
	m_gMotors.SetMotorSpeeds(0, 0);

	// Turn off LED to indicate we are through with calibration
	digitalWrite(13, LOW);

	// Play music and wait for it to finish before we start driving.
	buzzer.play("L16 cdegreg4");

	//Write a message to the console
	SPRINT("Ready to start...");
	SPRINT("Press P to begin");

	runMotors = false;
	printCounter = 0;
}

//Main Loop
void loop()
{
	if (runMotors == true)
	{
		switch (m_eZumoState)
		{
		case INIT:
			m_gMotors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
			m_eZumoState = CORRIDOR;

#if PRINT_STATE_CHANGES
			SPRINT("Changing to CORRIDOR state");
#endif
			break;
		case USER:
			//Read input from user through Serial connection (xBee)
			ReadInput();
			break;
		case CORRIDOR:
			//Read input from user through Serial connection (xBee)
			ReadInput();

			//If the reflectance array is allowed to run
			if (runReflectanceArray)
			{
				HandleReflectanceArray();
			}
			break;
		}
	}
	else
	{
		m_gMotors.SetMotorSpeeds(0, 0);
		ReadStartStopInput();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									REFLECTANCE ARRAY													//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void HandleReflectanceArray()
{
	//Get new data from reflectance sensors and put in array
	reflectanceSensors.readLine(sensorArray);

#if PRINT_ARRAY_DATA
	DisplayArrayData();
#endif

	//Check to see if we've hit a wall
	int wallHitCounter = 0;
	//Loop through all the sensors
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		//If they have a slight bit of darkness we will count that as a hit
		if (sensorArray[i] > 100)
		{
			//Increment counter
			wallHitCounter++;
		}
	}

	//If all the sensors bar 1 have been hit then stop
	if (wallHitCounter == NUM_SENSORS - 2)
	{
		//We've hit a wall
		//Stop moving and tell user
		m_gMotors.SetMotorSpeeds(0, 0);
		SPRINT("Wall hit!");

		//Switch to USER state
		m_eZumoState = ZUMO_STATES::USER;

		return;
	}

	//If we detect darkness on the left two sensors then turn right
	//Need to make these values variables for easier calibration
	//Maybe use calibrated sensor value instead?

	if (sensorArray[0] > 900 || sensorArray[1] > 900)
	{
		//Turn right away from wall
#if PRINT_WALL_HIT_DATA
		SPRINT("Wall hit on left!");
#endif
		m_gMotors.Turn(1, 50, true);
	}
	//If we detect darkness on the right two sensors then turn left
	else if (sensorArray[NUM_SENSORS-1] > 900 || sensorArray[NUM_SENSORS - 2] > 900)
	{
		//Turn left away from wall
#if PRINT_WALL_HIT_DATA
		SPRINT("Wall hit on right!");
#endif
		m_gMotors.Turn(-1, 50, true);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									INPUT																//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReadInput()
{
	if (Serial.available() > 0)
	{
		int input = Serial.read();
		switch (tolower(input))
		{
		case 'w':
			m_gMotors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
			break;
		case 's':
			if (m_gMotors.GetLeftMotorSpeed() != 0 && m_gMotors.GetRightMotorSpeed()	 != 0)
			{
				m_gMotors.SetMotorSpeeds(0, 0);
			}
			else
			{
				m_gMotors.SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
			}
			break;

		case 'a':
			m_gMotors.Turn(-1, 50, false);
			break;
		case 'd':
			m_gMotors.Turn(1, 50, false);
			break;
		case 'c':
#if PRINT_STATE_CHANGES
			SPRINT("Changing to CORRIDOR state");
#endif
			m_eZumoState = ZUMO_STATES::CORRIDOR;
			runReflectanceArray = true;
			m_gMotors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
			delay(100);
			break;
		case 'u':
#if PRINT_STATE_CHANGES
			SPRINT("Changing to USER state");
#endif
			m_eZumoState = ZUMO_STATES::USER;
			m_gMotors.SetMotorSpeeds(0, 0);
			delay(100);
			break;

		case '1':
			runMotors = !runMotors;
			break;
		case '2':
			runReflectanceArray = !runReflectanceArray;
			break;

		case 'r':
			if (m_eZumoState == ZUMO_STATES::USER)
			{
				m_eZumoState = ZUMO_STATES::ROOM;
			}
			break;
		case 'o':
			if (m_eZumoState == ZUMO_STATES::USER)
			{
				m_eZumoState = ZUMO_STATES::CORRIDOR;
			}

		default:
			break;
		}
	}
}

void ReadStartStopInput()
{
	if (Serial.available() > 0)
	{
		int input = Serial.read();
		switch (input)
		{
		case 'p':
		case 'P':
			runMotors = !runMotors;
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									MOTOR FUNCTIONS														//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									DEBUG HELPERS														//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//Print out the sensor array data all in one line with tabs in between
void DisplayArrayData()
{
	printCounter++;

	if (printCounter > PRINT_FRAME_COUNT)
	{
		printCounter = 0;
	}
	else
	{
		return;
	}

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		Serial.print(sensorArray[i]);
		Serial.print("\t");
	}
	Serial.print("\n");
}
