package com.wargames.client.gui;

import java.awt.Graphics;
import java.net.URL;

import javax.swing.ImageIcon;

import com.wargames.client.helpers.Coordinate;
import com.wargames.client.helpers.DamageCalculator;
import com.wargames.client.helpers.WinChecker;
import com.wargames.client.model.*;

public class GuiMap {
	public Game logicalGame;
	private GuiUnit[][] graphicalUnits;
	private GuiTerrain[][] graphicalTerrain;
	private GameClientGui client;
	
	private final int MapOffsetX = 44;
	private final int MapOffsetY = 44;
	private final int TILEWIDTH = 32;
	private final int TILEHEIGHT = 32;
	private int mapWidth;
	private int mapHeight;
	
	public GuiMap(Game logicalGame, GameClientGui client)
	{
		this.logicalGame = logicalGame;
		this.client = client;
		mapWidth = logicalGame.gameMap.getWidth();
		mapHeight = logicalGame.gameMap.getHeight();
		this.graphicalUnits = new GuiUnit[mapWidth][mapHeight];
		this.graphicalTerrain = new GuiTerrain[mapWidth][mapHeight];
		
		for(int i = 0; i < mapWidth; i++)
		{
			for(int j = 0; j < mapHeight; j++)
			{
				GuiTerrain newGuiTerrain = new GuiTerrain(logicalGame.gameMap.getTerrainAt(i, j), i * TILEWIDTH + MapOffsetX, j * TILEHEIGHT + MapOffsetY);
				this.graphicalTerrain[i][j] = newGuiTerrain;
				if(logicalGame.gameMap.getUnitAt(i, j) != null)
				{
					this.graphicalUnits[i][j] = new GuiUnit(logicalGame.gameMap.getUnitAt(i,j), i * TILEWIDTH + MapOffsetX, j * TILEHEIGHT + MapOffsetY);
				}
			}
		}
	}
	
	public void draw(Graphics g)
	{
		for(int i = 0; i < mapWidth; i++)
		{
			for(int j = 0; j < mapHeight; j++)
			{
				GuiTerrain terrain = this.graphicalTerrain[i][j];
				g.drawImage(terrain.getImage(), terrain.getX(), terrain.getY(), null);
				if(graphicalUnits[i][j] != null)
				{
					GuiUnit unit = graphicalUnits[i][j];
					g.drawImage(unit.getImage(), unit.getX(), unit.getY(), null);
					g.drawImage(unit.getHealthImage(), unit.getX(), unit.getY(), null);
					if(!unit.getLogicalUnit().isActive())
					{
						URL urlUnitImage = getClass().getResource("/com/wargames/client/gui/img/disabled.png");
						g.drawImage(new ImageIcon(urlUnitImage).getImage(), unit.getX(), unit.getY(), null);
					}
				}
			}
		}
	}
	
	public GuiTerrain getTerrainAt(int x, int y) throws MapException
	{
		if(x < 44 || x > 556 || y < 44 || y > 556)
		{
			throw new MapException("MapException: X or Y is out of bounds.");
		}
		
		int realX = (x - MapOffsetX) / TILEWIDTH;
		int realY = (y - MapOffsetY) / TILEHEIGHT;
		return graphicalTerrain[realX][realY];
	}
	
	public GuiUnit getUnitAt(int x, int y) throws MapException
	{
		if(x < 44 || x > 556 || y < 44 || y > 556)
		{
			throw new MapException("MapException: X or Y is out of bounds.");
		}
		
		int realX = (x - MapOffsetX) / TILEWIDTH;
		int realY = (y - MapOffsetY) / TILEHEIGHT;
		return graphicalUnits[realX][realY];
	}
	
	public Coordinate getCoordinateOfUnit(GuiUnit unit)
	{
		int graphicalX = unit.getX();
		int graphicalY = unit.getY();
		
		int logicalX = (graphicalX - MapOffsetX) / TILEWIDTH;
		int logicalY = (graphicalY - MapOffsetY) / TILEHEIGHT;
		
		Coordinate coordinate = new Coordinate(logicalX, logicalY);
		return coordinate;
	}
	
	public Coordinate getCoordinate(int x, int y)
	{
		int translatedX = (x - MapOffsetX) / TILEWIDTH;
		int translatedY = (y - MapOffsetY) / TILEHEIGHT;
		Coordinate coordinate = new Coordinate(translatedX, translatedY);
		return coordinate;
	}
	
	/**
	 * Used when you want to move the currently selected unit on the field.
	 * @param selectedUnit
	 * @param destinationCoordinate
	 */
	public void moveSelectedUnit(GuiUnit selectedUnit, Coordinate destinationCoordinate)
	{
		if (this.client.guiMap.logicalGame.isLocalGame()){
			//update UI locally
			Coordinate selectedUnitCoordinates = getCoordinateOfUnit(selectedUnit);
			this.logicalGame.moveUnit(selectedUnitCoordinates.x, selectedUnitCoordinates.y, destinationCoordinate.x, destinationCoordinate.y);
			
			// If everything is OK, we update the unit's position
			selectedUnit.setX(destinationCoordinate.x * TILEWIDTH + MapOffsetX);
			selectedUnit.setY(destinationCoordinate.y * TILEHEIGHT + MapOffsetY);
			
			if (!(destinationCoordinate.x==selectedUnitCoordinates.x && destinationCoordinate.y == selectedUnitCoordinates.y)){
				graphicalUnits[destinationCoordinate.x][destinationCoordinate.y] = selectedUnit;
				graphicalUnits[selectedUnitCoordinates.x][selectedUnitCoordinates.y] = null;
			}
			selectedUnit.getLogicalUnit().deactivate();
		} else {
			//TODO: SEND PACKET
			//wait for server to update UI
		}
	}
	
