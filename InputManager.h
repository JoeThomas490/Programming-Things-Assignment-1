#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "HelperMacros.h"

//*********************************************************************************************
// File:			InputManager.h
// Description:		Handles input for all states. Stores key presses in an array that gets 
//					cleared every frame. Other classes can query it by using IsKeyPressed()
// Notes:			
// Todo:			-Add a key held event?
//*********************************************************************************************

//ASCII values ranging from 32 - 127 , 95 values
const int ASCII_RANGE = 95;

class InputManagerClass
{
public:

	//Initialise the class
	static void Init();

	//Handles the actual input (Serial.read) and puts inside 
	//input queue
	static void HandleInput();

	//Resets the whole queue to false
	static void ClearQueue();

	//Main query function to see whether a key is currently pressed
	//Parameters:
	//1.Character to check is being pressed
	//Returns:
	//Whether key is pressed or not
	static bool IsKeyPressed(const char key);
};

extern InputManagerClass InputManager;

#endif

