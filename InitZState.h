// InitZState.h

#ifndef _INITZSTATE_h
#define _INITZSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

class InitZState : public ZState
{
public:

	InitZState();
	virtual ~InitZState();

	virtual void InitState();
	virtual void UpdateState();

	virtual void StopState();

};


#endif

