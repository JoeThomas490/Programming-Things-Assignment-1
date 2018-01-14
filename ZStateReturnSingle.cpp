#include "ZStateReturnSingle.h"

ZStateReturnSingle::ZStateReturnSingle()
{
}

ZStateReturnSingle::~ZStateReturnSingle()
{
}

//Virtual function for initialising state
void ZStateReturnSingle::InitState()
{
	//Make sure the state isn't already finished
	m_bStateFinished = false;

	//Get the reflectance array instance
	m_reflectanceArray = ReflectanceArrayClass::GetReflectanceArrayInstance();

	//Get the pointer to the corridor we're currently moving through
	m_pCorridor = m_pBuildingData->GetCurrentCorridor();

	//Get the length of this corridor
	m_fCorridorTime = m_pCorridor->m_fApproxLength;

	SPRINT(Approximate return time:);
	Serial.print(m_fCorridorTime / 1000);

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
void ZStateReturnSingle::UpdateState()
{
	//Check for any wall collisions and adjust robot appropriately
	CheckWallCollision();

	//Calculate the current elapsed time for moving down this corridor
	float elapsedTime = millis() - m_fStartTime;

	//If our elapsed time is greater than the length of the corridor
	if (elapsedTime > m_fCorridorTime)
	{
		SPRINT(Reached length of corridor.Stopping...);

		//Stop the robot and add a small delay
		m_motors.SetMotorSpeeds(0, 0);
		delay(500);

		m_bStateFinished = true;
		m_eNextState = ZUMO_STATES::USER;
	}
}

void ZStateReturnSingle::StopState()
{

}

//Uses the reflectance array to check any wall collision
//and moves out the way
void ZStateReturnSingle::CheckWallCollision()
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
