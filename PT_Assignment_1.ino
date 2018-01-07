
#include "ZStateRoom.h"
#include "ZStateInit.h"
#include "ZStateUser.h"
#include "ZStateCorridor.h"

#include "InputManager.h"
#include "Motors.h"
#include "ReflectanceArray.h"

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#include <NewPing\NewPing.h>

#include "HelperMacros.h"
#include "Constants.h"

ZumoBuzzer buzzer;

Pushbutton button(ZUMO_BUTTON);

bool runMotors = true;
bool runReflectanceArray = true;

bool run = true;

//Different behaviour states for robot

ZState::ZUMO_STATES m_eZumoState;
NewPing sonar(SONAR::TRIGGER_PIN, SONAR::ECHO_PIN, SONAR::MAX_DISTANCE); // NewPing setup of pins and maximum distance.

ZState** m_aStateList;
ZState* m_pCurrentState;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									ARDUINO FUNCTIONS													//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
	m_aStateList = new ZState*[4];

	ZStateInit* initState = new ZStateInit();
	ZStateUser* userState = new ZStateUser();
	ZStateCorridor* corridorState = new ZStateCorridor();
	ZStateRoom* roomState = new ZStateRoom();

	AddState(initState);
	AddState(userState);
	AddState(corridorState);
	AddState(roomState);

	//Set start state as init state
	m_eZumoState = ZState::ZUMO_STATES::INIT;

	//Begin Serial communication
	Serial.begin(9600);

	// Play a little welcome song
	buzzer.play(">g32>>c32");

	SPRINT(Press button on Zumo to begin..);

	// Wait for the user button to be pressed and released
	button.waitForButton();

	// Play music and wait for it to finish before we start driving.
	buzzer.play("L16 cdegreg4");

	runMotors = false;

	ChangeState((int)ZState::ZUMO_STATES::INIT);


}

//Main Loop
void loop()
{
	InputManagerClass::HandleInput();

	if (InputManagerClass::IsKeyPressed('.'))
	{
		run = !run;
	}

	if (run == true)
	{
		if (m_pCurrentState != nullptr)
		{
			if (m_pCurrentState->GetIsStateFinished())
			{
				ChangeState((int)m_pCurrentState->GetNextState());
			}

			m_pCurrentState->UpdateState();
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									INPUT																//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReadInput()
{
	if (Serial.available() > 0)
	{
		int input = Serial.read();
		switch (tolower(input))
		{
		case 'c':
#if PRINT_STATE_CHANGES
			SPRINT("Changing to CORRIDOR state");
#endif
			m_eZumoState = ZState::ZUMO_STATES::CORRIDOR;
			runReflectanceArray = true;
			delay(100);
			break;
		case 'u':
#if PRINT_STATE_CHANGES
			SPRINT("Changing to USER state");
#endif
			m_eZumoState = ZState::ZUMO_STATES::USER;
			delay(100);
			break;

		case '1':
			runMotors = !runMotors;
			break;
		case '2':
			runReflectanceArray = !runReflectanceArray;
			break;

		case 'r':
			if (m_eZumoState == ZState::ZUMO_STATES::USER)
			{
				m_eZumoState = ZState::ZUMO_STATES::ROOM;
			}
			break;
		case 'o':
			if (m_eZumoState == ZState::ZUMO_STATES::USER)
			{
				m_eZumoState = ZState::ZUMO_STATES::CORRIDOR;
			}

		default:
			break;
		}
	}
}

void ReadStartStopInput()
{
	if (Serial.available() > 0)
	{
		int input = Serial.read();
		switch (input)
		{
		case 'p':
		case 'P':
			runMotors = !runMotors;
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									STATE CHANGES														//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void AddState(ZState* mState)
{
	static int stateCounter = 0;
	m_aStateList[stateCounter] = mState;
	mState->SetStateNumber(stateCounter);
	stateCounter++;
}

void ChangeState(ZState* mState)
{
	int stateNumber = mState->GetStateNumber();

	SPRINT(Changing to state number : );
	Serial.print("\t");
	Serial.print(stateNumber);

	if (m_pCurrentState == nullptr)
	{
		m_pCurrentState = m_aStateList[stateNumber];
		m_pCurrentState->InitState();
	}
	else
	{
		m_pCurrentState->StopState();
		m_pCurrentState = m_aStateList[stateNumber];
		m_pCurrentState->InitState();
	}
}

void ChangeState(int mStateNum)
{
	SPRINT(Changing to state number : );
	Serial.print("\t");
	Serial.print(mStateNum);


	if (m_pCurrentState == nullptr)
	{
		m_pCurrentState = m_aStateList[mStateNum];
		m_pCurrentState->InitState();
	}
	else
	{
		m_pCurrentState->StopState();
		m_pCurrentState = m_aStateList[mStateNum];
		m_pCurrentState->InitState();
	}
}