// ZStateInit.h

#ifndef _ZSTATEINIT_H_
#define _ZSTATEINIT_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ZState.h"

class ZStateInit : public ZState
{
public:

	ZStateInit();
	virtual ~ZStateInit();

	virtual void InitState();
	virtual void UpdateState();

	virtual void StopState();

};


#endif

