#ifndef _USERZSTATE_H_
#define _USERZSTATE_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "ZState.h"

#include "Motors.h"


//*********************************************************************************************
// File:			ZStateUser.h
// Description:		State in which user has complete control of robot
// Notes:			
// Todo:			
//*********************************************************************************************


class ZStateUser : public ZState
{
public:

	ZStateUser();
	virtual ~ZStateUser();

	//Virtual function for initialising state
	virtual void InitState();
	//Virtual function for updating state (tick)
	virtual void UpdateState();
	//Virtual function for stopping state
	virtual void StopState();

private:

	//Check key input to do with robot movement
	void CheckMovementInput();
	//Check key input to do with state changes
	void CheckStateChangeInput();
	//Check key input to do with directional state change
	void CheckDirectionInput();

private:

	//Whether the state is waiting for direction
	//when changing states
	bool m_bWaitForDirection;

	//Reference to our motor class
	MotorsClass m_motors;
};

#endif

