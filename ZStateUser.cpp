#include "ZStateUser.h"

ZStateUser::ZStateUser()
{
}

ZStateUser::~ZStateUser()
{
}

void ZStateUser::InitState()
{
	SPRINT(Initialising USER State);

	m_bStateFinished = false;
}

void ZStateUser::UpdateState()
{
	if (InputManagerClass::IsKeyPressed('w'))
	{
		MotorsClass::GetMotorInstance().SetMotorSpeeds(RUN_SPEED, RUN_SPEED);

	}
	if (InputManagerClass::IsKeyPressed('s'))
	{
		if (MotorsClass::GetLeftMotorSpeed() != 0 && MotorsClass::GetRightMotorSpeed() != 0)
		{
			MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
		}
		else
		{
			MotorsClass::GetMotorInstance().SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
		}
	}
	if (InputManagerClass::IsKeyPressed('a'))
	{
		MotorsClass::GetMotorInstance().Turn(-1, 50, false);
	}
	if (InputManagerClass::IsKeyPressed('d'))
	{
		MotorsClass::GetMotorInstance().Turn(1, 50, false);
	}

	if (InputManagerClass::IsKeyPressed('9'))
	{
		MotorsClass::GetMotorInstance().Turn90(-1, false);
	}
	if (InputManagerClass::IsKeyPressed('0'))
	{
		MotorsClass::GetMotorInstance().Turn90(1, false);
	}

	if (InputManagerClass::IsKeyPressed(32))
	{
		MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
	}

	if (InputManagerClass::IsKeyPressed('c'))
	{
		m_eNextState = ZUMO_STATES::CORRIDOR;
		m_bStateFinished = true;
	}
}

void ZStateUser::StopState()
{
	SPRINT(Stopping USER State);
}
