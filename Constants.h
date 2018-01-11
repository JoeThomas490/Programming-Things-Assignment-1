#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//This is the maximum speed the motors will be allowed to turn.
//(400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 220;

//Run speed is half of MAX_SPEED
const int RUN_SPEED = MAX_SPEED / 2;

//Speed in which to rotate in a scan
const int SCAN_SPEED = 180;

const int NINETY_DEGREE_TIME = 315;

//Number of sensors in the reflectance sensor array
const int NUM_SENSORS = 6;

//How often to print debug data
const int PRINT_FRAME_COUNT = 5;

//Maximum number of different states in list
const int MAX_STATES = 5;

//Maximum number of corridors allowed in building data
const int MAX_CORRIDORS = 10;

//Maximum number of rooms allowed for each corridor
const int MAX_ROOMS = 2;

namespace SONAR
{
	//Pin attached to trigger on U/S sensor
	const int TRIGGER_PIN = 2;
	//Pin attached to echo on U/S sensor
	const int ECHO_PIN = 6;
	//Max distance for U/S to scan
	const int MAX_DISTANCE_CM = 40;
}

#endif
