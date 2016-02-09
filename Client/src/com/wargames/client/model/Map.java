package com.wargames.client.model;

import java.util.ArrayList;
import java.util.Hashtable;

public class Map {
	private Unit[][] unitMap;
	private Terrain[][] terrainMap;
	private int height;
	private int width;
	public Hashtable<UnitType, Integer> unitCost;
	public ArrayList<Player> players;
	
	public Map(int width, int height)
	{
		this.height = height;
		this.width = width;
		this.players = new ArrayList<Player>();
		this.unitMap = new Unit[width][height];
		this.terrainMap = new Terrain[width][height];
		this.unitCost = new Hashtable<UnitType, Integer>();
	}

	public void addPlayer(Player player)
	{
		this.players.add(player);
	}
	
	public int getWidth()
	{
		return this.width;
	}
	
	public int getHeight()
	{
		return this.height;
	}
	
	public Unit getUnitAt(int width, int height)
	{
		return this.unitMap[width][height];
	}
	
	public Unit deleteUnitAt(int x, int y)
	{
		Unit targetUnit = this.unitMap[x][y];
		this.unitMap[x][y] = null;
		return targetUnit;
	}
	
	/**
	 * Tries to move a unit on the map to the destination location.
	 * @param startX
	 * @param startY
	 * @param destX
	 * @param destY
	 * @return The unit that moved.
	 * @throws MapException
	 */
	public Unit moveUnit(int startX, int startY, int destX, int destY) throws MapException
	{
		if (startX == destX && startY == destY){
			return unitMap[startX][startY];
		}
		else if(unitMap[destX][destY] == null)
		{
			Unit targetUnit = unitMap[startX][startY];
			unitMap[startX][startY] = null;
			unitMap[destX][destY] = targetUnit;
			return targetUnit;
		}
		else
		{
			throw new MapException("MapException: Destination location already has a unit.");
		}
	}
	
	public Terrain getTerrainAt(int width, int height)
	{
		return this.terrainMap[width][height];
	}
	
	/**
	 * Adds a terrain to the map at the specified location.
	 * Should be used in initialization only.
	 * @param width
	 * @param height
	 * @param terrain
	 * @throws MapException
	 */
	public void addTerrain(int width, int height, Terrain terrain) throws MapException
	{
		if (this.getTerrainAt(width, height) == null)
		{
			this.terrainMap[width][height] = terrain;
		}
		else
		{
			throw new MapException("MapException: Terrain already exists.  Try again.");
		}
	}
	
	/**
	 * Creates a specified unit at the location.
	 * @param x
	 * @param y
	 * @param unit
	 * @throws MapException
	 */
	public void createUnit(int x, int y, Unit unit) throws MapException
	{
		if(this.unitMap[x][y] == null)
		{
			this.unitMap[x][y] = unit;
		}
		else
		{
			throw new MapException("MapException: There is already a unit in this location.");
		}
	}
	
	/**
	 * Captures a structure.
	 * @param x X coordinate of structure.
	 * @param y Y coordinate of structure.
	 * @param capturer Unit that is capturing the structure.
	 * @return The Structure that is being captured (updated with new information)
	 * @throws MapException if location isn't a Structure, or unit isn't capable of capturing.
	 */
	public Structure captureStructure(int x, int y, Unit capturer) throws MapException
	{
		if(capturer.getUnitType() != UnitType.SOLDIER)
		{
			throw new MapException("MapException: This unit is not capable of capturing.");
		}
		if(this.unitMap[x][y] != capturer)
		{
			throw new MapException("MapException: This unit is not on the structure location.");
		}
		try {
			Structure targetStructure = (Structure) terrainMap[x][y];
			targetStructure.capture(capturer);
			return targetStructure;
		}
		catch(ClassCastException e)
		{
			throw new MapException("MapException: Location for capturing is not a structure.");
		}
	}
	
	/**
	 * Activates all units on the map.
	 */
	public void activateAllUnits()
	{
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{
				if(this.unitMap[i][j] != null)
				{
					this.unitMap[i][j].activate();
				}
			}
		}
	}
}
