
#include "damageCalculator.h"
const int DamageCalculator::m_damage[UnitType::UnitTypeCount][UnitType::UnitTypeCount] =
{ { 55, 5, 10, 12, 45, 20, 45, 0, 0, 0, 30, 0, 0, 0, 0 },
{ 75, 55, 70, 85, 70, 85, 70, 0, 0, 0, 0, 8, 9, 9, 18 },
{ 90, 60, 75, 80, 85, 55, 65, 0, 0, 0, 0, 0, 55, 55, 65 },
{ 75, 8, 45, 35, 65, 55, 65, 0, 0, 0, 35, 0, 0, 0, 0 },
{ 65, 8, 15, 18, 55, 35, 55, 0, 0, 0, 35, 0, 0, 0, 0 },
{ 95, 70, 80, 90, 90, 85, 90, 0, 0, 0, 0, 55, 65, 65, 75 },
{ 65, 55, 70, 85, 55, 85, 55, 0, 0, 0, 35, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 55, 80, 65, 120, 0, 0, 0, 0 },
{ 55, 8, 15, 18, 45, 20, 45, 40, 55, 45, 90, 0, 0, 0, 0 },
{ 115, 105, 105, 105, 110, 105, 110, 0, 0, 0, 0, 85, 50, 95, 95 },
{ 75, 65, 70, 70, 70, 75, 70, 0, 0, 0, 0, 45, 65, 65, 75 },
{ 0, 0, 0, 0, 0, 0, 0, 105, 105, 105, 120, 38, 28, 95, 40 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 20, 55, 85, } };

//returns (Damage to Target, Return Damage)
std::pair<float, float> DamageCalculator::getDamage(Unit *unit, Unit *target){
	int baseDamage = m_damage[unit->getUnitType()][target->getUnitType()];
	int baseReturnDamage = m_damage[target->getUnitType()][unit->getUnitType()] / 2; //initiator takes half damage
	
	float damage = static_cast<float>(baseDamage*unit->getHealth()) / 100.0;
	float returnDamage = static_cast<float>(baseReturnDamage*target->getHealth()) / 100.0;

	return std::pair<float, float>(damage, returnDamage);

}



