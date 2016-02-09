#pragma once

#include "lib/cbasetypes.h"
#include <vector>
#include "Map.h"
#include "TypeEnums.h"
#include "Unit.h"

class DamageCalculator
{
private:
	static const int m_damage[UnitType::UnitTypeCount][UnitType::UnitTypeCount];


public:
	static std::pair<float, float> getDamage(Unit *attacking, Unit *defending);

};

