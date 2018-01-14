#include "ZStateReturn.h"

ZStateReturn::ZStateReturn()
{
}

ZStateReturn::~ZStateReturn()
{
}

//Virtual function for initialising state
void ZStateReturn::InitState()
{
	//Make sure the state isn't already finished
	m_bStateFinished = false;

	//Get the reflectance array instance
	m_reflectanceArray = ReflectanceArrayClass::GetReflectanceArrayInstance();

	//Get the pointer to the corridor we're currently moving through
	m_pCurrentCorridor = m_pBuildingData->GetCurrentCorridor();

	//Get the length of this corridor
	m_fCorridorTime = m_pCurrentCorridor->m_fApproxLength;
	
	SPRINT(Approximate return time:);
	Serial.print(m_fCorridorTime/1000);

	//Turn through two 90 degree turns and have a delay 
	//in between
	m_motors.Turn90(1, false);
	delay(500);
	m_motors.Turn90(1, false);
	delay(200);
	//Start moving forward
	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);

	//Get the current elapsed time of the program
	m_fStartTime = millis();
}

//Virtual function for updating state (tick)
void ZStateReturn::UpdateState()
{
	//Check for any wall collisions and adjust robot appropriately
	CheckWallCollision();

	//Calculate the current elapsed time for moving down this corridor
	float elapsedTime = millis() - m_fStartTime;

	//If our elapsed time is greater than the length of the corridor
	if (elapsedTime > m_fCorridorTime)
	{
		SPRINT(Reached length of corridor. Stopping...);

		//Stop the robot and add a small delay
		m_motors.SetMotorSpeeds(0, 0);
		delay(500);


		//Get the direction that was turned to get into this corridor
		DIRECTION endDirection = m_pBuildingData->GetCurrentCorridor()->m_eDirectionFromParent;
		//If we turned left to get into this corridor
		if (endDirection == DIRECTION::LEFT)
		{
			//Turn right
			m_motors.Turn90(1, false);
		}
		//If we turned right to get into this corridor
		else if (endDirection == DIRECTION::RIGHT)
		{
			//Turn left
			m_motors.Turn90(-1, false);
		}
		delay(250);

		//Get the pointer to the next corridor we're moving into
		//(The parent of our current corridor)
		Corridor* nextCorridor = m_pBuildingData->GetParentCorridor(m_pCurrentCorridor);

		SPRINT(Moving into corridor);
		Serial.print(nextCorridor->ID);

		//If our current corridor doesn't have a parent
		if (nextCorridor == nullptr)
		{
			//We've reached the end of the return path
			SPRINT(Reached end of all corridors(parent is null));
			
			//Finish the state and move into USER mode
			m_bStateFinished = true;
			m_eNextState = ZUMO_STATES::USER;
		}
		else
		{
			//Reset start time
			m_fStartTime = millis();

			//Get the length of the new corridor
			m_fCorridorTime = nextCorridor->m_fApproxLength;

			//Set our current corridor pointer to the new corridor
			m_pCurrentCorridor = nextCorridor;

			//Start moving forward
			m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
		}
	}
}

void ZStateReturn::StopState()
{
	
}

//Uses the reflectance array to check any wall collision
//and moves out the way
void ZStateReturn::CheckWallCollision()
{
	ReflectanceData hitData;

	hitData = m_reflectanceArray.HandleReflectanceArray();

	//If the reflectance array has detected a hit
	if (hitData.m_bHit == true)
	{
		//If we've hit a wall
		if (hitData.m_iSensorsHit > 1 && hitData.m_iDirection == 0)
		{
			m_motors.SetMotorSpeeds(0, 0);
		}

		else if (hitData.m_iSensorsHit == 1)
		{
			//If we've hit something on the left
			if (hitData.m_iDirection == -1)
			{
				m_motors.Turn(1, 30, true);
			}
			else if (hitData.m_iDirection == 1)
			{
				m_motors.Turn(-1, 30, true);
			}
		}

	}
}
