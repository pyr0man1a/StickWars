#pragma once

#include "lib/cbasetypes.h"
#include <utility>
#include <vector>
#include "Map.h"
#include "TypeEnums.h"
#include "TerrainBuilder.h"
#include "Unit.h"
#include "player.h"

class MapBuilder
{
private:
	uint8 m_width;
	uint8 m_height;
	uint8 m_mapID;
	TerrainMatrix m_terrain;
	UnitList m_unitList;
	PlayerList m_playerList;

public:
	MapBuilder(uint8 mapID, std::vector<CPlayer*> playerList);
	~MapBuilder();

	Map *getResult();

private:
	void buildMap01();
	void buildMap02();
	void buildMap03(); //demoMap
	void buildMap04(); //demoMap2?
	void addUnit(uint8 x, uint8 y, Unit *unit);
};

