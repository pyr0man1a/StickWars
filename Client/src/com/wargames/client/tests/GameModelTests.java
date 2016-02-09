package com.wargames.client.tests;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.wargames.client.model.*;

public class GameModelTests {

	private Game testGame;
	private Map gameMap;
	private Player player1;
	private Player player2;
	
	@Before
	public void setUp() throws Exception {
		player1 = new Player(0, "Clinton", 1, 1, "red");
		player2 = new Player(1, "Jesus", 2, 2, "blue");
		gameMap = MapGenerator.generateMap01(player1, player2);
		testGame = new Game(gameMap, true);
	}

	@Test
	public void ConstructorTests() {
		assertEquals(testGame.gameMap.players.size(), 2);
		assertEquals(testGame.gameMap, gameMap);
		assertEquals(testGame.currentTurn, player1);
	}
	
	@Test
	public void UnitSpawnTests() {
		// Spawn a unit for player 1.
		// Player 1's factory is at (0,0)
		testGame.createUnit(0, 0, UnitType.SOLDIER, player1);
		assertFalse(testGame.gameMap.getUnitAt(0,0) == null);
		Unit player1createdUnit = testGame.gameMap.getUnitAt(0, 0);
		assertEquals(player1createdUnit.getOwner(), player1);
		assertEquals(player1createdUnit.health, 10);
		assertEquals(player1createdUnit.getMobility(), 3);
		
		// Spawn a unit for player 2.
		// Player 2's factory is at (15,15)
		testGame.createUnit(15, 15, UnitType.SOLDIER, player2);
		assertFalse(testGame.gameMap.getUnitAt(15,15) == null);
		Unit player2createdUnit = testGame.gameMap.getUnitAt(0, 0);
		assertEquals(player2createdUnit.getOwner(), player1);
		assertEquals(player2createdUnit.health, 10);
		assertEquals(player2createdUnit.getMobility(), 3);
	}
	
	@Test
	public void UnitMovementTests() {
		// Spawn a unit for player 1.
		// Player 1's factory is at (0,0)
		testGame.createUnit(0, 0, UnitType.SOLDIER, player1);
		assertFalse(testGame.gameMap.getUnitAt(0,0) == null);
		Unit player1createdUnit = testGame.gameMap.getUnitAt(0, 0);
		assertEquals(player1createdUnit.getOwner(), player1);
		
		testGame.moveUnit(0, 0, 1, 1);
	}
}
