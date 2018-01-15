#ifndef _ZSTATECORRIDOR_H_
#define _ZSTATECORRIDOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

//*********************************************************************************************
// File:			ZStateCorridor.h
// Description:		State for controlling the robot down a corridor. Completely autononmous and
//					will only stop and move onto the USER state once it has hit a wall. Also adds
//					to the building data object by calculating how long a corridor is.
// Notes:			
// Todo:			
//*********************************************************************************************

class ZStateCorridor : public ZState
{
public:
	ZStateCorridor();
	virtual ~ZStateCorridor();

	//Virtual function for initialising state
	virtual void InitState();
	//Virtual function for updating state (tick)
	virtual void UpdateState();
	//Virtual function for stopping state
	virtual void StopState();


private:

	//Uses the reflectance array to check any wall collision
	//and moves out the way
	void CheckWallCollision();

	//Checks for certain key input
	void CheckUserInput();

	//Checks for player input to change states
	void CheckStateChangeInput();

	//Calculates the time in which it took to traverse a
	//corridor
	void CalculateCorridorLength();
private:

	//Reference to our reflectance array class
	ReflectanceArrayClass m_reflectanceArray;
	//Reference to our motors class
	MotorsClass m_motors;

	//Starting and finish times for traversing corridor
	//(Used for building data)
	float m_fStartTime, m_fFinishTime;

	//Trigger to make state wait for state change user input
	bool m_bWaitForStateChange;

};

#endif

