
#include "Sonar.h"
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
#include <NewPing.h>


#include "HelperMacros.h"
#include "Constants.h"


ZumoBuzzer buzzer;

Pushbutton button(ZUMO_BUTTON);

bool m_bRunBehaviour = true;


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

	//Begin Serial communication
	Serial.begin(9600);

	// Play a little welcome song
	buzzer.play(">g32>>c32");

	SPRINT(Press button on Zumo to begin..);

	// Wait for the user button to be pressed and released
	button.waitForButton();

	// Play music and wait for it to finish before we start driving.
	buzzer.play("L16 cdegreg4");

	ChangeState((int)ZState::ZUMO_STATES::INIT);
}

//Main Loop
void loop()
{
	InputManagerClass::HandleInput();

	//Check if '.' is pressed and flip main run flag
	if (InputManagerClass::IsKeyPressed('.'))
	{
		m_bRunBehaviour = !m_bRunBehaviour;
	}

	//If we are supposed to run main behaviour
	if (m_bRunBehaviour)
	{
		//Check state pointer isn't null
		if (m_pCurrentState != nullptr)
		{
			//Check if the state is finished
			if (m_pCurrentState->GetIsStateFinished())
			{
				//If so change to the next connected state
				ChangeState((int)m_pCurrentState->GetNextState());
			}

			//Update the current state
			m_pCurrentState->UpdateState();
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