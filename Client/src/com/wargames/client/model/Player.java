package com.wargames.client.model;

public class Player {
	
	public int funds;
	
	/**
	 * The Name of the player.
	 */
	public String name;
	
	/**
	 * The Team the player belongs to.
	 */
	public int teamNumber;
	
	/**
	 * String representation of their color.
	 */
	public String color;
	
	/**
	 * ID of the player that is stored on the database.
	 */
	public int ID;
	
	/**
	 * Player number in relationship to the map (1, 2, 3, 4 for a 4 player game, etc)
	 */
	public int playerNumber;
	
	/**
	 * Adds funds to the player.
	 * @param newFunds The new funds to add to the player.
	 * @return The total funds that the player has.
	 */
	public int addFunds(int newFunds)
	{
		this.funds = this.funds + newFunds;
		return this.funds;
	}
	
	/**
	 * Creates a new Player with initial funds, and name.
	 * @param initialFunds The initial funds of the player.
	 * @param name The name of the player.
	 */
	public Player(int ID, String name, int teamNumber, int playerNumber, String color)
	{
		this.ID = ID;
		this.name = name;
		this.teamNumber = teamNumber;
		this.playerNumber = playerNumber;
		this.funds = 0;
		this.color = color;
	}
}
