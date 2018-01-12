#ifndef _ZSTATEINIT_H_
#define _ZSTATEINIT_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

//*********************************************************************************************
// File:			ZStateInit.h
// Description:		State to handle the intialisation of all components e.g reflectance array
//					calibration etc..
// Notes:			
// Todo:			
//*********************************************************************************************

class ZStateInit : public ZState
{
public:

	ZStateInit();
	virtual ~ZStateInit();

	//Virtual function for initialising state
	virtual void InitState();
	//Virtual function for updating state (tick)
	virtual void UpdateState();
	//Virtual function for stopping state
	virtual void StopState();

};


#endif

