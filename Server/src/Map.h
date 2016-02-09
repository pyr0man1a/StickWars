#pragma once

#define DEFAULT_WIDTH 16
#define DEFAULT_HEIGHT 16

#include "lib/cbasetypes.h"
#include <utility>
#include <vector>
#include "TypeEnums.h"
#include "Terrain.h"
#include "Unit.h"
#include "player.h"

typedef std::map<uint16, Unit*> UnitList;
typedef std::vector< std::vector<Terrain*> > TerrainMatrix;
typedef std::vector< CPlayer*> PlayerList;

class Map
{
private:
	const uint8 m_WIDTH;
	const uint8 m_HEIGHT;
	const uint8 m_mapID;
	const TerrainMatrix m_terrain;
	UnitList m_unitList;
	const PlayerList m_playerList;


	uint16 newUnitId(); //same as lobby's newLobbyId()

public:
	Map(uint8 mapID, uint8 width, uint8 height, TerrainMatrix terrain, UnitList unitList, PlayerList playerList);
	Map(uint8 mapID, TerrainMatrix terrain, UnitList unitList, PlayerList playerList);
	~Map();

	bool unitsRemain(CPlayer*);

	uint8 getMapID();
	uint8 getWidth();
	uint8 getHeight();

	Terrain* getTerrainAt(uint8 x, uint8 y);
	Terrain* getTerrainUnderUnit(uint16 id);
	TerrainType getTerrainTypeAt(uint8 x, uint8 y);

	std::pair<uint8, uint8> getUnitPos(uint16 id);
	Unit *getUnit(uint16 id);
	Unit *getUnitAt(uint8 x, uint8 y);

	Unit *produceUnit(uint8 x, uint8 y, CPlayer* owner, UnitType type);
	bool moveUnit(Unit* unit, uint8 new_x, uint8 new_y);
	bool attackUnit(Unit* unit, uint8 new_x, uint8 new_y, Unit* target, int* targetdamage, int* returndamage);
	bool deleteUnit(Unit* unit);
	bool captureStructure(uint8 x, uint8 y); 
	void turnChange(CPlayer* player);
};

