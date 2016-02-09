package com.wargames.client.model;

/**
 * Representation of a Lobby that we can connect to.
 * @author Clinton
 *
 */
public class Lobby {
	
	public int ID;
	public int numPlayers;
	public int maxPlayers;
	public int mapID;
	public String host;
	
	public Lobby(int id, int numPlayers, int maxPlayers, int mapID, String host)
	{
		this.ID = id;
		this.numPlayers = numPlayers;
		this.maxPlayers = maxPlayers;
		this.mapID = mapID;
		this.host = host;
	}

}
