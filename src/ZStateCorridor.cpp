#include "../ZStateCorridor.h"

ZStateCorridor::~ZStateCorridor()
{
}

void ZStateCorridor::InitState()
{
	SPRINT(Initialising CORRIDOR State);

	//Get singleton instance of reflectance array
	m_reflectanceArray = ReflectanceArrayClass::GetReflectanceArrayInstance();
	//Get singleton instance of motors
	m_motors = MotorsClass::GetMotorInstance();

	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);

	m_bStateFinished = false;
}

void ZStateCorridor::UpdateState()
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
		}

		else if (hitData.sensorsHit == 1)
		{
			//If we've hit something on the left
			if (hitData.direction == -1)
			{
				m_motors.Turn(1, 50, true);
			}
			else if (hitData.direction == 1)
			{
				m_motors.Turn(-1 ,50, true);
			}
		}
		
	}
}

void ZStateCorridor::StopState()
{
	SPRINT(Stopping CORRIDOR State);
}

