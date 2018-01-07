#include "UserZState.h"

UserZState::UserZState()
{
}

UserZState::~UserZState()
{
}

void UserZState::InitState()
{
	SPRINT("INITIALISING USER STATE");
}

void UserZState::UpdateState()
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
}

void UserZState::StopState()
{
	SPRINT("STOPPING USER STATE");
}
