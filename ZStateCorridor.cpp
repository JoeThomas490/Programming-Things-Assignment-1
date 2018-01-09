#include "ZStateCorridor.h"

ZStateCorridor::~ZStateCorridor()
{
}

void ZStateCorridor::InitState()
{
#if PRINT_STATE_CHANGES
	SPRINT(Initialising CORRIDOR State);
#endif
	//Get singleton instance of reflectance array
	m_reflectanceArray = ReflectanceArrayClass::GetReflectanceArrayInstance();

	//Get singleton instance of motors
	m_motors = MotorsClass::GetMotorInstance();

	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);

	m_bStateFinished = false;

	startTime = millis();
}

void ZStateCorridor::UpdateState()
{
	CheckWallCollision();
	CheckUserInput();

	
}

void ZStateCorridor::StopState()
{
#if PRINT_STATE_CHANGES
	SPRINT(Stopping CORRIDOR State);
#endif
}

void ZStateCorridor::CheckWallCollision()
{
	ReflectanceData hitData;

	hitData = m_reflectanceArray.HandleReflectanceArray();

	//If the reflectance array has detected a hit
	if (hitData.hit == true)
	{
		//If we've hit a wall
		if (hitData.sensorsHit > 1 && hitData.direction == 0)
		{
			m_motors.SetMotorSpeeds(0, 0);

			m_bStateFinished = true;
			m_eNextState = ZUMO_STATES::USER;

			//Building data stuff
			{
				//Get finishing time
				finishTime = millis();
				//Calculate overall time
				float overallCorridorTime = finishTime - startTime;
				//Set approximate time in building data
				m_pBuildingData->m_aCorridors[m_pBuildingData->m_iCurrentCorridor].m_fApproxLength = overallCorridorTime;

				SPRINT(Approximate corridor time : );
				Serial.print(overallCorridorTime/1000);
				Serial.print("\t");
				Serial.print("for corridor :");
				Serial.print(m_pBuildingData->m_iCurrentCorridor);
			}
			
		}

		else if (hitData.sensorsHit == 1)
		{
			//If we've hit something on the left
			if (hitData.direction == -1)
			{
				m_motors.Turn(1, 30, true);
			}
			else if (hitData.direction == 1)
			{
				m_motors.Turn(-1, 30, true);
			}
		}

	}
}

void ZStateCorridor::CheckUserInput()
{
	//If spacebar key is pressed or 's'
	if (InputManagerClass::IsKeyPressed(32) || InputManagerClass::IsKeyPressed('s'))
	{
		m_motors.SetMotorSpeeds(0, 0);
		m_eNextState = ZUMO_STATES::USER;
		m_bStateFinished = true;

		/*SPRINT(Corridor behaviour stopped..);
		SPRINT(Giving user control..);*/
	}
}

