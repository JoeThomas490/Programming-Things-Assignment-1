#include "ZStateReturn.h"

ZStateReturn::~ZStateReturn()
{
}

void ZStateReturn::InitState()
{
	m_motors = MotorsClass::GetMotorInstance();
	m_reflectanceArray = ReflectanceArrayClass::GetReflectanceArrayInstance();

	m_bStateFinished = false;

	m_motors.Turn90(1, false);
	delay(250);
	m_motors.Turn90(1, false);
	delay(250);

	m_pFromCorridor = m_pBuildingData->GetCurrentCorridor();

	m_fCorridorTime = m_pFromCorridor->m_fApproxLength;
	m_fStartTime = millis();

	SPRINT(Approximate return time:);
	Serial.print(m_fCorridorTime);

	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
}

void ZStateReturn::UpdateState()
{
	CheckWallCollision();

	float elapsedTime = millis() - m_fStartTime;

	if (elapsedTime > m_fCorridorTime)
	{
		SPRINT(Reached length of corridor. Stopping...);
		m_motors.SetMotorSpeeds(0, 0);

		delay(500);

		DIRECTION endDirection = m_pBuildingData->GetCurrentCorridor()->m_eDirectionFromParent;
		if (endDirection == DIRECTION::LEFT)
		{
			m_motors.Turn90(1, false);
		}
		else if (endDirection == DIRECTION::RIGHT)
		{
			m_motors.Turn90(-1, false);
		}

		delay(250);

		Corridor* nextCorridor = m_pBuildingData->GetParentCorridor(m_pFromCorridor);
		if (nextCorridor == nullptr)
		{
			SPRINT(Reached end of all corridors(parent is null));
			m_eNextState = ZUMO_STATES::USER;
			m_bStateFinished = true;
		}
		else
		{
			m_fStartTime = millis();
			m_fCorridorTime = nextCorridor->m_fApproxLength;

			m_pFromCorridor = nextCorridor;

			m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);

		}
	}
}

void ZStateReturn::StopState()
{
	
}

void ZStateReturn::CheckWallCollision()
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

			SPRINT(Returned to wall..);
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
