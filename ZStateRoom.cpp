#include "ZStateRoom.h"

ZStateRoom::~ZStateRoom()
{
}

void ZStateRoom::InitState()
{
	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	delay(150);

	m_motors.SetMotorSpeeds(0, 0);

	m_bScanFinished = false;
	m_bScanningRoom = false;

	m_bStateFinished = false;
}

void ZStateRoom::UpdateState()
{
	if (m_bScanningRoom == false)
	{
		ScanRoom();
	}
	
	if (m_bScanFinished == true)
	{
		m_eNextState = ZUMO_STATES::USER;
		m_bStateFinished = true;
	}
}

void ZStateRoom::StopState()
{
}

void ZStateRoom::ScanRoom()
{
	delay(1000);

	digitalWrite(13, HIGH);

	SPRINT(Scanning room....);
	m_bScanningRoom = true;

	int hitCount = 0;

	for (int i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			m_motors.SetMotorSpeeds(-SCAN_SPEED, SCAN_SPEED);
		else
			m_motors.SetMotorSpeeds(SCAN_SPEED, -SCAN_SPEED);

		delay(30);
		

		if (PingSonar())
		{
			hitCount++;
		}
	}

	m_motors.SetMotorSpeeds(0, 0);

	if(hitCount > 1)
	{ 
		Corridor* corridor = m_pBuildingData->GetCurrentCorridor();

		Room* room = corridor->GetCurrentRoom();
		room->m_bPingHit = true;

		SPRINT(Something has been found!!!);
	}

	// Turn off LED to indicate we are finished with the scan
	digitalWrite(13, LOW);

	SPRINT(Finished scanning...);

	m_motors.SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);

	delay(75);

	m_motors.SetMotorSpeeds(0, 0);

	m_bScanFinished = true;

}

bool ZStateRoom::PingSonar()
{
	float ping = m_sonar.PingCm();
#if PRINT_SONAR_PING
	SPRINT(Ping :);
	Serial.print(ping);
#endif

	if (ping > 0)
	{
		SPRINT(PING HIT);
		return true;
	}

	return false;
};
