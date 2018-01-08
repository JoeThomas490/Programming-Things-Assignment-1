#ifndef _ZSTATE_H_
#define _ZSTATE_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"	
#include "HelperMacros.h"

#include "InputManager.h"	
#include "Motors.h"
#include "ReflectanceArray.h"
#include "Sonar.h"
#include "Compass.h"

class ZState
{
public:

	enum ZUMO_STATES
	{
		INIT,
		USER,
		CORRIDOR,
		ROOM,
		JUNTION,
		RETURN
	};

	ZState();
	virtual ~ZState();

	virtual void InitState() = 0;
	virtual void UpdateState() = 0;
	virtual void StopState() = 0;

	void SetStateNumber(int mStateNum) { m_iStateNumber = mStateNum; };
	int GetStateNumber() const { return m_iStateNumber; };

	bool GetIsStateFinished() const { return m_bStateFinished; };

	ZUMO_STATES GetNextState() { return m_eNextState; };

protected:

	unsigned int m_iStateNumber = -1;

	bool m_bStateFinished = false;

	ZUMO_STATES m_eNextState;
};


#endif

