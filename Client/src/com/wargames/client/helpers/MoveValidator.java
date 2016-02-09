package com.wargames.client.helpers;

import java.util.ArrayList;

import com.wargames.client.model.*;

public class MoveValidator {

	public static boolean isMoveValid(int startX, int startY, int destX, int destY, Unit unit, Map gameMap)
	{
		return false;
	}
		
	public static ArrayList<Coordinate> validLocations(int startX, int startY, Unit unit, Map gameMap)
	{
		ArrayList<Coordinate> validLocations = new ArrayList<Coordinate>();
		// Maximum possible area to move in one direction is based on mobility.
		int remainingMobility = unit.getMobility();
		Coordinate beginningCoord = new Coordinate(startX, startY);
		validLocations.add(beginningCoord);

		while(remainingMobility > 0)
		{
			ArrayList<Coordinate> neighbours = new ArrayList<Coordinate>();
			for(Coordinate validCoord : validLocations)
			{
				ArrayList<Coordinate> potentialNeighbours = getNeighbours(validCoord.x, validCoord.y, unit, gameMap);
				for(Coordinate potentialNeighbour : potentialNeighbours)
				{
					if(!validLocations.contains(potentialNeighbour))
					{
						neighbours.add(potentialNeighbour);
					}
				}
			}
			for(Coordinate neighbourCoord : neighbours)
			{
				if(!validLocations.contains(neighbourCoord))
				{
					Terrain associatedTerrain = gameMap.getTerrainAt(neighbourCoord.x, neighbourCoord.y);
					if(associatedTerrain.canMove(unit))
					{
						// Unit can potentially move onto this square, let's see if it has enough mobility to get onto the square
						int moveCost = associatedTerrain.getMoveCost(unit);
						if(remainingMobility >= moveCost)
						{
							// Unit can move onto this square.
							// Check if it's occupied.
							if(gameMap.getUnitAt(neighbourCoord.x, neighbourCoord.y) == null)
							{
								// Unoccupied. Add it to the list.
								validLocations.add(neighbourCoord);
							}
							
						}
					}
				}
				
			}
			
			remainingMobility = remainingMobility - 1;
		}
		
		return validLocations;
	}
	
	/**
	 * Gets the neighbours of the given points.
	 * @param startX
	 * @param startY
	 * @return
	 */
	public static ArrayList<Coordinate> getNeighbours(int startX, int startY, Unit playerUnit, Map gameMap)
	{
		ArrayList<Coordinate> neighbours = new ArrayList<Coordinate>();
		ArrayList<Coordinate> potentialNeighbours = new ArrayList<Coordinate>();
		Coordinate northNeighbour = new Coordinate(startX, startY - 1);
		Coordinate southNeighbour = new Coordinate(startX, startY + 1);
		Coordinate eastNeighbour = new Coordinate(startX + 1, startY);
		Coordinate westNeighbour = new Coordinate(startX - 1, startY);
		potentialNeighbours.add(northNeighbour);
		potentialNeighbours.add(southNeighbour);
		potentialNeighbours.add(eastNeighbour);
		potentialNeighbours.add(westNeighbour);
		
		for(Coordinate coordinate : potentialNeighbours)
		{
			if(coordinate.x <= 15 && coordinate.x >= 0 && coordinate.y <= 15 && coordinate.y >= 0)
			{
				// Check if neighbour has enemy on it.
				if(gameMap.getUnitAt(coordinate.x, coordinate.y) != null)
				{
					// Someone's here!
					Unit unit = gameMap.getUnitAt(coordinate.x, coordinate.y);
					if(unit.getOwner() == playerUnit.getOwner())
					{
						// Friendly
						neighbours.add(coordinate);
					}
				}
				else
				{
					neighbours.add(coordinate);
				}			
			}
		}
				
		return neighbours;
	}
	
	/**
	 * Gets the squares where there is an enemy unit that the playerUnit can attack.
	 * @param startX
	 * @param startY
	 * @param playerUnit
	 * @param gameMap
	 * @return
	 */
	public static ArrayList<Coordinate> getAttackableCoordinates(int startX, int startY, Unit playerUnit, Map gameMap)
	{
		ArrayList<Coordinate> attackableCoords = new ArrayList<Coordinate>();
		if(playerUnit.canMoveAndAttack())
		{
			ArrayList<Coordinate> moveableSpots = validLocations(startX, startY, playerUnit, gameMap);
			for(Coordinate moveable : moveableSpots)
			{
				for(Coordinate attackableCoordinate : getAttackableNeighbours(moveable, playerUnit, gameMap))
				{
					if(!attackableCoords.contains(attackableCoordinate))
					{
						attackableCoords.add(attackableCoordinate);
					}
				}
			}
		}
		else
		{
			
		}
		return attackableCoords;
	}
	
	private static ArrayList<Coordinate> getAttackableNeighbours(Coordinate startingPosition, Unit playerUnit, Map gameMap)
	{
		ArrayList<Coordinate> validAttacks = new ArrayList<Coordinate>();
		int northernY = startingPosition.y - 1;
		int southernY = startingPosition.y + 1;
		int westernX = startingPosition.x - 1;
		int easternX = startingPosition.x + 1;
		
		// Check North
		if(northernY >= 0)
		{
			if(gameMap.getUnitAt(startingPosition.x, northernY) != null)
			{
				Unit potentialEnemyUnit = gameMap.getUnitAt(startingPosition.x, northernY);
				if(potentialEnemyUnit.getOwner() != playerUnit.getOwner())
				{
					validAttacks.add(new Coordinate(startingPosition.x, northernY));
				}
			}
		}
		// Check South
		if(southernY <= 15)
		{
			if(gameMap.getUnitAt(startingPosition.x, southernY) != null)
			{
				Unit potentialEnemyUnit = gameMap.getUnitAt(startingPosition.x, southernY);
				if(potentialEnemyUnit.getOwner() != playerUnit.getOwner())
				{
					validAttacks.add(new Coordinate(startingPosition.x, southernY));
				}
			}
		}
		//Check West
		if(westernX >= 0)
		{
			if(gameMap.getUnitAt(westernX, startingPosition.y) != null)
			{
				Unit potentialEnemyUnit = gameMap.getUnitAt(westernX, startingPosition.y);
				if(potentialEnemyUnit.getOwner() != playerUnit.getOwner())
				{
					validAttacks.add(new Coordinate(westernX, startingPosition.y));
				}
			}
		}
		// Check East
		if(easternX <= 15)
		{
			if(gameMap.getUnitAt(easternX, startingPosition.y) != null)
			{
				Unit potentialEnemyUnit = gameMap.getUnitAt(easternX, startingPosition.y);
				if(potentialEnemyUnit.getOwner() != playerUnit.getOwner())
				{
					validAttacks.add(new Coordinate(easternX, startingPosition.y));
				}
			}
		}

		return validAttacks;
	}
	
	/**
	 * Checks if the two coordinates are adjacent to each other.
	 * @param a
	 * @param b
	 * @return
	 */
	public static boolean isNeighbour(Coordinate a, Coordinate b)
	{
		if(Math.abs(a.x - b.x) == 1 && (a.y == b.y))
		{
			return true;
		}
		else if(Math.abs(a.y - b.y) == 1 && (a.x == b.x))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
