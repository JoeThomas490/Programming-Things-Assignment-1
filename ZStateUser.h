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

class ZStateUser : public ZState
{
public:

	ZStateUser();
	virtual ~ZStateUser();

	virtual void InitState();
	virtual void UpdateState();

	virtual void StopState();

private:

	void CheckMovementInput();
	void CheckStateChangeInput();
	void CheckDirectionInput();

private:

	bool m_bWaitForDirection;

};

#endif

