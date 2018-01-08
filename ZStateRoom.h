// ZStateRoom.h

#ifndef _ZSTATEROOM_H
#define _ZSTATEROOM_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

class ZStateRoom : public ZState
{
public:

	virtual ~ZStateRoom();

	virtual void InitState();
	virtual void UpdateState();
	virtual void StopState();

private:

	void ScanRoom();
	bool PingSonar();

private:

	MotorsClass m_motors;
	SonarClass m_sonar;

	bool m_bScanFinished;
	bool m_bScanningRoom;

};


#endif

