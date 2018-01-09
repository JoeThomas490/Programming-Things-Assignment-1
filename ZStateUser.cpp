#include "ZStateUser.h"

ZStateUser::ZStateUser()
{
}

ZStateUser::~ZStateUser()
{
}

void ZStateUser::InitState()
{
#if PRINT_STATE_CHANGES
	SPRINT(Initialising USER State);
#endif
	//Make sure the state hasn't been finished
	m_bStateFinished = false;
	m_bWaitForDirection = false;

	m_eNextState = ZUMO_STATES::USER;
}

void ZStateUser::UpdateState()
{
	//If we're not waiting for a direction (running normally)
	if (!m_bWaitForDirection)
	{
		CheckMovementInput();
		CheckStateChangeInput();
	}
	else
	{
		CheckDirectionInput();
	}
}

void ZStateUser::StopState()
{
#if PRINT_STATE_CHANGES
	SPRINT(Stopping USER State);
#endif
}

void ZStateUser::CheckMovementInput()
{
	//If the 'w' key is pressed
	if (InputManagerClass::IsKeyPressed('w'))
	{
		//Set both motors to move the robot forward
		MotorsClass::GetMotorInstance().SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	}
	//If the 's' key is pressed
	if (InputManagerClass::IsKeyPressed('s'))
	{
		//If both motor speeds don't equal 0 then set stop robot
		if (MotorsClass::GetLeftMotorSpeed() != 0 && MotorsClass::GetRightMotorSpeed() != 0)
		{
			//Stop motors
			MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
		}
		//Otherwise put the robot in reverse
		else
		{
			MotorsClass::GetMotorInstance().SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
		}
	}
	//If the 'a' key is pressed
	if (InputManagerClass::IsKeyPressed('a'))
	{
		//Turn slightly the left
		MotorsClass::GetMotorInstance().Turn(-1, 50, false);
	}
	//If the 'd' key is pressed
	if (InputManagerClass::IsKeyPressed('d'))
	{
		//Turn slightly the right
		MotorsClass::GetMotorInstance().Turn(1, 50, false);
	}
	//If the '9' key is pressed
	if (InputManagerClass::IsKeyPressed('9'))
	{
		//Turn 90 degrees to the left
		MotorsClass::GetMotorInstance().Turn90(-1, false);
	}
	//If '0' key is pressed
	if (InputManagerClass::IsKeyPressed('0'))
	{
		//Turn 90 degrees to the right
		MotorsClass::GetMotorInstance().Turn90(1, false);
	}

	//If space bar has been pressed
	if (InputManagerClass::IsKeyPressed(32))
	{
		//Stop robot
		MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);
	}
}

void ZStateUser::CheckStateChangeInput()
{
	//If the 'c' key is pressed
	if (InputManagerClass::IsKeyPressed('c'))
	{
		//Change the connected state to corridor behaviour
		m_eNextState = ZUMO_STATES::CORRIDOR;
		//Set this state to now wait for a direction
		m_bWaitForDirection = true;


		//SPRINT(Corridor detected..);
		SPRINT(Which direction ? [r]ight[l]eft or [s]traight);

	}
	//If the 'r' key is pressed
	if (InputManagerClass::IsKeyPressed('r'))
	{
		//Change the connected state to corridor behaviour
		m_eNextState = ZUMO_STATES::ROOM;
		//Set this state to now wait for a direction
		m_bWaitForDirection = true;

		//Notify user
		//SPRINT(Room detected..);
		SPRINT(Which direction ? [r]ight  [l]eft or [s]traight );
	}

	if (InputManagerClass::IsKeyPressed('e'))
	{
		//Change the connected state to return behaviour (returns back down the corridor)
		m_eNextState = ZUMO_STATES::RETURN;

		//Set the state to be finished
		m_bStateFinished = true;
	}
}

void ZStateUser::CheckDirectionInput()
{
	//If the 'r' key is pressed
	if (InputManagerClass::IsKeyPressed('r'))
	{
		//Turn 90 degrees to the left
		MotorsClass::GetMotorInstance().Turn90(1, false);

		//Finish state
		m_bStateFinished = true;


		//Increment current corridor
		m_pBuildingData->m_iCurrentCorridor++;
		m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor].m_eDirectionFromParent = DIRECTION::RIGHT;
		m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor].m_pParentCorridor = &m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor - 1];

		//Notify user
		//SPRINT(Entering room on right..);
	}
	//If '0' key is pressed
	if (InputManagerClass::IsKeyPressed('l'))
	{
		//Turn 90 degrees to the right
		MotorsClass::GetMotorInstance().Turn90(-1, false);

		//Finish state
		m_bStateFinished = true;

		//Increment current corridor
		m_pBuildingData->m_iCurrentCorridor++;
		m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor].m_eDirectionFromParent = DIRECTION::LEFT;
		m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor].m_pParentCorridor = &m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor - 1];


		//Notify user
		//SPRINT(Entering room on left..);
	}

	if (InputManagerClass::IsKeyPressed('s'))
	{
		//Finish state
		m_bStateFinished = true;

		//Increment current corridor
		m_pBuildingData->m_iCurrentCorridor++;

		//Notify user
		SPRINT(Carrying on forward..);
	}


}
