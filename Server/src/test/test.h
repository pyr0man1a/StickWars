#include <iostream>
#include "../server.h"
#include "../lib/showmsg.h"
#include "../lib/cbasetypes.h"
#include "../TypeEnums.h"
#include "../Unit.h"
#include "../Terrain.h"
#include "../UnitBuilder.h"
#include "../TerrainBuilder.h"
#include "../Map.h"

class Test
{
public:
	static void run();
};

class TestUnit
{
public:
	TestUnit();
	~TestUnit();

	bool run();
	
private:
	bool m_allTestsPassed;

	bool testGeneralUnit(Unit *testUnit);
	bool testInfantry(Unit *testUnit);
	bool testTank(Unit *testUnit);
	bool testArtillery(Unit *testUnit);
	bool testRecon(Unit *testUnit);
	bool testBike(Unit *testUnit);
	bool testRockets(Unit *testUnit);
	bool testMech(Unit *testUnit);
	bool testFighter(Unit *testUnit);
	bool testDuster(Unit *testUnit);
	bool testBomber(Unit *testUnit);
	bool testTransportCopter(Unit *testUnit);
	bool testBattleship(Unit *testUnit);
	bool testCruiser(Unit *testUnit);
	bool testSubmarine(Unit *testUnit);
	bool testLander(Unit *testUnit);
};

class TestTerrain
{
public:
	TestTerrain();
	~TestTerrain();

	bool run();

private:
	bool m_allTestsPassed;

	bool testGeneralTerrain(Terrain *testTerrain);
	bool testPlain(Terrain *testTerrain);
	bool testMountain(Terrain *testTerrain);
	bool testRoad(Terrain *testTerrain);
	bool testSea(Terrain *testTerrain);
	bool testWood(Terrain *testTerrain);
	bool testHQ(Terrain *testTerrain);
	bool testFactory(Terrain *testTerrain);
	bool testCity(Terrain *testTerrain);
	bool testAirport(Terrain *testTerrain);
};

class TestMap{
public:
	TestMap();
	~TestMap();

	bool run();

private:
	bool m_allTestsPassed;

};