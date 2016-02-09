#include "MapBuilder.h"
#include "UnitBuilder.h"

Map *MapBuilder::getResult(){
	return new Map(m_mapID, m_width, m_height, m_terrain, m_unitList, m_playerList);
}

MapBuilder::MapBuilder(uint8 mapID, std::vector<CPlayer*> playerList){
	m_mapID = mapID;
	m_playerList = playerList;

	switch (mapID){
	case 1:
		buildMap01();
		break;
	case 2:
		buildMap02();
		break;
	case 3:
		buildMap03();
		break;
	case 4:
	default:
		buildMap01();
		break;
	}
}

void MapBuilder::buildMap01(){
	TerrainBuilder plainBuilder(TerrainType::Plain);

	//Fill with plain
	for (int i = 0; i < 16; i++)
	{
		std::vector<Terrain*> row;
		for (int j = 0; j < 16; j++)
		{
			row.push_back(plainBuilder.getResult());
		}
		m_terrain.push_back(row);
	}

	TerrainBuilder factoryBuilder(TerrainType::Factory);
	delete m_terrain[0][0];
	m_terrain[0][0] = factoryBuilder.getResult();
	m_terrain[0][0]->setOwner(m_playerList[0]);
	delete m_terrain[15][15];
	m_terrain[15][15] = factoryBuilder.getResult();
	m_terrain[15][15]->setOwner(m_playerList[1]);

	// Add a unit for each player.
	addUnit(0, 0, (new UnitBuilder(UnitType::Infantry, m_playerList[0], 1))->getResult());
	addUnit(15, 15, (new UnitBuilder(UnitType::Infantry, m_playerList[1], 2))->getResult());

}

void MapBuilder::buildMap02(){
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			// Loop through all the coordinates
			if ((i == 0 && j == 0) || (i == 2 && j == 0) || (i == 0 && j == 2))	{
				// Player 1's factory.
				Terrain *playerOneFactory = (new TerrainBuilder(TerrainType::Factory))->getResult();
				m_terrain[i][j] = playerOneFactory;
				m_terrain[i][j]->setOwner(m_playerList[0]);
			}
			else if ((i == 15 && j == 15) || (i == 13 && j == 15) || (i == 15 && j == 13)){
				// Player 2's factory.
				Terrain *playerTwoFactory = (new TerrainBuilder(TerrainType::Factory))->getResult();
				m_terrain[i][j] = playerTwoFactory;
				m_terrain[i][j]->setOwner(m_playerList[1]);
			}
			else if ((i == 3 || i == 11) && (j > 3 && j < 11)){
				// Fill with mountain.
				Terrain *mountainTerrain = (new TerrainBuilder(TerrainType::Mountain))->getResult();
				m_terrain[i][j] = mountainTerrain;
			}
			else if ((i > 3 && i < 11) && (j > 3 && j < 11)){
				// Fill with wood.
				Terrain *woodTerrain = (new TerrainBuilder(TerrainType::Wood))->getResult();
				m_terrain[i][j] = woodTerrain;
			}
			else{
				// Fill with plain.
				Terrain *plainTerrain = (new TerrainBuilder(TerrainType::Plain))->getResult();
				m_terrain[i][j] = plainTerrain;
			}
		}
	}
	// Add a unit for each player.
	addUnit(0, 0, (new UnitBuilder(UnitType::Infantry, m_playerList[0], 1))->getResult());
	addUnit(15, 15, (new UnitBuilder(UnitType::Infantry, m_playerList[1], 2))->getResult());
}

// DemoMap
// same as map02 but with units placed at 
// pre-determined locations for demo
void MapBuilder::buildMap03(){
	buildMap02();

	//delete players units at 0,0 and 15,15
	Unit *unit1 = m_terrain[0][0]->getUnit();
	m_terrain[0][0]->setUnit(NULL);
	m_unitList.erase(1);
	delete unit1;
	Unit *unit2 = m_terrain[15][15]->getUnit();
	m_terrain[15][15]->setUnit(NULL);
	m_unitList.erase(2);
	delete unit2;

	addUnit(5, 4, (new UnitBuilder(UnitType::Infantry, m_playerList[0], 1))->getResult());
	addUnit(7, 6, (new UnitBuilder(UnitType::Infantry, m_playerList[1], 2))->getResult());
	addUnit(9, 3, (new UnitBuilder(UnitType::Tank, m_playerList[0], 3))->getResult());
	addUnit(2, 7, (new UnitBuilder(UnitType::Infantry, m_playerList[0], 4))->getResult());
}

//demoMap2?
void MapBuilder::buildMap04(){
	//not implemented
}

void MapBuilder::addUnit(uint8 x, uint8 y, Unit *unit){
	m_unitList[unit->getID()] = unit;
	m_terrain[x][y]->setUnit(unit);
}