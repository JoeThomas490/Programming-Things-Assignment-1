#include "InitZState.h"


InitZState::InitZState()
{
}

InitZState::~InitZState()
{
}

void InitZState::InitState()
{
	SPRINT("INITIALISED INIT STATE");
}

void InitZState::UpdateState()
{
	if (InputManagerClass::IsKeyPressed('p'))
	{
		SPRINT("CHANGING STATE");
		m_bStateFinished = true;
	}
}

void InitZState::StopState()
{
	SPRINT("STOPPING INIT STATE");
}
