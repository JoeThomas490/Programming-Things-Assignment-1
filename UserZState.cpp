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
		MotorsClass::SetMotorSpeeds(RUN_SPEED, RUN_SPEED);

	}
	if (InputManagerClass::IsKeyPressed('s'))
	{
		if (MotorsClass::GetLeftMotorSpeed() != 0 && MotorsClass::GetRightMotorSpeed() != 0)
		{
			MotorsClass::SetMotorSpeeds(0, 0);
		}
		else
		{
			MotorsClass::SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
		}
	}
	if (InputManagerClass::IsKeyPressed('a'))
	{
		MotorsClass::Turn(-1, 50, false);
	}
	if (InputManagerClass::IsKeyPressed('d'))
	{
		MotorsClass::Turn(1, 50, false);

	}
}

void UserZState::StopState()
{
	SPRINT("STOPPING USER STATE");
}
