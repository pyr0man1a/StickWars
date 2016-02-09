#pragma once
#include "TypeEnums.h"
#include <map>
#include "Unit.h"

typedef std::map<MobilityType, int> MoveCost;

class Terrain
{
	
private:
	const TerrainType m_TYPE;
	const int m_INCOME;
	const int m_defense;
	const MoveCost m_moveCost;
	CPlayer *m_owner;
	Unit *m_unit;


public:
	Terrain(TerrainType type, int income, int defense, MoveCost cost);
	~Terrain();

	TerrainType getType();
	int getIncome();

	Unit *getUnit();
	Unit *setUnit(Unit *unit);
	CPlayer *getOwner();
	void setOwner(CPlayer *owner);
	int getMoveCost(MobilityType type);
	int getDefense();
	bool canMove(Unit *unit);
	bool canBeCaptured();
};

