#ifndef _BUILDINGDATA_H_
#define _BUILDINGDATA_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"
#include "HelperMacros.h"

//*********************************************************************************************
// File:			BuildingData.h
// Description:		Class to hold all data to do with the building the robot is currently in
//					such as corridors (with their lengths in time) and all rooms associated
//					with that corridor.
// Notes:			
// Todo:			
//*********************************************************************************************

//Directions in which a corridor/room could be
enum DIRECTION
{
	INVALID,
	LEFT,
	RIGHT,
	STRAIGHT
};


//Structure containing data to do with a single room
struct Room
{
	//ID associated with this room
	int ID;
	//Whether something was found in the room
	bool m_bPingHit;
	//Time it took to get to the room
	float m_fTimeDownCorridor;

	//Direction of room from corridor
	DIRECTION m_eDirection;

	Room()
		: ID(-1), m_bPingHit(false), m_fTimeDownCorridor(0)
		,m_eDirection(DIRECTION::INVALID)
	{
	}
};


//Structure to contain data to do with Corridors
struct Corridor
{
	//ID of room
	int ID;
	//Approximate length in milliseconds (time taken to drive down)
	float m_fApproxLength;
	//Corridor that is linked to this one (nullptr if it's the first corridor)
	Corridor* m_pParentCorridor;
	//Direction to turn to get down this corridor
	DIRECTION m_eDirectionFromParent;
	//Array of rooms 
	Room m_aRooms[MAX_ROOMS];
	//Number of rooms within corridor
	int m_iNumRooms;

	//Default constructor
	Corridor()
		: ID(0), m_fApproxLength(0), m_pParentCorridor(nullptr)
		, m_eDirectionFromParent(INVALID), m_iNumRooms(0)
	{
	}

	//Add a room to the array
	//Parameters:
	//1.Approximate time down the corridor (in Ms)
	//2.Direction from the corridor to room 
	void AddRoom(float mApproxTime, DIRECTION mDirection)
	{
		//Get pointer to room we want to change
		Room* room = &m_aRooms[m_iNumRooms];
		//Set it's ID to the number of rooms we have
		room->ID = m_iNumRooms;
		//Set it's time down the corridor
		room->m_fTimeDownCorridor = mApproxTime;
		//Set it's direction from the corridor
		room->m_eDirection = mDirection;
		//Increment our number of rooms for this corridor
		m_iNumRooms++;
	}

	//Get a pointer to a room for a given index
	//Parameters:
	//1.Index of room to get
	//Returns:
	//Pointer to chosen room
	Room* GetRoom(int mIndx)
	{
		return &m_aRooms[mIndx];
	}
	
	//Gets a pointer to a room that we're currently
	//Returns:
	//Pointer to current room
	Room* GetCurrentRoom()
	{
		return &m_aRooms[m_iNumRooms - 1];
	}
};


//Class to hold all the data to do with a building
//which includes an array of corridors and rooms
class BuildingData
{
public:

	BuildingData();
	~BuildingData();

	//Get the current corridor the robot is on
	//Return:
	//Pointer to current corridor we're on
	Corridor* GetCurrentCorridor() { return &m_aCorridors[m_iCurrentCorridor]; };

	//Get the parent corridor attached to a corridor
	//Parameters:
	//1. Corridor to get the parent from
	//Return:
	//Pointer to parent corridor
	Corridor* GetParentCorridor(Corridor* mChildCorridor);

	//Gets the previous corridor in the list
	//Return:
	//Pointer to previous corridor
	Corridor* PreviousCorridor();

	//Adds a corridor to the vector of corridors
	//Parameters:
	//1.Direction from parent corridor
	//2.Pointer to parent corridor
	void AddCorridor(DIRECTION mDirection, Corridor* mpParentCorridor);

	//Array of corridors
	Corridor m_aCorridors[MAX_CORRIDORS];

	//Current corridor the robot is on
	int m_iCurrentCorridor = 0;
};


#endif

