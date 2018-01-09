// BuildingData.h

#ifndef _BUILDINGDATA_H
#define _BUILDINGDATA_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum DIRECTION
{
	INVALID,
	LEFT,
	RIGHT,
	STRAIGHT
};

struct Corridor
{
	float m_fApproxLength;
	Corridor* m_pParentCorridor;
	DIRECTION m_eDirectionFromParent;

	Corridor()
		: m_fApproxLength(0), m_pParentCorridor(nullptr)
		, m_eDirectionFromParent(INVALID)
	{

	}
};

struct Room
{
	Room()
	{

	}
};


class BuildingData
{
public:

	BuildingData();
	~BuildingData();


	Corridor m_aCorridors[10];
	int m_iCurrentCorridor = 0;

private:


};


#endif

