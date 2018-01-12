#include "ZStateInit.h"


ZStateInit::ZStateInit()
{
}

ZStateInit::~ZStateInit()
{
}

//Virtual function for initialising state
void ZStateInit::InitState()
{
	//Make sure the state hasn't already been finished
	m_bStateFinished = false;

	//Set pin 13 to be an output pin
	pinMode(13, OUTPUT);

	//Initialise the input manager class
	InputManagerClass::Init();

	//Initialise the reflectance array class
	ReflectanceArrayClass::GetReflectanceArrayInstance().Init();

	//Calibrate the reflectance array
	ReflectanceArrayClass::GetReflectanceArrayInstance().Calibrate();

	//Set the next state to be CORRIDOR
	m_eNextState = ZUMO_STATES::CORRIDOR;
}

//Virtual function for updating state (tick)
void ZStateInit::UpdateState()
{
	//Wait for the 'p' key to be pressed and then finish the state
	if (InputManagerClass::IsKeyPressed('p'))
	{
		m_bStateFinished = true;
	}
}

//Virtual function for stopping state
void ZStateInit::StopState()
{
}
