#include "ZStateInit.h"


ZStateInit::ZStateInit()
{
}

ZStateInit::~ZStateInit()
{
}

void ZStateInit::InitState()
{
	InputManagerClass::Init();
	ReflectanceArrayClass::GetReflectanceArrayInstance().Init();
	ReflectanceArrayClass::GetReflectanceArrayInstance().Calibrate();

	SPRINT("INITIALISED INIT STATE");

	SPRINT("Press 'p' to start!");
}

void ZStateInit::UpdateState()
{
	if (InputManagerClass::IsKeyPressed('p'))
	{
		m_bStateFinished = true;
	}
}

void ZStateInit::StopState()
{
	SPRINT("STOPPING INIT STATE");
}
