// ZStateCorridor.h

#ifndef _ZSTATECORRIDOR_h
#define _ZSTATECORRIDOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"
#include "Motors.h"

class ZStateCorridorClass : public ZState
{
 protected:


public:
	virtual ~ZStateCorridorClass();

	virtual void InitState();
	virtual void UpdateState();
	virtual void StopState();
};

extern ZStateCorridorClass ZStateCorridor;

#endif

