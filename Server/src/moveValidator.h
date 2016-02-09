#pragma once

#include <vector>
#include "Map.h"
#include "TypeEnums.h"
#include "Terrain.h"
#include "Unit.h"

typedef std::pair<int, int> Coordinate;
typedef std::vector< Coordinate > CoordinateList;

class MoveValidator
{

public:
	static bool isMoveValid(int old_x, int old_y, int new_x, int new_y, Unit *unit, Map *map);
	static bool isAttackValid(int old_x, int old_y, int new_x, int new_y, Unit *unit, Unit *target, Map *map);
	static CoordinateList getValidLocations(int x, int y, Unit *unit, Map *gameMap);
	static CoordinateList getNeighbours(int x, int y, Unit *unit, Map *map);
	static CoordinateList getAttackableCoordinates(int x, int y, Unit *unit, Map *map);
	static CoordinateList getAttackableNeighbours(Coordinate pos, Unit *unit, Map *map);
	static bool isNeighbour(Coordinate a, Coordinate b);

};

