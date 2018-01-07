
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

#include "HelperMacros.h"
#include "Constants.h"


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
	m_aStateList = new ZState*[3];

	ZStateInit* initState = new ZStateInit();
	ZStateUser* userState = new ZStateUser();
	ZStateCorridor* corridorState = new ZStateCorridor();

	AddState(initState);
	AddState(userState);
	AddState(corridorState);

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

	if (m_pCurrentState != nullptr)
	{
		if (m_pCurrentState->GetIsStateFinished())
		{
			ChangeState((int) m_pCurrentState->GetNextState());
		}

		m_pCurrentState->UpdateState();
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