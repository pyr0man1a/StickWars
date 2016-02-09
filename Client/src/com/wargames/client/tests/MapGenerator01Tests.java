package com.wargames.client.tests;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import com.wargames.client.model.*;

public class MapGenerator01Tests {

	private Map TestMap;
	private Player player1;
	private Player player2;
	
	@Before
	public void setUp() throws Exception {
		player1 = new Player(0, "Clinton", 1, 0, "red");
		player2 = new Player(1, "Jesus", 2, 1, "blue");
		TestMap = MapGenerator.generateMap01(player1, player2);
	}

	/**
	 * Tests that the initial map is OK.
	 */
	@Test
	public void testGeneratorInit() {
		assertEquals(TestMap.getHeight(), 16);
		assertEquals(TestMap.getWidth(), 16);
		
		Structure playerOneFactory = (Structure) TestMap.getTerrainAt(0,0);
		Structure playerTwoFactory = (Structure) TestMap.getTerrainAt(15,15);
		assertEquals(playerOneFactory.terrainType, TerrainType.Factory);
		assertEquals(playerOneFactory.owner, player1);
		
		assertEquals(playerTwoFactory.terrainType, TerrainType.Factory);
		assertEquals(playerTwoFactory.owner, player2);
		
		for(int i = 0; i < TestMap.getWidth(); i++)
		{
			for(int j = 0; j < TestMap.getHeight(); j++)
			{
				if((i == 0 && j == 0) || (i == 15 && j == 15))
				{
					assertEquals(TestMap.getTerrainAt(i, j).terrainType, TerrainType.Factory);
				}
				else
				{
					assertEquals(TestMap.getTerrainAt(i, j).terrainType, TerrainType.Plain);
				}
			}
		}
	}

}
