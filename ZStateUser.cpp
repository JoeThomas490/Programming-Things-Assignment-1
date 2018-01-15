#include "ZStateUser.h"

ZStateUser::ZStateUser()
{
}

ZStateUser::~ZStateUser()
{
}

//Virtual function for initialising state
void ZStateUser::InitState()
{
#if PRINT_STATE_CHANGES
	SPRINT(Initialising USER State);
#endif
	//Make sure the state hasn't been finished
	m_bStateFinished = false;
	m_bWaitForDirection = false;
	m_bWaitForReturnState = false;

	m_eNextState = ZUMO_STATES::USER;
}

//Virtual function for updating state (tick)
void ZStateUser::UpdateState()
{
	//If we're not waiting for a direction (running normally)
	if (!m_bWaitForDirection && !m_bWaitForReturnState)
	{
		CheckMovementInput();
		CheckStateChangeInput();
	}
	if (m_bWaitForDirection)
	{
		CheckDirectionInput();
	}
}

//Virtual function for stopping state
void ZStateUser::StopState()
{
#if PRINT_STATE_CHANGES
	SPRINT(Stopping USER State);
#endif
}

//Check key input to do with robot movement
void ZStateUser::CheckMovementInput()
{
	//If the 'w' key is pressed
	if (InputManagerClass::IsKeyPressed('w'))
	{
		//Set both motors to move the robot forward
		m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	}
	//If the 's' key is pressed
	if (InputManagerClass::IsKeyPressed('s'))
	{
		//If both motor speeds don't equal 0 then set stop robot
		if (MotorsClass::GetLeftMotorSpeed() != 0 && MotorsClass::GetRightMotorSpeed() != 0)
		{
			//Stop motors
			m_motors.SetMotorSpeeds(0, 0);
		}
		//Otherwise put the robot in reverse
		else
		{
			m_motors.SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
		}
	}
	//If the 'a' key is pressed
	if (InputManagerClass::IsKeyPressed('a'))
	{
		//Turn slightly the left
		m_motors.Turn(-1, 50, false);
	}
	//If the 'd' key is pressed
	if (InputManagerClass::IsKeyPressed('d'))
	{
		//Turn slightly the right
		m_motors.Turn(1, 50, false);
	}
	//If the '9' key is pressed
	if (InputManagerClass::IsKeyPressed('9'))
	{
		//Turn 90 degrees to the left
		m_motors.Turn90(-1, false);
	}
	//If '0' key is pressed
	if (InputManagerClass::IsKeyPressed('0'))
	{
		//Turn 90 degrees to the right
		m_motors.Turn90(1, false);
	}

	//If space bar has been pressed
	if (InputManagerClass::IsKeyPressed(32))
	{
		//Stop robot
		m_motors.SetMotorSpeeds(0, 0);
	}
}

//Check key input to do with state changes
void ZStateUser::CheckStateChangeInput()
{
	//If the 'c' key is pressed
	if (InputManagerClass::IsKeyPressed('C'))
	{
		//Change the connected state to corridor behaviour
		m_eNextState = ZUMO_STATES::CORRIDOR;
		//Set this state to now wait for a direction
		m_bWaitForDirection = true;


		//SPRINT(Corridor detected..);
		SPRINT(Which direction ? [r]ight[l]eft or [s]traight);

	}
	//If the 'r' key is pressed
	if (InputManagerClass::IsKeyPressed('R'))
	{
		//Change the connected state to corridor behaviour
		m_eNextState = ZUMO_STATES::ROOM;
		//Set this state to now wait for a direction
		m_bWaitForDirection = true;

		//Notify user
		SPRINT(Which direction ? [r]ight  [l]eft or [s]traight );
	}

	if (InputManagerClass::IsKeyPressed('e'))
	{
		//Change the connected state to return behaviour (returns back down the corridor)
		m_eNextState = ZUMO_STATES::RETURN;
		m_bStateFinished = true;
	}
}

//Check key input to do with directional state change
void ZStateUser::CheckDirectionInput()
{
	//If the 'r' key is pressed
	if (InputManagerClass::IsKeyPressed('r'))
	{
		//Turn 90 degrees to the left
		m_motors.Turn90(1, false);

		//Finish state
		m_bStateFinished = true;


		//If we're moving into a new corridor
		if (m_eNextState == ZUMO_STATES::CORRIDOR)
		{
			//Add a new corridor to our building data 
			m_pBuildingData->AddCorridor(DIRECTION::RIGHT, m_pBuildingData->GetCurrentCorridor());
		}
		//If we're moving into a room
		else if (m_eNextState == ZUMO_STATES::ROOM)
		{
			Corridor* currentCorridor = m_pBuildingData->GetCurrentCorridor();
			currentCorridor->GetCurrentRoom()->m_eDirection = DIRECTION::RIGHT;
		}
		//Notify user
		//SPRINT(Entering room on right..);
	}

	//If 'l' key is pressed
	if (InputManagerClass::IsKeyPressed('l'))
	{
		//Turn 90 degrees to the right
		m_motors.Turn90(-1, false);

		//Finish state
		m_bStateFinished = true;

		//If we're moving into a new corridor
		if (m_eNextState == ZUMO_STATES::CORRIDOR)
		{
			//Add a new corridor to our building data 
			m_pBuildingData->AddCorridor(DIRECTION::LEFT, m_pBuildingData->GetCurrentCorridor());
		}
		//If we're moving into a room
		else if (m_eNextState == ZUMO_STATES::ROOM)
		{
			//Get the current corridor we're in
			Corridor* currentCorridor = m_pBuildingData->GetCurrentCorridor();

			//Set the direction of the current room we've found
			currentCorridor->GetCurrentRoom()->m_eDirection = DIRECTION::LEFT;
		}

		//Notify user
		//SPRINT(Entering room on left..);
	}

	//If 's' key is pressed
	if (InputManagerClass::IsKeyPressed('s'))
	{
		//Finish state
		m_bStateFinished = true;

		//Notify user
		SPRINT(Carrying on forward..);
	}


}