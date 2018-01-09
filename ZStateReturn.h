// ZStateReturn.h

#ifndef _ZSTATERETURN_H
#define _ZSTATERETURN_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

class ZStateReturn : public ZState
{
public:

	virtual ~ZStateReturn();

	virtual void InitState();
	virtual void UpdateState();
	virtual void StopState();

private:
	
	void CheckWallCollision();

private:

	float m_fCorridorTime;
	float m_fCurrentTime;
	float m_fStartTime;

	ReflectanceArrayClass m_reflectanceArray;
	MotorsClass m_motors;

	Corridor* m_pFromCorridor;
};


#endif

