#include "InputManager.h"

static bool m_aInputQueue[ASCII_RANGE];

void InputManagerClass::Init()
{
	//Make sure the queue is false initally
	ClearQueue();
}

void InputManagerClass::HandleInput()
{
	//Reset the queue to false every frame
	ClearQueue();

	//If there is something in the Serial queue
	if (Serial.available() > 0)
	{
		//Read it as an integer value (ASCII value of char)
		int input = Serial.read();

#if PRINT_USER_INPUT
		SPRINT(Key pressed : );
		Serial.print("\t");
		Serial.print((char)input);
#endif
		//Takeaway 32 as this is our starting value in the ASCII range
		input -= 32;
		//Use the value of input as the index within the array to set to true
		m_aInputQueue[input] = true;
	}
}

void InputManagerClass::ClearQueue()
{
	//Loop through whole array and set every member to false
	for (int i = 0; i < ASCII_RANGE; i++)
	{
		m_aInputQueue[i] = false;
	}
}

bool InputManagerClass::IsKeyPressed(const char key)
{
	//Get the integer value of the character being passed
	int asciiVal = (int)key;
	//Check whether the key is in range
	if (asciiVal < 32 || asciiVal > 127)
	{
		SPRINT(Key entered out of range);
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

