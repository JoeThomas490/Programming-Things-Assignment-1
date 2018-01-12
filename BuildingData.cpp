#include "BuildingData.h"

BuildingData::BuildingData()
{
}

BuildingData::~BuildingData()
{
}

//Get the parent corridor attached to a corridor
//Parameters:
//1. Corridor to get the parent from
//Return:
//Pointer to parent corridor
Corridor * BuildingData::GetParentCorridor(Corridor * mChildCorridor)
{
	//Check if the corridor has a parent
	if (mChildCorridor->m_pParentCorridor == nullptr)
	{
		//If not return a nullptr
		return nullptr;
	}
	else
	{
		//Otherwise get the corridor out of the list using it's ID
		return &m_aCorridors[mChildCorridor->m_pParentCorridor->ID];
	}
}

//Gets the previous corridor in the list
//Return:
//Pointer to previous corridor
Corridor * BuildingData::PreviousCorridor()
{
	//Check that we aren't on the first corridor
	if (m_iCurrentCorridor < 0)
	{
		//Return reference to the previous corridor in the vector
		return &m_aCorridors[m_iCurrentCorridor - 1];
	}

	return nullptr;
}

//Adds a corridor to the vector of corridors
//Parameters:
//1.Direction from parent corridor
//2.Pointer to parent corridor
void BuildingData::AddCorridor(DIRECTION mDirection, Corridor * mpParentCorridor)
{
	//Increment the current corridor we're on
	m_iCurrentCorridor++;

	//Create a new corridor object
	Corridor newCorridor;
	
	//Set the direction
	newCorridor.m_eDirectionFromParent = mDirection;
	//Set the parent corridor
	newCorridor.m_pParentCorridor = mpParentCorridor;


	//Set the ID of the corridor
	static int idCounter = 1;
	newCorridor.ID = idCounter;
	idCounter++;

	//Push the new corridor into the array
	m_aCorridors[m_iCurrentCorridor] = newCorridor;
}
