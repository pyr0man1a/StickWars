package com.wargames.client.gui;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.net.URL;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import com.wargames.client.helpers.Coordinate;
import com.wargames.client.helpers.MoveValidator;
import com.wargames.client.model.Game;
import com.wargames.client.model.MapGenerator;
import com.wargames.client.model.Player;
import com.wargames.client.model.Terrain;
import com.wargames.client.model.Unit;

public class GameClientGui extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7504649405406424171L;
	private Game game;
	private Player player1;
	private Player player2;
	
	// Gui objects
	public GuiMap guiMap;
	private Image imgBackground; // background image
	
	public GuiTerrain selectedTerrain;
	public GuiUnit selectedUnit;
	
	private JTextArea lblSelectedTerrain;
	private JTextArea lblSelectedUnit;
	private JTextArea lblGameState;
	private JButton endTurnButton;
	public JFrame f;
	
	public GameClientGui()
	{
		// background
		URL urlBackgroundImg = getClass().getResource("/com/wargames/client/gui/img/background.png");
		this.imgBackground = new ImageIcon(urlBackgroundImg).getImage();
		
		// Initialize the game.
		player1 = new Player(0, "Clinton", 1, 0, "red");
		player2 = new Player(1, "Jesus", 2, 1, "blue");
		
		//TODO: get game map from server
		//TODO: set local game 
		boolean localGame = true;
		game = new Game(MapGenerator.generateMap03(player1, player2), localGame);
		
		// Wrap our Map around the game Map
		guiMap = new GuiMap(game, this);
		
		
		// label to display game state
		this.lblSelectedTerrain = new JTextArea(5, 10);
		this.lblSelectedTerrain.setLineWrap( true );
		this.lblSelectedTerrain.setBackground(Color.GRAY);
		this.lblSelectedTerrain.setForeground(Color.WHITE);
		Font font = new Font("Verdana", Font.BOLD, 12);
		this.lblSelectedTerrain.setFont(font);
		this.lblSelectedTerrain.getCaret().setVisible(false);
		this.lblSelectedTerrain.getCaret().setSelectionVisible(false);
		this.lblSelectedTerrain.setWrapStyleWord( true );
		this.add(lblSelectedTerrain);
		
		this.lblSelectedUnit = new JTextArea(5, 10);
		this.lblSelectedUnit.setLineWrap( true );
		this.lblSelectedUnit.setBackground(Color.GRAY);
		this.lblSelectedUnit.setForeground(Color.WHITE);
		this.lblSelectedUnit.setFont(font);
		this.lblSelectedUnit.getCaret().setVisible(false);
		this.lblSelectedUnit.getCaret().setSelectionVisible(false);
		this.lblSelectedUnit.setWrapStyleWord( true );
		this.add(lblSelectedUnit);
		
		this.lblGameState = new JTextArea(5, 10);
		this.lblGameState.setLineWrap( true );
		this.lblGameState.setBackground(Color.GRAY);
		this.lblGameState.setForeground(Color.WHITE);
		this.lblGameState.setFont(font);
		this.lblGameState.getCaret().setVisible(false);
		this.lblGameState.getCaret().setSelectionVisible(false);
		this.lblGameState.setWrapStyleWord( true );
		this.add(lblGameState);
		
		// End Turn button
		this.endTurnButton = new JButton("End Turn");
		this.endTurnButton.setFont(font);
		this.add(endTurnButton);
		
		
		// Add listeners
		GameMouseListener mouseListener = new GameMouseListener(this);
		this.addMouseListener(mouseListener);
		EndTurnListener endTurnListener = new EndTurnListener(this);
		this.endTurnButton.addActionListener(endTurnListener);
		
		// create application frame and set visible
		//
		f = new JFrame();
		f.setSize(100, 100);
		f.setVisible(true);
		f.setResizable(true);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.add(this);
		f.setSize(800, 624);
	}

	
	@Override
	protected void paintComponent(Graphics g)
	{
		// draw background
		g.drawImage(this.imgBackground, 0, 0, null);
		this.guiMap.draw(g);
		
		this.lblSelectedTerrain.setText(this.getSelectedTerrain());
		this.lblSelectedTerrain.setLocation(600,44);
		this.lblSelectedUnit.setText(this.getSelectedUnit());
		this.lblSelectedUnit.setLocation(600,150);
		this.lblGameState.setLocation(600, 400);
		this.lblGameState.setText(getStateText());
		this.endTurnButton.setLocation(602, 520);
		
		
		drawSelectedTerrain(g);
		
		// If we have a unit selected, highlight the valid locations.
		if(this.selectedUnit != null && this.selectedUnit.getLogicalUnit().isActive())
		{
			Coordinate unitCoordinate = guiMap.getCoordinateOfUnit(selectedUnit);
			ArrayList<Coordinate> validLocations = MoveValidator.validLocations(unitCoordinate.x, unitCoordinate.y, selectedUnit.getLogicalUnit(), this.game.gameMap);
			for(Coordinate validLocation : validLocations)
			{
				int highlightX = validLocation.x * 32 + 44;
				int highlightY = validLocation.y * 32 + 44;
				
				// draw the highlight
				g.setColor(new Color(0, 255, 0, 100));
				g.fillRoundRect( highlightX, highlightY, 32, 32, 10, 10);
			}
			ArrayList<Coordinate> attackables = MoveValidator.getAttackableCoordinates(unitCoordinate.x, unitCoordinate.y, selectedUnit.getLogicalUnit(), this.game.gameMap);
			for(Coordinate attackable : attackables)
			{
				int highlightX = attackable.x * 32 + 44;
				int highlightY = attackable.y * 32 + 44;
				
				// draw the highlight
				g.setColor(new Color(255, 0, 0, 100));
				g.fillRoundRect( highlightX, highlightY, 32, 32, 10, 10);
			}
		}
	}
	
	public String getSelectedTerrain()
	{
		Terrain logicalTerrain;
		if(this.selectedTerrain == null)
		{
			logicalTerrain = this.game.gameMap.getTerrainAt(0, 0);
		}
		else
		{
			logicalTerrain = this.selectedTerrain.getLogicalTerrain();
		}
		
		return logicalTerrain.terrainType.toString() + "\n" + logicalTerrain.description;
	}
	
	public String getSelectedUnit()
	{
		Unit logicalUnit;
		if(this.selectedUnit == null)
		{
			return "";
		}
		else
		{
			logicalUnit = this.selectedUnit.getLogicalUnit();
		}
		String activeString;
		if(logicalUnit.isActive())
		{
			activeString = "Active";
		}
		else
		{
			activeString = "Inactive";
		}
		return logicalUnit.getUnitType().toString() + "\n" + logicalUnit.getDescription() + "\n\nHealth: " + logicalUnit.health + "\nRange: " + logicalUnit.getRange() + "\nMobility: " + logicalUnit.getMobility() + "\nActive: " + activeString; 
	}
	
	public void drawSelectedTerrain(Graphics g)
	{
		URL urlSelectorImage = getClass().getResource("/com/wargames/client/gui/img/mapReticle.png");
		Image selectorImage = new ImageIcon(urlSelectorImage).getImage();
		if(this.selectedTerrain == null)
		{
			g.drawImage(selectorImage, 44, 44, null);
		}
		else
		{
			g.drawImage(selectorImage, this.selectedTerrain.getX(), this.selectedTerrain.getY(), null);
		}
	}
	
	public String getStateText()
	{
		String returnString = "Current Turn: " + this.game.currentTurn.color;
		for(Player player : game.gameMap.players)
		{
			returnString = returnString.concat("\n" + player.color + " funds: " + player.funds);
		}
		return returnString;
	}
	
	public void endGame(Player winner)
	{
		EndGameWindow window = new EndGameWindow(this, winner);
	}
}
