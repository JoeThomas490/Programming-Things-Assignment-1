#include "ZStateInit.h"


ZStateInit::ZStateInit()
{
}

ZStateInit::~ZStateInit()
{
}

void ZStateInit::InitState()
{
	m_bStateFinished = false;

	pinMode(13, OUTPUT);

	InputManagerClass::Init();
	ReflectanceArrayClass::GetReflectanceArrayInstance().Init();
	ReflectanceArrayClass::GetReflectanceArrayInstance().Calibrate();


	m_eNextState = ZUMO_STATES::USER;

	SPRINT(Initialised INIT state);
	SPRINT(Press 'p' to start!);
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
	SPRINT(Stopping INIT State);
}
