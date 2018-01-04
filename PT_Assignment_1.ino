/*
* Demo line-following code for the Pololu Zumo Robot
*
* This code will follow a black line on a white background, using a
* PID-based algorithm.  It works decently on courses with smooth, 6"
* radius curves and has been tested with Zumos using 30:1 HP and
* 75:1 HP motors.  Modifications might be required for it to work
* well on different courses or with different motors.
*
* http://www.pololu.com/catalog/product/2506
* http://www.pololu.com
* http://forum.pololu.com
*/

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#include "HelperMacros.h"
#include "Constants.h"


ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);



bool runMotors = true;

bool runReflectanceArray = true;

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

int printCounter = 0;

unsigned int sensorArray[NUM_SENSORS];

enum ZUMO_STATES
{
	INIT,
	CORRIDOR,
	ROOM,
	JUNTION,
	RETURN
};

ZUMO_STATES m_eZumoState;

void setup()
{
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
	int i;
	for (i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			motors.setSpeeds(-200, 200);
		else
			motors.setSpeeds(200, -200);
		reflectanceSensors.calibrate();

		// Since our counter runs to 80, the total delay will be
		// 80*20 = 1600 ms.
		delay(20);
	}
	motors.setSpeeds(0, 0);

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

		//Read input from user through Serial connection
		ReadInput();

		switch (m_eZumoState)
		{
		case INIT:
			SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
			m_eZumoState = CORRIDOR;
			SPRINT("Changing to CORRIDOR state");
			break;
		case CORRIDOR:
			if (runReflectanceArray)
			{
				handleReflectanceArray();
			}
			break;
		}
	}
	else
	{
		SetMotorSpeeds(0, 0);
		ReadStartStopInput();
	}		
}

void handleReflectanceArray()
{
	//Get new data from reflectance sensors and put in array
	reflectanceSensors.readLine(sensorArray);

#if DEBUG
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
	if (wallHitCounter == NUM_SENSORS - 1)
	{
		//We've hit a wall
		runReflectanceArray = false;
		motors.setSpeeds(0, 0);
		SPRINT("Wall hit!");

		return;
	}

	//If we detect darkness on the left two sensors then turn right
	//Need to make these values variables for easier calibration
	//Maybe use calibrated sensor value instead?

	if (sensorArray[0] > 900 || sensorArray[1] > 900)
	{
		//Turn right away from wall
		SPRINT("Wall hit on left, turning right!");
		Turn(1, 50, true);
	}
	//If we detect darkness on the right two sensors then turn left
	else if (sensorArray[NUM_SENSORS] > 900 || sensorArray[NUM_SENSORS - 1] > 900)
	{
		//Turn left away from wall
		SPRINT("Wall hit on right, turning left!");
		Turn(-1, 50, true);
	}
}

void ReadInput()
{
	if (Serial.available() > 0) {
		int input = Serial.read();
		switch (input)
		{
		case 'W':
		case 'w':
			SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
			break;
		case 'S':
		case 's':
			if (leftMotorSpeed != 0 && rightMotorSpeed != 0)
			{
				SetMotorSpeeds(0, 0);
			}
			else
			{
				SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
			}
			break;

		case 'A':
		case 'a':
			Turn(-1, 50, false);
			break;
		case 'D':
		case 'd':
			Turn(1, 50, false);
			break;
		case 'C':
		case 'c':
			runReflectanceArray = !runReflectanceArray;
			break;

		case 'p':
		case 'P':
			runMotors = !runMotors;
			break;

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


//A function to handle turning the Zumo left or right
//Parameters : 
//1.Pass it -1 for left, 1 for right. 
//2.How long to turn for. 
//3.Whether to carry on straight after turn.
void Turn(int direction, int delayMs, bool carryOn)
{
	switch (direction)
	{
	case -1:
		SetMotorSpeeds(-MAX_SPEED, MAX_SPEED);
		break;

	case 1:
		SetMotorSpeeds(MAX_SPEED, -MAX_SPEED);
		break;
	}


	delay(delayMs);

	if (carryOn)
	{
		SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	}
	else
	{
		SetMotorSpeeds(0, 0);
	}
}

//Function to set speeds of both motors independantly
//Parameters :
//1.Left motor speed
//2.Right motor speed
void SetMotorSpeeds(int pLeftSpeed, int pRightSpeed)
{
	ClampMotorSpeed(pLeftSpeed);
	ClampMotorSpeed(pRightSpeed);

	motors.setSpeeds(pLeftSpeed, pRightSpeed);
	leftMotorSpeed = pLeftSpeed;
	rightMotorSpeed = pRightSpeed;
}

//Function to set left motor speed only
//Parameters: 
//1.Left motor speed
void SetLeftMotorSpeed(int pLeftSpeed)
{
	ClampMotorSpeed(pLeftSpeed);

	motors.setSpeeds(pLeftSpeed, rightMotorSpeed);
	leftMotorSpeed = pLeftSpeed;
}

//Function to set right motor speed only
//Parameters: 
//2.Right motor speed
void SetRightMotorSpeed(int pRightSpeed)
{
	ClampMotorSpeed(pRightSpeed);

	motors.setSpeeds(leftMotorSpeed, pRightSpeed);
	rightMotorSpeed = pRightSpeed;
}

//Function to clamp any motor speed between it's maximum value (MAX_SPEED)
//Paramaters : Reference to speed being clamped
void ClampMotorSpeed(int& pSpeed)
{
	if (pSpeed > MAX_SPEED)
	{
		pSpeed = MAX_SPEED;
	}
	else if (pSpeed < -MAX_SPEED)
	{
		pSpeed = -MAX_SPEED;
	}
}

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
