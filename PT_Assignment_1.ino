
#include "ZStateInit.h"
#include "UserZState.h"

#include "InputManager.h"
#include "Motors.h"
#include "ReflectanceArray.h"

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#include "HelperMacros.h"
#include "Constants.h"


MotorsClass m_gMotors;

ZumoBuzzer buzzer;

Pushbutton button(ZUMO_BUTTON);

bool runMotors = true;
bool runReflectanceArray = true;

//Different behaviour states for robot

ZState::ZUMO_STATES m_eZumoState;


ZState** m_aStateList;
ZState* m_pCurrentState;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//									ARDUINO FUNCTIONS													//
//																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
	m_aStateList = new ZState*[2];

	ZStateInit* initState = new ZStateInit();
	UserZState* userState = new UserZState();

	m_gMotors = MotorsClass::GetMotorInstance();

	AddState(initState);
	AddState(userState);

	//Set start state as init state
	m_eZumoState = ZState::ZUMO_STATES::INIT;

	//Begin Serial communication
	Serial.begin(9600);

	// Play a little welcome song
	buzzer.play(">g32>>c32");

	// Wait for the user button to be pressed and released
	button.waitForButton();

	// Play music and wait for it to finish before we start driving.
	buzzer.play("L16 cdegreg4");

	runMotors = false;

	ChangeState(0);
}

//Main Loop
void loop()
{
	InputManagerClass::HandleInput();


	if (m_pCurrentState != nullptr)
	{
		if (m_pCurrentState->GetIsStateFinished())
		{
			ChangeState(m_pCurrentState->GetStateNumber() + 1);
		}

		m_pCurrentState->UpdateState();
	}


//	if (runMotors == true)
//	{
//		switch (m_eZumoState)
//		{
//		case INIT:
//			m_gMotors.SetMotorSpeeds(0, 0);
//			m_eZumoState = ZUMO_STATES::CORRIDOR;
//#if PRINT_STATE_CHANGES
//			SPRINT("Changing to CORRIDOR state");
//#endif
//			break;
//		case USER:
//			//Read input from user through Serial connection (xBee)
//			ReadInput();
//			//InputManagerClass::HandleInput();
//			break;
//		case CORRIDOR:
//			//Read input from user through Serial connection (xBee)
//			ReadInput();
//
//			//If the reflectance array is allowed to run
//			if (runReflectanceArray)
//			{
//				HandleReflectanceArray();
//			}
//			break;
//		}
//	}
//	else
//	{
//		m_gMotors.SetMotorSpeeds(0, 0);
//		ReadStartStopInput();
//	}
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
			m_gMotors.SetMotorSpeeds(RUN_SPEED, RUN_SPEED);
			delay(100);
			break;
		case 'u':
#if PRINT_STATE_CHANGES
			SPRINT("Changing to USER state");
#endif
			m_eZumoState = ZState::ZUMO_STATES::USER;
			m_gMotors.SetMotorSpeeds(0, 0);
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

	SPRINT("Changing to state number : ");
	Serial.print("\t" + stateNumber);

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
	SPRINT("Changing to state number : ");
	Serial.print("\t" + mStateNum);


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