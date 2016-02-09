package com.wargames.client.model;
import java.util.*;

public class Terrain {
	public int defense;
	public String description;
	public Hashtable<MoveType, Integer> moveCost;
	public TerrainType terrainType;
	
	protected Terrain(int defense, String description, TerrainType terrainType) {
		this.defense = defense;
		this.description = description;
		this.terrainType = terrainType;
		this.moveCost = new Hashtable<MoveType, Integer>();
	}
	
	/**
	 * Creates a new Plain Terrain.
	 * @return A Terrain object representation of Plain.
	 */
	public static Terrain createPlainTerrain() {
		Terrain newTerrain = new Terrain(1, "Plains are easily traveled but offer little defense.", TerrainType.Plain);
		newTerrain.moveCost.put(MoveType.FOOT, 1);
		newTerrain.moveCost.put(MoveType.TANK, 1);
		newTerrain.moveCost.put(MoveType.TIRE, 2);
		return newTerrain;
	}
	
	/**
	 * Creates a new Mountain Terrain.
	 * @return A Terrain object representation of Mountain.
	 */
	public static Terrain createMountainTerrain() {
		Terrain newTerrain = new Terrain(4, "Mountains can only be traversed by infantry units.", TerrainType.Mountain);
		newTerrain.moveCost.put(MoveType.FOOT, 2);
		return newTerrain;
	}
	
	/**
	 * Creates a new Wood Terrain.
	 * @return A Terrain object representation of Wood.
	 */
	public static Terrain createWoodTerrain() {
		Terrain newTerrain = new Terrain(3, "Wood provides protection, but vehicles have a harder time travelling through.", TerrainType.Wood);
		newTerrain.moveCost.put(MoveType.FOOT, 1);
		newTerrain.moveCost.put(MoveType.TANK, 3);
		newTerrain.moveCost.put(MoveType.TIRE, 3);
		return newTerrain;
	}
	
	/**
	 * Creates a new Road Terrain.
	 * @return A Terrain object representation of Road.
	 */
	public static Terrain createRoadTerrain() {
		Terrain newTerrain = new Terrain(0, "Roads provide great mobility, but little cover.", TerrainType.Road);
		for(MoveType moveType : MoveType.values())
		{
			newTerrain.moveCost.put(moveType, 1);
		}
		return newTerrain;
	}
	
	/**
	 * Creates a new Sea Terrain.
	 * @return A Terrain object representation of Sea.
	 */
	public static Terrain createSeaTerrain() {
		Terrain newTerrain = new Terrain(0, "Naval and air forces have good mobility on calm seas.", TerrainType.Sea);
		return newTerrain;
	}
	
	/**
	 * Checks if the unit can move through this terrain.
	 * @param unit The unit that wants to move through this terrain
	 * @return True if it can, false otherwise.
	 */
	public boolean canMove(Unit unit)
	{
		if(!this.moveCost.containsKey(unit.getMoveType()))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	/**
	 * Gets the move cost for a given unit.
	 * @param unit
	 * @return
	 */
	public int getMoveCost(Unit unit)
	{
		if(!this.moveCost.containsKey(unit.getMoveType()))
		{
			return 0;
		}
		else
		{
			return this.moveCost.get(unit.getMoveType());
		}
	}
}
