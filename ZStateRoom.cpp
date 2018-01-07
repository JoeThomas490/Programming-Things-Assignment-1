#include "ZStateRoom.h"

ZStateRoom::~ZStateRoom()
{
}

void ZStateRoom::InitState()
{
	m_motors = MotorsClass::GetMotorInstance();

	m_motors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
	delay(75);

	m_motors.SetMotorSpeeds(0, 0);
}

void ZStateRoom::UpdateState()
{
	ScanRoom();
}

void ZStateRoom::StopState()
{
}

void ZStateRoom::ScanRoom()
{
	// Wait 1 second and then begin automatic sensor calibration
	// by rotating in place to sweep the sensors over the line
	delay(1000);

	digitalWrite(13, HIGH);

	SPRINT(Scanning room....);
	int i;
	for (i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			MotorsClass::GetMotorInstance().SetMotorSpeeds(-200, 200);
		else
			MotorsClass::GetMotorInstance().SetMotorSpeeds(200, -200);

		// Since our counter runs to 80, the total delay will be
		// 80*20 = 1600 ms.
		delay(20);
	}

	// Turn off LED to indicate we are through with calibration
	digitalWrite(13, LOW);

	//Set motors to not move
	MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);

	SPRINT(Finished scanning...);

	MotorsClass::GetMotorInstance().SetMotorSpeeds(-RUN_SPEED, -RUN_SPEED);

	m_eNextState = ZUMO_STATES::USER;
	m_bStateFinished = true;

}
