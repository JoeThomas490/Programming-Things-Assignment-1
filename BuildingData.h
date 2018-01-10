// BuildingData.h

#ifndef _BUILDINGDATA_H
#define _BUILDINGDATA_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"

//Directions in which a corridor/room could be
enum DIRECTION
{
	INVALID,
	LEFT,
	RIGHT,
	STRAIGHT
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

	Corridor()
		: ID(0), m_fApproxLength(0), m_pParentCorridor(nullptr)
		, m_eDirectionFromParent(INVALID)
	{
	}
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
	//Corridor attached to this room
	Corridor* m_pParentCorridor;
	//Direction of room from corridor
	DIRECTION m_eDirection;
	
	Room()
		: ID(-1), m_bPingHit(false), m_fTimeDownCorridor(0)
		, m_pParentCorridor(nullptr), m_eDirection(DIRECTION::INVALID)
	{
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

