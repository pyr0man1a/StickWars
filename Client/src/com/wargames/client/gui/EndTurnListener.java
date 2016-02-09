package com.wargames.client.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.wargames.client.helpers.WinChecker;
import com.wargames.client.model.Player;

/**
 * Class for handling the End Turn button.
 * @author Crumbs
 *
 */
public class EndTurnListener implements ActionListener{
	
	private GameClientGui client;
	
	public EndTurnListener(GameClientGui client)
	{
		this.client = client;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		/////////////////
		this.client.guiMap.logicalGame.endTurn(this.client.guiMap.logicalGame.currentTurn);
		//////////////
		Player winner = WinChecker.checkWinCondition(client.guiMap.logicalGame.gameMap);
		if(winner != null)
		{
			System.out.println("Winner: " + winner.color);
			this.client.endGame(winner);
		}
		this.client.repaint();
	}

}
