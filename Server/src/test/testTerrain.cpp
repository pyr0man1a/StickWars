#include "test.h"

TestTerrain::TestTerrain(){
	m_allTestsPassed = false;
}

bool TestTerrain::run()
{
	m_allTestsPassed = true;
	Terrain *testTerrain;
	for (int i = 0; i < TerrainType::TerrainTypeCount; i++)
	{
		bool currentTest;
		TerrainBuilder *builder = new TerrainBuilder(static_cast<TerrainType>(i));
		testTerrain = builder->getResult();
		assert(testTerrain != NULL);

		switch (static_cast<TerrainType>(i)){
		case TerrainType::Plain:
			currentTest = testPlain(testTerrain);
			break;
		case TerrainType::Mountain:
			currentTest = testMountain(testTerrain);
			break;
		case TerrainType::Road:
			currentTest = testRoad(testTerrain);
			break;
		case TerrainType::Sea:
			currentTest = testSea(testTerrain);
			break;
		case TerrainType::Wood:
			currentTest = testWood(testTerrain);
			break;
		case TerrainType::HQ:
			currentTest = testHQ(testTerrain);
			break;
		case TerrainType::Factory:
			currentTest = testFactory(testTerrain);
			break;
		case TerrainType::City:
			currentTest = testCity(testTerrain);
			break;
		case TerrainType::Airport:
			currentTest = testAirport(testTerrain);
			break;
		case TerrainType::Error:
			currentTest = (testTerrain == NULL);
			break; 
		default:
			currentTest = false;
			break;
		
		}
		currentTest = testGeneralTerrain(testTerrain);

		if (!currentTest)
			m_allTestsPassed = false;
	}
	return m_allTestsPassed;
}

bool TestTerrain::testGeneralTerrain(Terrain *testTerrain){
	assert(testTerrain->getOwner() == NULL);
	assert(testTerrain->getUnit() == NULL);
	return true;
}

bool TestTerrain::testPlain(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::Plain);
	assert(testTerrain->getIncome() == 0);
	assert(testTerrain->getDefense() == 1);
	assert(testTerrain->getMoveCost(MobilityType::Foot) == 1);
	assert(testTerrain->getMoveCost(MobilityType::Tread) == 1);
	assert(testTerrain->getMoveCost(MobilityType::Tire) == 2);
	return true;
}

bool TestTerrain::testMountain(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::Mountain);
	assert(testTerrain->getIncome() == 0);
	assert(testTerrain->getDefense() == 4);
	assert(testTerrain->getMoveCost(MobilityType::Foot) == 2);
	return true;
}

bool TestTerrain::testRoad(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::Road);
	assert(testTerrain->getIncome() == 0);
	assert(testTerrain->getDefense() == 0);
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		assert(testTerrain->getMoveCost(static_cast<MobilityType>(i)) == 1);
	return true;
}

bool TestTerrain::testSea(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::Sea);
	assert(testTerrain->getIncome() == 0);
	assert(testTerrain->getDefense() == 0);
	assert(testTerrain->getMoveCost(MobilityType::Boat) == 1);
	return true;
}

bool TestTerrain::testWood(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::Wood);
	assert(testTerrain->getIncome() == 0);
	assert(testTerrain->getDefense() == 3);
	assert(testTerrain->getMoveCost(MobilityType::Foot) == 1);
	assert(testTerrain->getMoveCost(MobilityType::Tread) == 2);
	assert(testTerrain->getMoveCost(MobilityType::Tire) == 3);
	return true;
}

bool TestTerrain::testHQ(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::HQ);
	assert(testTerrain->getIncome() == 1000);
	assert(testTerrain->getDefense() == 4);
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		assert(testTerrain->getMoveCost(static_cast<MobilityType>(i)) == 1);
	return true;
}

bool TestTerrain::testFactory(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::Factory);
	assert(testTerrain->getIncome() == 1000);
	assert(testTerrain->getDefense() == 3);
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		assert(testTerrain->getMoveCost(static_cast<MobilityType>(i)) == 1);
	return true;
}

bool TestTerrain::testCity(Terrain * testTerrain){
	assert(testTerrain->getType() == TerrainType::City);
	assert(testTerrain->getIncome() == 1000);
	assert(testTerrain->getDefense() == 2);
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		assert(testTerrain->getMoveCost(static_cast<MobilityType>(i)) == 1);
	return true;
}

bool TestTerrain::testAirport(Terrain * testTerrain){
	// Not Implemented
	return true;
}