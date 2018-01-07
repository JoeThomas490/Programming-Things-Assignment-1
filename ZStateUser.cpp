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
<<<<<<< HEAD
	//if (!m_bWaitingForDirection)
	//{
	//	CheckMovementInput();
	//	CheckNextStateInput();
	//}
	//else
	//{
	//	CheckDirectionInput();
	//}
=======
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

	if (InputManagerClass::IsKeyPressed(32))
	{
		MotorsClass::GetMotorInstance().Turn90(1, false);
	}
>>>>>>> parent of d5f9035... Added ability to go from USER state to CORRIDOR state by pressing 'c' when in USER state.
}

void ZStateUser::StopState()
{
	SPRINT(Stopping USER State);
}

//void ZStateUser::CheckMovementInput()
//{
//	if (InputManagerClass::IsKeyPressed('w'))
//	{
//		MotorsClass::GetMotorInstance().SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
//
//	}
//	if (InputManagerClass::IsKeyPressed('s'))
//	{
//		if (MotorsClass::GetLeftMotorSpeed() != 0 && MotorsClass::GetRightMotorSpeed() != 0)
//		{
//			MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
//		}
//		else
//		{
//			MotorsClass::GetMotorInstance().SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
//		}
//	}
//	if (InputManagerClass::IsKeyPressed('a'))
//	{
//		MotorsClass::GetMotorInstance().Turn(-1, 50, false);
//	}
//	if (InputManagerClass::IsKeyPressed('d'))
//	{
//		MotorsClass::GetMotorInstance().Turn(1, 50, false);
//	}
//
//	if (InputManagerClass::IsKeyPressed('9'))
//	{
//		MotorsClass::GetMotorInstance().Turn90(-1, false);
//	}
//	if (InputManagerClass::IsKeyPressed('0'))
//	{
//		MotorsClass::GetMotorInstance().Turn90(1, false);
//	}
//
//
//	if (InputManagerClass::IsKeyPressed(32))
//	{
//		MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
//	}
//}
//
//void ZStateUser::CheckNextStateInput()
//{
//	if (InputManagerClass::IsKeyPressed('c'))
//	{
//		m_eNextState = ZUMO_STATES::CORRIDOR;
//		m_bWaitingForDirection = true;
//
//		SPRINT(Corridor detected);
//		SPRINT(Which direction ? 'r' or 'l');
//	}
//	if (InputManagerClass::IsKeyPressed('r'))
//	{
//		m_eNextState = ZUMO_STATES::ROOM;
//		m_bWaitingForDirection = true;
//
//		SPRINT(Room detected);
//		SPRINT(Which direction ? 'r' or 'l');
//	}
//}
//
//void ZStateUser::CheckDirectionInput()
//{
//	if (InputManagerClass::IsKeyPressed('r'))
//	{
//		MotorsClass::GetMotorInstance().Turn90(1, false);
//		m_bStateFinished = true;
//	}
//	if (InputManagerClass::IsKeyPressed('l'))
//	{
//		MotorsClass::GetMotorInstance().Turn90(-1, false);
//		m_bStateFinished = true;
//	}
//}
