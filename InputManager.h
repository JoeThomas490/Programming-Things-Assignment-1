// InputManager.h

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "HelperMacros.h"

//ascii values 32 - 127 , 95 values
const int ASCII_RANGE = 95;

class InputManagerClass
{
public:

	static void init();

	static void HandleInput();

	static void ClearQueue();

	static bool IsKeyPressed(const char key);

protected:

};

extern InputManagerClass InputManager;

#endif

