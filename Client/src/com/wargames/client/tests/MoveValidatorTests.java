package com.wargames.client.tests;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

import com.wargames.client.helpers.MoveValidator;
import com.wargames.client.model.*;
import com.wargames.client.helpers.*;

public class MoveValidatorTests {
	private Player player1;
	private Player player2;
	private Map gameMap;
	
	
	@Before
	public void setUp() throws Exception {
		player1 = new Player(0, "Clinton", 1, 1, "red");
		player2 = new Player(1, "Jesus", 2, 2, "blue");
		gameMap = MapGenerator.generateMap01(player1, player2);
	}

	@Test
	public void testMoveValidator() {
		Unit unit = Unit.createSoldier(player1);
		System.out.println("Soldier's mobility: " + unit.getMobility());
		ArrayList<Coordinate> validMoves = MoveValidator.validLocations(0, 0, unit, gameMap);
		for(Coordinate validCoordinate : validMoves)
		{
			System.out.println("Soldier can move to: (" + validCoordinate.x + "," + validCoordinate.y + ")");
		}
	}

}
