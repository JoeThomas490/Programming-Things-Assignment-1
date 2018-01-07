#include "ZStateInit.h"


ZStateInit::ZStateInit()
{
}

ZStateInit::~ZStateInit()
{
}

void ZStateInit::InitState()
{
	SPRINT("INITIALISED INIT STATE");
}

void ZStateInit::UpdateState()
{
	if (InputManagerClass::IsKeyPressed('p'))
	{
		SPRINT("CHANGING STATE");
		m_bStateFinished = true;
	}
}

void ZStateInit::StopState()
{
	SPRINT("STOPPING INIT STATE");
}
