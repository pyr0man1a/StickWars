package com.wargames.client.model;

public class Structure extends Terrain{

	public int income;
	public int captureStatus;
	public Player owner;
	public String color;
	
	/**
	 * Private constructor to build a structure.
	 * Defaults to Neutral (White)
	 * @param defense
	 * @param description
	 * @param terrainType
	 * @param income
	 * @param captureStatus
	 */
	private Structure(int defense, String description, TerrainType terrainType, int income, int captureStatus)
	{
		super(defense, description, terrainType);
		this.income = income;
		this.captureStatus = captureStatus;
		this.color = "white";
	}
	
	/**
	 * Private constructor to build a structure with an owner.
	 * @param defense
	 * @param description
	 * @param terrainType
	 * @param income
	 * @param captureStatus
	 * @param owner
	 */
	private Structure(int defense, String description, TerrainType terrainType, int income, int captureStatus, Player owner)
	{
		this(defense, description, terrainType, income, captureStatus);
		this.owner = owner;
		this.color = owner.color;
	}

	/**
	 * Creates a new HeadQuarters building for the given player.
	 * @param owner The player that owns the HQ.
	 * @return The Structure Object representing the HQ object.
	 */
	public static Structure createHQ(Player owner)
	{
		Structure newHQ = new Structure(4, "Capture the HQ to end a battle.", TerrainType.HQ, 1000, 0, owner);
		for(MoveType moveType : MoveType.values())
		{
			newHQ.moveCost.put(moveType, 1);
		}
		
		return newHQ;
	}
	
	/**
	 * Creates a new city that is neutral.
	 * @return The Structure Object representing the City object.
	 */
	public static Structure createCity()
	{
		Structure newCity = new Structure(2, "A populated city.  Once captured, cities provide funds.", TerrainType.City, 1000, 0);
		for(MoveType moveType : MoveType.values())
		{
			newCity.moveCost.put(moveType, 1);
		}
		return newCity;
	}
	
	/**
	 * Creates a new city for the given player.
	 * @param owner The player that owns the city.
	 * @return The Structure Object representing the City object.
	 */
	public static Structure createCity(Player owner)
	{
		Structure newCity = new Structure(2, "A populated city.  Once captured, cities provide funds.", TerrainType.City, 1000, 0, owner);
		for(MoveType moveType : MoveType.values())
		{
			newCity.moveCost.put(moveType, 1);
		}
		return newCity;
	}
	
	/**
	 * Creates a new factory building that neutral.
	 * @return The Structure Object representing the Factory object.
	 */
	public static Structure createFactory()
	{
		Structure newFactory = new Structure(3, "Once captured, this can be used to produce ground units.", TerrainType.Factory, 1000, 0);
		for(MoveType moveType : MoveType.values())
		{
			newFactory.moveCost.put(moveType, 1);
		}
		return newFactory;
	}
	
	/**
	 * Creates a new factory building for the given player.
	 * @param owner The player that owns the factory.
	 * @return The Structure Object representing the Factory object.
	 */
	public static Structure createFactory(Player owner)
	{
		Structure newFactory = new Structure(3, "Once captured, this can be used to produce ground units.", TerrainType.Factory, 1000, 0, owner);
		for(MoveType moveType : MoveType.values())
		{
			newFactory.moveCost.put(moveType, 1);
		}
		return newFactory;
	}

	/**
	 * Captures the structure with the given unit.
	 * @param capturer
	 * @return True if the structure has changed owners.  False otherwise.
	 */
	public boolean capture(Unit capturer)
	{
		this.captureStatus = this.captureStatus + capturer.health;
		if(this.captureStatus > 10)
		{
			this.owner = capturer.getOwner();
			return true;
		}
		else
		{
			return false;
		}
	}
	
	/**
	 * Gets the color of this building.
	 * @return
	 */
	public String getColor()
	{
		return this.color;
	}
}
