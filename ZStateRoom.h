#ifndef _ZSTATEROOM_H_
#define _ZSTATEROOM_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

//*********************************************************************************************
// File:			ZStateRoom.h
// Description:		State to control the room scanning behaviour
// Notes:			
// Todo:			
//*********************************************************************************************


class ZStateRoom : public ZState
{
public:

	ZStateRoom();
	virtual ~ZStateRoom();

	//Virtual function for initialising state
	virtual void InitState();
	//Virtual function for updating state (tick)
	virtual void UpdateState();
	//Virtual function for stopping state
	virtual void StopState();

private:

	//Function to be called to trigger a scan
	void ScanRoom();
	
	//Function to handle calling of sonar ping
	//Returns:
	//Whether the ping hit or not
	bool PingSonar();

private:

	//Reference to motors class
	MotorsClass m_motors;
	//Reference to sonar calss
	SonarClass m_sonar;

	//Whether the scan has been finished
	bool m_bScanFinished;
	//Whether the room is currently being scanned
	bool m_bScanningRoom;
};


#endif

