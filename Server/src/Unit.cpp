#include "Unit.h"
#include "UnitBuilder.h"


Unit::Unit(UnitType type, CPlayer* owner, MobilityType mType, int mobility, int cost, int range, int vision, int id):
m_UNIT_TYPE(type),
m_OWNER(owner),
m_MOBILITY_TYPE(mType),
m_MOBILITY(mobility),
m_COST(cost),
m_RANGE(range),
m_VISION(vision),
m_id(id)
{
	m_active = true;
	m_health = MAX_HEALTH;
	m_ammo = MAX_AMMO;
	m_armor = 0;
	m_fuel = MAX_FUEL;
	m_capturing = false;
}

Unit::~Unit()
{
}

uint16 Unit::getID(){
	return this->m_id;
}

UnitType Unit::getUnitType(){
	return this->m_UNIT_TYPE;
}	

CPlayer* Unit::getOwner(){
	return this->m_OWNER;
}

MobilityType Unit::getMobilityType(){
	return this->m_MOBILITY_TYPE;
}

int Unit::getMobility(){
	return this->m_MOBILITY;
}
int Unit::getCost(){
	return this->m_COST;
}

//Range is either stored as a single int for 
//units who can only attack one space away
//for ranged attacks, a 2-digit representation
//of the form (MIN,MAX) is stored as a decimal 
//value. ie m_RANGE = 23 means a unit can attack
//2 or 3 spaces away from itself - no closer or
//farther attacks will be allwoed.
int Unit::getMaxRange(){
	if (m_RANGE > 1)
		return (m_RANGE % 10);
	else return m_RANGE;
}

int Unit::getMinRange(){
	if (m_RANGE > 1)
		return (m_RANGE / 10);
	else return m_RANGE;
}

int Unit::getVision(){
	return this->m_VISION;
}

bool Unit::isActive(){
	return this->m_active;
}

bool Unit::activate(){
	return this->m_active = true;
}

bool Unit::deactivate(){
	return this->m_active = false;
}

int Unit::getHealth(){
	return this->m_health;
}

void Unit::damageUnit(int damage){
	if (damage > m_health){
		m_health = 0;
	}
	else{
		this->m_health -= damage;
	}
}

// returns true if unit has captured the current position,
// and false if the unit just started capturing
bool Unit::capture(){
	if (this->m_capturing == false){
		//unit has started capturing this position
		this->m_capturing = true;
		return false;
	}
	else{
		//unit previously started capturing this position
		this->m_capturing = false;
		return true;
	}
}

void Unit::cancelCapture(){
	this->m_capturing = false;
}

bool Unit::isCapturing(){
	return this->m_capturing;
}

void Unit::decreaseAmmo(int ammo){
	this->m_ammo -= ammo;
}

void Unit::increaseAmmo(int ammo){
	this->m_ammo += ammo;
}

int Unit::getAmmo(){
	return this->m_ammo;
}
void Unit::decreaseFuel(int fuel){
	this->m_fuel -= fuel;
}

void Unit::increaseFuel(int fuel){
	this->m_fuel += fuel;
}

int Unit::getFuel(){
	return this->m_fuel;
}

int Unit::getArmor(){
	return this->m_armor;
}

void Unit::setDamage(int damage)
{
	m_damage = damage;
}
int Unit::getDamage()
{
	return m_damage;
}
void Unit::setDamageType(DamageType type)
{
	m_damageType = type;
}
DamageType Unit::getDamageType()
{
	return m_damageType;
}
void Unit::setArmor(int armor)
{
	m_armor = armor;
}

