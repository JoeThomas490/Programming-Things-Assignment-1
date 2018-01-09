#include "BuildingData.h"

BuildingData::BuildingData()
{
}

BuildingData::~BuildingData()
{
}

Corridor * BuildingData::GetParentCorridor(Corridor * mChildCorridor)
{
	if (mChildCorridor->m_pParentCorridor == nullptr)
	{
		return nullptr;
	}
	else
	{
		return &m_aCorridors[mChildCorridor->m_pParentCorridor->ID];
	}
}
