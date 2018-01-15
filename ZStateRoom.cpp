#include "ZStateRoom.h"

ZStateRoom::ZStateRoom()
{
}

ZStateRoom::~ZStateRoom()
{
}

//Virtual function for initialising state
void ZStateRoom::InitState()
{
	//Move the robot forward slightly
	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	delay(150);

	//And then stop
	m_motors.SetMotorSpeeds(0, 0);

	m_bScanFinished = false;
	m_bScanningRoom = false;
	m_bStateFinished = false;
}

//Virtual function for updating state (tick)
void ZStateRoom::UpdateState()
{
	//If we're not already scanning the room
	if (m_bScanningRoom == false)
	{
		//Call the function to trigger a scan
		ScanRoom();
	}
	
	//If the scan has been finished
	if (m_bScanFinished == true)
	{
		//Finish the state and move into USER mode
		m_eNextState = ZUMO_STATES::USER;
		m_bStateFinished = true;
	}
}

//Virtual function for stopping state
void ZStateRoom::StopState()
{
}

//Function to be called to trigger a scan
void ZStateRoom::ScanRoom()
{
	delay(1000);

	//Trigger the LED on pin 13
	digitalWrite(13, HIGH);

	SPRINT(Scanning room....);
	//Trigger the scanning room bool
	m_bScanningRoom = true;

	//Number of hits counted
	int hitCount = 0;
	
	//Loop through and rotate the robot
	for (int i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			m_motors.SetMotorSpeeds(-SCAN_SPEED, SCAN_SPEED);
		else
			m_motors.SetMotorSpeeds(SCAN_SPEED, -SCAN_SPEED);

		delay(30);
		

		//If we have got a ping hit
		if (PingSonar())
		{
			//Increment the hit count
			hitCount++;
		}
	}

	//Stop the robot from rotating
	m_motors.SetMotorSpeeds(0, 0);

	SPRINT(Finished scanning...);

	//If we've hit more than once
	if(hitCount > 0)
	{ 
		//Get the pointer to the current corridor we're on
		Corridor* corridor = m_pBuildingData->GetCurrentCorridor();

		//Get the pointer to the current room we're in
		Room* room = corridor->GetCurrentRoom();

		//Set the flag to say there's something in the room
		room->m_bPingHit = true;

		SPRINT(Something has been found in Room );
		Serial.print(room->ID);
		Serial.print(" in corridor ");
		Serial.print(corridor->ID);
	}
	else
	{
		SPRINT(Nothing found);
	}

	// Turn off LED to indicate we are finished with the scan
	digitalWrite(13, LOW);

	//Reverse the robot out the room
	m_motors.SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);
	delay(75);
	m_motors.SetMotorSpeeds(0, 0);


	//Set the scan to be finished
	m_bScanFinished = true;
}

//Function to handle calling of sonar ping
//Returns:
//Whether the ping hit or not
bool ZStateRoom::PingSonar()
{
	//Get the ping value from our sonar
	float ping = m_sonar.PingCm();
#if PRINT_SONAR_PING
	SPRINT(Ping :);
	Serial.print(ping);
#endif

	//If it's greater than 0 cm then it's a hit and
	//return true
	if (ping > 0)
	{
		return true;
	}

	//Otherwise return false
	return false;
};
