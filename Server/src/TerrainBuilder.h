#pragma once

#include "lib/cbasetypes.h"

#include "TypeEnums.h"
#include "Terrain.h"
class TerrainBuilder
{
private:
	TerrainType m_type;
	int m_income;
	int m_defense;
	MoveCost m_moveCost;

public:
	TerrainBuilder(TerrainType type);
	~TerrainBuilder();
	Terrain *getResult();

private:
	uint8 setOwner();
	void buildPlain();
	void buildMountain();
	void buildRoad();
	void buildSea();
	void buildWood();
	void buildHQ();
	void buildFactory();
	void buildCity();
	void buildAirport();
};