	/**
	 * SelectedUnit attacks the unit at victimCoordinate, by moving to moveCoordinate.
	 * @param selectedUnit
	 * @param moveCoordinate
	 * @param victimCoordinate
	 */
	public void moveAttackUnit(GuiUnit selectedUnit, Coordinate moveCoordinate, Coordinate victimCoordinate)
	{
		Unit attacker = selectedUnit.getLogicalUnit();
		Coordinate attackerCoordinate = this.getCoordinateOfUnit(selectedUnit);
		Unit defender = this.logicalGame.gameMap.getUnitAt(victimCoordinate.x, victimCoordinate.y);
		Terrain attackerTerrain = this.logicalGame.gameMap.getTerrainAt(attackerCoordinate.x, attackerCoordinate.y);
		Terrain defenderTerrain = this.logicalGame.gameMap.getTerrainAt(victimCoordinate.x, victimCoordinate.y);
		int damage = DamageCalculator.calculateDamage(attacker, defender, defenderTerrain);
		int returnDamage = DamageCalculator.calculateDamage(defender, attacker, attackerTerrain) / 2;//initiator takes half damage
		
		
		if (this.logicalGame.isLocalGame()){
			//update UI locally
			moveSelectedUnit(selectedUnit, moveCoordinate);
			boolean isDead = this.logicalGame.damageUnit(victimCoordinate.x, victimCoordinate.y, damage);
			if(isDead)
			{
				this.graphicalUnits[victimCoordinate.x][victimCoordinate.y] = null;
				Player winner = WinChecker.checkWinCondition(this.logicalGame.gameMap);
				if(winner != null)
				{
					System.out.println("Winner: " + winner.color);
					client.endGame(winner);
				}
			}
			selectedUnit.getLogicalUnit().deactivate();
			isDead = this.logicalGame.damageUnit(attackerCoordinate.x, attackerCoordinate.y, returnDamage);
			if(isDead)
			{
				this.graphicalUnits[attackerCoordinate.x][attackerCoordinate.y] = null;
				Player winner = WinChecker.checkWinCondition(this.logicalGame.gameMap);
				if(winner != null)
				{
					System.out.println("Winner: " + winner.color);
					client.endGame(winner);
				}
			}
		}
		else{
			//TODO: SEND PACKET attackerID, movecoordinate.x, movecoordinate.y, ACTION_ATTACK, targetID
			//wait for server packet to update UI
		}
	}
	
	/**
	 * Attack without moving.
	 * @param selectedUnit
	 * @param victimCoordinate
	 */
	public void AttackUnit(GuiUnit selectedUnit, Coordinate victimCoordinate)
	{
		Unit attacker = selectedUnit.getLogicalUnit();
		Coordinate attackerCoordinate = this.getCoordinateOfUnit(selectedUnit);
		Unit defender = this.logicalGame.gameMap.getUnitAt(victimCoordinate.x, victimCoordinate.y);
		Terrain attackerTerrain = this.logicalGame.gameMap.getTerrainAt(attackerCoordinate.x, attackerCoordinate.y);
		Terrain defenderTerrain = this.logicalGame.gameMap.getTerrainAt(victimCoordinate.x, victimCoordinate.y);
		int damage = DamageCalculator.calculateDamage(attacker, defender, defenderTerrain);
		int returnDamage = DamageCalculator.calculateDamage(defender, attacker, attackerTerrain) / 2;//initiator takes half damage
		
		if (this.logicalGame.isLocalGame()){
			//update UI locally
			boolean isDead = this.logicalGame.damageUnit(victimCoordinate.x, victimCoordinate.y, damage);
			if(isDead)
			{
				this.graphicalUnits[victimCoordinate.x][victimCoordinate.y] = null;
				Player winner = WinChecker.checkWinCondition(this.logicalGame.gameMap);
				if(winner != null)
				{
					System.out.println("Winner: " + winner.color);
					client.endGame(winner);
				}
			}
			selectedUnit.getLogicalUnit().deactivate();
			isDead = this.logicalGame.damageUnit(attackerCoordinate.x, attackerCoordinate.y, returnDamage);
			if(isDead)
			{
				this.graphicalUnits[attackerCoordinate.x][attackerCoordinate.y] = null;
				Player winner = WinChecker.checkWinCondition(this.logicalGame.gameMap);
				if(winner != null)
				{
					System.out.println("Winner: " + winner.color);
					client.endGame(winner);
				}
			}
		}
		else{
			//TODO: SEND PACKET attacker_id, attackerCoordinate.x, attackerCoordinate.y, ACTION_ATTACK, targetID 
			//wait for server to update UI
		}
	}
	
	/**
	 * Creates a unit for the current player.
	 * @param unitType
	 */
	public void CreateUnit(UnitType unitType, Coordinate factoryCoordinates)
	{
		if (this.client.guiMap.logicalGame.isLocalGame()){
			//update UI locally
			Player currentPlayer = this.logicalGame.currentTurn;
			Unit newUnit = this.logicalGame.createUnit(factoryCoordinates.x, factoryCoordinates.y, unitType, currentPlayer);
			this.graphicalUnits[factoryCoordinates.x][factoryCoordinates.y] = new GuiUnit(newUnit, factoryCoordinates.x * TILEWIDTH + MapOffsetX, factoryCoordinates.y * TILEHEIGHT + MapOffsetY);
			client.guiMap.logicalGame.currentTurn.funds = client.guiMap.logicalGame.currentTurn.funds - UnitCosts.getUnitCost(unitType);
			newUnit.deactivate();	
		}
		else{
			Player currentPlayer = this.logicalGame.currentTurn;
			//TODO: SEND PACKET unit creation
			//wait for server to update UI
		}
		
			
	}
}
