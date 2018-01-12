#ifndef _ZSTATE_H_
#define _ZSTATE_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"	
#include "HelperMacros.h"

#include "InputManager.h"	
#include "Motors.h"
#include "ReflectanceArray.h"
#include "Sonar.h"
#include "Compass.h"

#include "BuildingData.h"

//*********************************************************************************************
// File:			ZState.h
// Description:		Purely abstract class that all states inherit from. Contains purely virtual
//					functions for initialising, updating and shutting down of states.
// Notes:			
// Todo:			
//*********************************************************************************************

class ZState
{
public:

	//Enum to contain all the different states
	enum ZUMO_STATES
	{
		INIT,
		USER,
		CORRIDOR,
		ROOM,
		RETURN,
		JUNTION,
	};

	ZState();
	virtual ~ZState();

	//Purely virtual function for initialising state
	virtual void InitState() = 0;
	//Purely virtual function for updating state (tick)
	virtual void UpdateState() = 0;
	//Purely virtual function for stopping state
	virtual void StopState() = 0;

	//Set the state number (used when changing states) 
	void SetStateNumber(int mStateNum) { m_iStateNumber = mStateNum; };
	//Get the number associated with this state
	//Returns:
	//ID of state
	int GetStateNumber() const { return m_iStateNumber; };

	//Get whether the state has finished or not
	//Returns:
	//If the state has finished
	bool GetIsStateFinished() const { return m_bStateFinished; };

	//Get the state that is connected to this one (used for switching states)
	//Returns:
	//Enum of which state to move onto next
	ZUMO_STATES GetNextState() { return m_eNextState; };

	//Set the building data pointer so each state can read/write the building data
	//Parameters:
	//1. Pointer to the building data object
	void SetBuildingDataPtr(BuildingData* mData) { m_pBuildingData = mData; };

protected:

	//ID of state
	unsigned int m_iStateNumber = -1;

	//Whether the state has finished or not
	bool m_bStateFinished = false;

	//State that will be moved onto once this state has finished
	ZUMO_STATES m_eNextState;

	//Pointer to the building data object
	BuildingData* m_pBuildingData;

};


#endif

