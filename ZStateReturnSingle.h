#ifndef _ZSTATERETURNSINGLE_H_
#define _ZSTATERETURNSINGLE_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

//*********************************************************************************************
// File:			ZStateReturnSingle.h
// Description:		State to return the robot back up a single corridor and turn the next way
// Notes:			
// Todo:			
//*********************************************************************************************

class ZStateReturnSingle : public ZState
{
public:

	ZStateReturnSingle();
	virtual ~ZStateReturnSingle();

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

private:

	//Length (in ms) of the current corridor
	float m_fCorridorTime;
	//Current length of time moved (in ms) 
	float m_fCurrentTime;
	//Time in which corridor movement started (in ms)
	float m_fStartTime;

	//Reference to our reflectance array class
	ReflectanceArrayClass m_reflectanceArray;

	//Reference to our motors class
	MotorsClass m_motors;

	//Pointer to the corridor we're moving through
	Corridor* m_pCorridor;
};


#endif

