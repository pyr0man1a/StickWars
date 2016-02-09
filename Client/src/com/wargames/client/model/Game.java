package com.wargames.client.model;


public class Game {
	public Map gameMap;
	public Player currentTurn;
	private boolean localGame;
	
	public Game(Map gameMap, boolean localGame)
	{
		this.gameMap = gameMap;
		this.currentTurn = gameMap.players.get(gameMap.players.size() - 1);
		this.localGame = localGame;
		this.endTurn(currentTurn);
	}
	
	/**
	 * Returns true if local game.
	 * @return localGame
	 */	
	public boolean isLocalGame(){
		return this.localGame;
	}
		
	/**
	 * Moves a unit from its initial position to its final position.
	 * @param xStart
	 * @param yStart
	 * @param xDest
	 * @param yDest
	 */
	public void moveUnit(int xStart, int yStart, int xDest, int yDest)
	{
		try{
			gameMap.moveUnit(xStart, yStart, xDest, yDest);
		}
		catch(MapException e)
		{
			System.out.println("Game: Error in moving unit.  This should never happen.");
			e.printStackTrace();
		}
	}

	/**
	 * Uses the unit to capture a structure.
	 * @param x The X coordinate of the structure.
	 * @param y The Y coordinate of the structure.
	 * @param capturer The Unit that is trying to capture.
	 */
	public void captureStructure(int x, int y, Unit capturer)
	{
		try {
			this.gameMap.captureStructure(x, y, capturer);
		}
		catch(MapException e)
		{
			System.out.println("Game: Error in capturing structure.  This should never happen.");
			e.printStackTrace();
		}
	}
	
	/**
	 * Damages a unit on the field.
	 * @param x
	 * @param y
	 * @param damageAmount
	 */
	public boolean damageUnit(int x, int y, int damageAmount)
	{
		Unit targetUnit = gameMap.getUnitAt(x, y);
		if(damageAmount >= targetUnit.health)
		{
			this.gameMap.deleteUnitAt(x, y);
			return true;
		}
		else
		{
			targetUnit.damageUnit(damageAmount);
			return false;
		}
	}
	
	/**
	 * Creates a new unit at the X and Y location.
	 * X and Y should be a factory.
	 * @param x
	 * @param y
	 * @param unitType
	 * @param owner
	 */
	public Unit createUnit(int x, int y, UnitType unitType, Player owner)
	{
		Unit newUnit = null;
		switch(unitType)
		{
			case SOLDIER:
				newUnit = Unit.createSoldier(owner);
				break;
			case TANK:
				newUnit = Unit.createTank(owner);
				break;
			case ARTILLERY:
				newUnit = Unit.createArtillery(owner);
				break;
		}
		try {
			// Game Logic here -- Prevent creation if factory isn't here.
			if(gameMap.getTerrainAt(x, y).terrainType.equals(TerrainType.Factory))
			{
				Structure factoryStructure = (Structure) gameMap.getTerrainAt(x,y);
				if(factoryStructure.owner == owner)
				{
					this.gameMap.createUnit(x, y, newUnit);
				}
			}
		}
		catch(MapException e)
		{
			System.out.println("Game: Error in creating new unit. This should never happen.");
			e.printStackTrace();
		}
		return newUnit;
	}
	
	public void setTurn(Player player)
	{
		this.currentTurn = player;
	}
	
	/**
	 * 
	 */
	public void endTurn(Player player)
	{
		System.out.println("Input player: " + player.color);
		
		if(this.currentTurn == player)
		{
			// Change the currentTurn to the other player.
			int nextPlayerNumber = player.playerNumber + 1;
			if(nextPlayerNumber >= gameMap.players.size())
			{
				nextPlayerNumber = 0;
			}
			Player nextPlayer = gameMap.players.get(nextPlayerNumber);
			setTurn(nextPlayer);
			nextPlayer.addFunds(15000);
			// Activate all units.
			gameMap.activateAllUnits();
			
			// We should add the funds here.
		}
	}
}
