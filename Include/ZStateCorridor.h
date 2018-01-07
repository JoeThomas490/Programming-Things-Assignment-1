// ZStateCorridor.h

#ifndef _ZSTATECORRIDOR_H
#define _ZSTATECORRIDOR_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

class ZStateCorridor : public ZState
{
 protected:


public:
	virtual ~ZStateCorridor();

	virtual void InitState();
	virtual void UpdateState();
	virtual void StopState();


private:
	
	ReflectanceArrayClass m_reflectanceArray;
	MotorsClass m_motors;
};

#endif

