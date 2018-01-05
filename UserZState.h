// UserZState.h

#ifndef _USERZSTATE_h
#define _USERZSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "ZState.h"

#include "Motors.h"

class UserZState : public ZState
{
public:

	UserZState();
	virtual ~UserZState();

	virtual void InitState();
	virtual void UpdateState();

	virtual void StopState();

};

#endif

