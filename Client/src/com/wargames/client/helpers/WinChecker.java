package com.wargames.client.helpers;

import java.util.HashMap;
import java.util.Map.Entry;

import com.wargames.client.model.*;

public class WinChecker {
	
	/**
	 * Returns the winner of the game, if there is one.
	 * @param gameMap
	 * @return
	 */
	public static Player checkWinCondition(Map gameMap)
	{
		HashMap<Player, Integer> possibleWinners = new HashMap<Player, Integer>();
		for(Player player : gameMap.players)
		{
			possibleWinners.put(player, 0);
		}
		
		for(int i = 0; i < gameMap.getWidth(); i++)
		{
			for(int j = 0; j < gameMap.getHeight(); j++)
			{
				if(gameMap.getUnitAt(i, j) != null)
				{
					Unit playerUnit = gameMap.getUnitAt(i,j);
					possibleWinners.put(playerUnit.getOwner(), possibleWinners.get(playerUnit.getOwner()) + 1);
				}
			}
		}
		
		HashMap<Player, Integer> possibleWinnersClone = new HashMap<Player,Integer>();
		possibleWinnersClone.putAll(possibleWinners);
		
		for(Entry<Player, Integer> entry : possibleWinnersClone.entrySet())
		{
			if(entry.getValue() == 0)
			{
				possibleWinners.remove(entry.getKey());
			}
		}
		
		if(possibleWinners.size() == 1)
		{
			for(Player player : possibleWinners.keySet())
			{
				return player;
			}
		}
		return null;
	}

}
