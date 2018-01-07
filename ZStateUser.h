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


	//Handle any input to do with movement
	void CheckMovementInput();
	//Handle any input to do with changing state
	void CheckNextStateInput();
	//Handle any input to do with detecting direction of next state
	void CheckDirectionInput();

	//Triggered when a room or corridor has been identified
	//and waits for a direction to move onto next state
	bool m_bWaitingForDirection = true;

};

#endif

