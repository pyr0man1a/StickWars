
#include "damageCalculator.h"
#include "Map.h"
#include "moveValidator.h"
#include "Terrain.h"
#include "TerrainBuilder.h"
#include "UnitBuilder.h"
#include "player.h"

Map::Map(uint8 width, uint8 height, uint8 mapID, TerrainMatrix terrain, UnitList unitList, PlayerList playerList):
m_mapID(mapID),
m_HEIGHT(height),
m_WIDTH(width),
m_terrain(terrain),
m_unitList(unitList),
m_playerList(playerList)
{
}

Map::Map(uint8 mapID, TerrainMatrix terrain, UnitList unitList, PlayerList playerList):
m_mapID(mapID),
m_HEIGHT(DEFAULT_HEIGHT),
m_WIDTH(DEFAULT_WIDTH),
m_terrain(terrain),
m_unitList(unitList),
m_playerList(playerList)
{
}

Map::~Map(){
}

uint16 Map::newUnitId()
{
	uint32 unitId = 1;
	for (uint32 i = 0; i < m_unitList.size(); i++)
	{
		if (m_unitList.at(i)->getID() == unitId)
		{
			unitId++;
			i = 0;
		}
	}
	return unitId;
}

uint8 Map::getMapID(){
	return m_mapID;
}

uint8 Map::getWidth(){
	return m_WIDTH;
}

uint8 Map::getHeight(){
	return m_HEIGHT;
}

Terrain* Map::getTerrainAt(uint8 x, uint8 y){
	return m_terrain[x][y];
}

Terrain* Map::getTerrainUnderUnit(uint16 id)
{
	for (int i = 0; i < m_WIDTH; i++)
	{
		for (int j = 0; j < m_HEIGHT; j++)
		{
			if (m_terrain[i][j]->getUnit() && m_terrain[i][j]->getUnit()->getID() == id)
			{
				return m_terrain[i][j];
			}
		}
	}
	return NULL;
}

TerrainType Map::getTerrainTypeAt(uint8 x, uint8 y){
	return m_terrain[x][y]->getType();
}

std::pair<uint8, uint8> Map::getUnitPos(uint16 id){
	for (int i = 0; i < m_WIDTH; i++){
		for (int j = 0; j < m_HEIGHT; j++){
			if (m_terrain[i][j]->getUnit() && m_terrain[i][j]->getUnit()->getID() == id){
				return std::pair<uint8, uint8>(i, j);
			}
		}
	}
	return std::pair<uint8, uint8>(-1, -1);
}

Unit* Map::getUnit(uint16 id){
	return m_unitList.find(id)->second;
}

Unit* Map::getUnitAt(uint8 x, uint8 y){
	return m_terrain[x][y]->getUnit();
}

Unit* Map::produceUnit(uint8 x, uint8 y, CPlayer* owner, UnitType type)
{
	Terrain* pos = getTerrainAt(x, y);
	if (pos->getUnit() == NULL)
	{
		UnitBuilder builder(type, owner, newUnitId());
		Unit* newUnit = builder.getResult();

		//Add unit to map
		m_terrain[x][y]->setUnit(newUnit);

		//Add unit to unit list
		m_unitList[newUnit->getID()] = newUnit;
		return newUnit;
	}
	return NULL;
}

//returns false if move is invalid or destination is occupied
bool Map::moveUnit(Unit* unit, uint8 new_x, uint8 new_y)
{
	//ensure unit can move onto newPos
	Coordinate unitPos = getUnitPos(unit->getID());
	if (!unit->isActive() || !MoveValidator::isMoveValid(unitPos.first, unitPos.second, new_x, new_y, unit, this)){
		return false;
	}

	Terrain* newTerrain = getTerrainAt(new_x, new_y);
	if (newTerrain->getUnit() == unit){
		return true;
	}
	//todo: implement fuel (not yet implemented on client)
	else if (newTerrain->setUnit(unit) == unit){
		if (unit->isCapturing()){
			unit->cancelCapture();
		}
		return true;
	}
	return false;
}

//new_x and new_y are the location the attacking unit is moving to
//returns true if attack was successful
bool Map::attackUnit(Unit* unit, uint8 new_x, uint8 new_y, Unit* target, int* targetDamage, int* returnDamage)
{
	Coordinate unitPos = this->getUnitPos(unit->getID());
	if (!unit->isActive() || !MoveValidator::isAttackValid(unitPos.first, unitPos.second, new_x, new_y, unit, target, this)){
		return false;
	}
	
	if (moveUnit(unit, new_x, new_y)) 
  	{
		//TODO: ammo check
		std::pair<float, float> damage = DamageCalculator::getDamage(unit, target);
		*targetDamage = static_cast<int>(damage.first);
		*returnDamage = static_cast<int>(damage.second);
		target->damageUnit(*targetDamage);
		unit->damageUnit(*returnDamage);
		unit->deactivate();
		if (target->getHealth() <= 0)
		{
			deleteUnit(target);
		}
		if (unit->getHealth() <= 0)
		{
			deleteUnit(unit);
		}
		return true;
	}
	return false;
}

bool Map::deleteUnit(Unit* unit)
{
	Terrain* pos = getTerrainUnderUnit(unit->getID());

	m_unitList.erase(unit->getID());
	pos->setUnit(NULL);
	delete unit;
	return true;
}

bool Map::unitsRemain(CPlayer* player)
{
	for (auto u : m_unitList)
	{
		if (u.second->getOwner() == player)
		{
			return true;
		}
	}
	return false;
}

//returns true if captured, false otherwise
bool Map::captureStructure(uint8 x, uint8 y){
	Unit *unit = getUnitAt(x, y);
	Terrain *captureTerrain = getTerrainAt(x, y);
	if (!unit->isActive() || !captureTerrain->canBeCaptured()){
		return false;
	}

	bool captured = unit->capture();
	unit->deactivate();

	//Set owner if captured
	if (captured){
		m_terrain[x][y]->setOwner(unit->getOwner());
	}
	return captured;
}

void Map::turnChange(CPlayer* player){
	for (auto u : m_unitList){
		if (u.second->getOwner() == player){
			u.second->activate();
		}else{
			u.second->deactivate();
		}
	}
}