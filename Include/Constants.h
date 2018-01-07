#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//This is the maximum speed the motors will be allowed to turn.
//(400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 250;

//Run speed is half of MAX_SPEED
const int RUN_SPEED = MAX_SPEED / 2;

//Number of sensors in the reflectance sensor array
const int NUM_SENSORS = 6;

//How often to print debug data
const int PRINT_FRAME_COUNT = 5;

namespace SONAR
{
	const int TRIGGER_PIN = 2;
	const int ECHO_PIN = 6;
	const int MAX_DISTANCE = 100;
}

#endif
