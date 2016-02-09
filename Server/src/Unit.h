#pragma once
#include "lib/cbasetypes.h"
#include "TypeEnums.h"

#define MAX_HEALTH 10
#define MAX_AMMO 20
#define MAX_FUEL 100

class CPlayer;
class Unit
{
private:
	const uint16 m_id;
	const UnitType m_UNIT_TYPE;
	CPlayer* m_OWNER;
	const MobilityType m_MOBILITY_TYPE;
	const int m_MOBILITY;
	const int m_COST;
	const int m_RANGE;
	const int m_VISION;
	bool m_active;
	int m_health;
	int m_ammo;
	int m_armor;
	int m_fuel;
	int m_damage;
	DamageType m_damageType;
	bool m_capturing;
	
public:
	void updateIncome(int amount);

	Unit(UnitType type, CPlayer* owner, MobilityType mType, int mobility, int cost, int range, int vision, int id);
	~Unit();

	uint16 getID();
	UnitType getUnitType();
	CPlayer* getOwner();
	MobilityType getMobilityType();
	int getMobility();
	int getCost();
	int getMaxRange();
	int getMinRange();
	int getVision();
	bool isActive();
	bool activate();
	bool deactivate();
	int getHealth();
	void damageUnit(int damage);
	bool capture();
	void cancelCapture();
	bool isCapturing();
	void decreaseAmmo(int ammo);
	void increaseAmmo(int ammo);
	int getAmmo();
	int getArmor();
	void decreaseFuel(int fuel);
	void increaseFuel(int fuel);
	int getFuel();
	void setDamage(int damage);
	int getDamage();
	void setDamageType(DamageType type);
	DamageType getDamageType();
	void setArmor(int armor);
};

