#include "test.h"

TestUnit::TestUnit(){
	m_allTestsPassed = false;
}

bool TestUnit::run()
{
	m_allTestsPassed = true;
	Unit *testUnit;
	for (int i = 0; i < UnitType::UnitTypeCount; i++)
	{
		bool currentTest;
		UnitBuilder *builder = new UnitBuilder(static_cast<UnitType>(i), 0, 0);
		testUnit = builder->getResult();
		assert(testUnit != NULL);

		switch (static_cast<UnitType>(i)){
		case UnitType::Infantry:
			currentTest = testInfantry(testUnit);
			break;
		case UnitType::Tank:
			currentTest = testTank(testUnit);
			break;
		case UnitType::Artillery:
			currentTest = testArtillery(testUnit);
			break;
		case UnitType::Recon:
			currentTest = testRecon(testUnit);
			break;
		case UnitType::Bike:
			currentTest = testBike(testUnit);
			break;
		case UnitType::Rockets:
			currentTest = testRockets(testUnit);
			break;
		case UnitType::Mech:
			currentTest = testMech(testUnit);
			break;
		case UnitType::Fighter:
			currentTest = testFighter(testUnit);
			break;
		case UnitType::Duster:
			currentTest = testDuster(testUnit);
			break;
		case UnitType::Bomber:
			currentTest = testBomber(testUnit);
			break;
		case UnitType::Transport_Copter:
			currentTest = testTransportCopter(testUnit);
			break;
		case UnitType::Battleship:
			currentTest = testBattleship(testUnit);
			break;
		case UnitType::Cruiser:
			currentTest = testCruiser(testUnit);
			break;
		case UnitType::Submarine:
			currentTest = testSubmarine(testUnit);
			break;
		case UnitType::Lander:
			currentTest = testLander(testUnit);
			break;
		case UnitType::Invalid:
			currentTest = (testUnit == NULL);
			break;
		default:
			currentTest = false;
			break;
		}
		currentTest = testGeneralUnit(testUnit);

		if (!currentTest)
			m_allTestsPassed = false;
	}
	return m_allTestsPassed;
}

bool TestUnit::testGeneralUnit(Unit *testUnit){
	assert(testUnit->getHealth() == MAX_HEALTH);
	assert(testUnit->isActive());
	assert(testUnit->getAmmo() == MAX_AMMO);
	assert(testUnit->getFuel() == MAX_FUEL);
	assert(!testUnit->isCapturing());
	return true;
}

bool TestUnit::testInfantry(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Infantry);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Foot);
	assert(testUnit->getMobility() == 3);
	assert(testUnit->getCost() == 1500);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 2);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::Bullet);
	return true;
}

bool TestUnit::testTank(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Tank);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Tread);
	assert(testUnit->getMobility() == 6);
	assert(testUnit->getCost() == 7000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 3);
	assert(testUnit->getArmor() == 2);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testArtillery(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Artillery);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Tread);
	assert(testUnit->getMobility() == 5);
	assert(testUnit->getCost() == 6000);
	assert(testUnit->getMinRange() == 2); 
	assert(testUnit->getMaxRange() == 3);
	assert(testUnit->getVision() == 3);
	assert(testUnit->getArmor() == 1);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testRecon(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Recon);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Tire);
	assert(testUnit->getMobility() == 8);
	assert(testUnit->getCost() == 4000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 5);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::Bullet);
	return true;
}

bool TestUnit::testBike(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Bike);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Tire);
	assert(testUnit->getMobility() == 5);
	assert(testUnit->getCost() == 2500);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 2);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::Bullet);
	return true;
}

bool TestUnit::testRockets(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Rockets);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Tire);
	assert(testUnit->getMobility() == 5);
	assert(testUnit->getCost() == 15000);
	assert(testUnit->getMinRange() == 3); 
	assert(testUnit->getMaxRange() == 5);
	assert(testUnit->getVision() == 3);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testMech(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Mech);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Foot);
	assert(testUnit->getMobility() == 2);
	assert(testUnit->getCost() == 2500);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 2);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testFighter(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Fighter);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Air);
	assert(testUnit->getMobility() == 9);
	assert(testUnit->getCost() == 20000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 5);
	assert(testUnit->getArmor() == 2);
	assert(testUnit->getDamageType() == DamageType::Bullet);
	return true;
}

bool TestUnit::testDuster(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Duster);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Air);
	assert(testUnit->getMobility() == 8);
	assert(testUnit->getCost() == 13000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 4);
	assert(testUnit->getArmor() == 1);
	assert(testUnit->getDamageType() == DamageType::Bullet);
	return true;
}

bool TestUnit::testBomber(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Bomber);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Air);
	assert(testUnit->getMobility() == 7);
	assert(testUnit->getCost() == 20000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 3);
	assert(testUnit->getArmor() == 2);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testTransportCopter(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Transport_Copter);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Air);
	assert(testUnit->getMobility() == 6);
	assert(testUnit->getCost() == 5000);
	assert(testUnit->getMinRange() == 0); 
	assert(testUnit->getMaxRange() == 0);
	assert(testUnit->getVision() == 1);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::NoDamage);
	return true;
}

bool TestUnit::testBattleship(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Battleship);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Boat);
	assert(testUnit->getMobility() == 5);
	assert(testUnit->getCost() == 25000);
	assert(testUnit->getMinRange() == 3);
	assert(testUnit->getMaxRange() == 5);
	assert(testUnit->getVision() == 5);
	assert(testUnit->getArmor() == 2);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testCruiser(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Cruiser);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Boat);
	assert(testUnit->getMobility() == 6);
	assert(testUnit->getCost() == 16000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 5);
	assert(testUnit->getArmor() == 1);
	assert(testUnit->getDamageType() == DamageType::Bullet);
	return true;
}

bool TestUnit::testSubmarine(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Submarine);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Boat);
	assert(testUnit->getMobility() == 6);
	assert(testUnit->getCost() == 20000);
	assert(testUnit->getMinRange() == 1); 
	assert(testUnit->getMaxRange() == 1);
	assert(testUnit->getVision() == 5);
	assert(testUnit->getArmor() == 1);
	assert(testUnit->getDamageType() == DamageType::Concussive);
	return true;
}

bool TestUnit::testLander(Unit *testUnit){
	assert(testUnit->getUnitType() == UnitType::Lander);
	assert(testUnit->getOwner() == 0);
	assert(testUnit->getMobilityType() == MobilityType::Boat);
	assert(testUnit->getMobility() == 6);
	assert(testUnit->getCost() == 10000);
	assert(testUnit->getMinRange() == 0); 
	assert(testUnit->getMaxRange() == 0);
	assert(testUnit->getVision() == 1);
	assert(testUnit->getArmor() == 0);
	assert(testUnit->getDamageType() == DamageType::NoDamage);
	return true;
}