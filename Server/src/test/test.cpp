#include "test.h"


void Test::run(){
	ShowInfo(CL_CYAN"Running WarGames Server Model Test"CL_RESET"\n");

	bool allTestsPassed = true;
	TestUnit *testUnits = new TestUnit();
	TestTerrain *testTerrain = new TestTerrain();
	TestMap *testMap = new TestMap();

	ShowStatus("Testing Unit Creation\n");
	if (!testUnits->run())
		allTestsPassed = false;

	ShowStatus("Testing Terrain Creation\n");
	if (!testTerrain->run())
		allTestsPassed = false;
	
	ShowStatus("Testing Map Creation\n");
	if (!testTerrain->run())
		allTestsPassed = false;

	if (allTestsPassed)
		ShowInfo(CL_CYAN"All Tests Passed"CL_RESET"\n\nPress enter to exit test.\n");
	else
		ShowInfo(CL_CYAN"Test(s) Failed"CL_RESET"\n\nPress enter to exit test.\n");

	char c = getchar();
	std::cout << "\n";
}