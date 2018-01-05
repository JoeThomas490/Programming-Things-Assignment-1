#include "InputManager.h"

static bool m_aInputQueue[ASCII_RANGE];

void InputManagerClass::init()
{
	ClearQueue();
}

void InputManagerClass::HandleInput()
{
	ClearQueue();


	if (Serial.available() > 0)
	{
		int input = Serial.read();

		input -= 32;

		m_aInputQueue[input] = true;
	}
}

void InputManagerClass::ClearQueue()
{
	for (int i = 0; i < ASCII_RANGE; i++)
	{
		m_aInputQueue[i] = false;
	}
}

bool InputManagerClass::IsKeyPressed(const char key)
{
	int asciiVal = (int)key;
	if (asciiVal < 32 || asciiVal > 127)
	{
		SPRINT("Key entered out of range");
		Serial.print("\t");
		Serial.print(key);
		return false;
	}

	//Get range from 0 - 95
	asciiVal -= 32;

	if (m_aInputQueue[asciiVal])
	{
		return true;
	}
	else
	{
		return false;
	}
}


InputManagerClass InputManager;

