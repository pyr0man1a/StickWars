package com.wargames.client.gui;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;

import com.wargames.client.helpers.Coordinate;
import com.wargames.client.helpers.MoveValidator;
import com.wargames.client.model.MapException;
import com.wargames.client.model.Structure;
import com.wargames.client.model.TerrainType;
import com.wargames.client.model.Unit;

public class GameMouseListener implements MouseListener{

	public MouseState mouseState;
	private GameClientGui client;
	public Coordinate lastClick;

	public GameMouseListener(GameClientGui client)
	{
		this.mouseState = MouseState.NothingSelected;
		this.client = client;
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		int mouseXPosition = e.getX();
		int mouseYPosition = e.getY();

		if(mouseXPosition >= 44 && mouseXPosition < 556)
		{
			if(mouseYPosition >= 44 && mouseYPosition < 556)
			{
				// We're manipulating the map!
				switch(this.mouseState)
				{
				case NothingSelected:
					handleOnNothingSelected(e);
					break;
				case UnitSelected:
					handleOnUnitSelected(e);
					break;
				case FindingAttackTarget:
					handleOnUnitAttackSelection(e);
					break;
				case FindingMoveTarget:
					handleMoveOnUnitAttackSelection(e);
					break;
				}

			}
		}		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	private void handleOnUnitSelected(MouseEvent e)
	{
		int mouseXPosition = e.getX();
		int mouseYPosition = e.getY();
		Coordinate unitCoordinate = this.client.guiMap.getCoordinateOfUnit(this.client.selectedUnit);
		ArrayList<Coordinate> validLocations = MoveValidator.validLocations(unitCoordinate.x, unitCoordinate.y, this.client.selectedUnit.getLogicalUnit(), this.client.guiMap.logicalGame.gameMap);
		ArrayList<Coordinate> attackableUnits = MoveValidator.getAttackableCoordinates(unitCoordinate.x, unitCoordinate.y, this.client.selectedUnit.getLogicalUnit(), this.client.guiMap.logicalGame.gameMap);

		// If we click anywhere outside the valid locations, we go back to nothing selected state.
		Coordinate mouseCoordinate = client.guiMap.getCoordinate(mouseXPosition, mouseYPosition);
		if(this.client.selectedUnit.getLogicalUnit().getOwner() == this.client.guiMap.logicalGame.currentTurn)
		{
			if(attackableUnits.contains(mouseCoordinate))
			{
				Coordinate movePos = null;
				ArrayList<UnitActionType> possibleActions = new ArrayList<UnitActionType>();
				if (MoveValidator.isNeighbour(unitCoordinate, mouseCoordinate)){
					possibleActions.add(UnitActionType.Attack);
				}
				else{
					// If it's a square adjacent to an attackable unit, valid actions are Move and Attack
					for(Coordinate validPos : validLocations){
						if(MoveValidator.isNeighbour(mouseCoordinate, validPos)){
							if(client.selectedUnit.getLogicalUnit().canMoveAndAttack()){
								if(!possibleActions.contains(UnitActionType.Attack)){
									movePos = validPos;
									possibleActions.add(UnitActionType.Attack);
								}	
							}
						}
					}
				}
				ActionWindow actionWindow = new ActionWindow(client, e, possibleActions, this);
			}
			else if(validLocations.contains(mouseCoordinate))
			{
				ArrayList<UnitActionType> possibleActions = new ArrayList<UnitActionType>();
				// If it's a square adjacent to an attackable unit, valid actions are Move and Attack
				for(Coordinate attackableUnit : attackableUnits){
					if(MoveValidator.isNeighbour(mouseCoordinate, attackableUnit)){
						if(client.selectedUnit.getLogicalUnit().canMoveAndAttack()){
							if(!possibleActions.contains(UnitActionType.Attack)){
								possibleActions.add(UnitActionType.Attack);
							}	
						}
					}
				}

				// Open the action window here.
				// Get all possible actions

				possibleActions.add(UnitActionType.Move);

				ActionWindow actionWindow = new ActionWindow(client, e, possibleActions, this);
			}
			else
			{
				// Otherwise, close the selection, treat it as if nothing happened.
				this.client.selectedUnit = null;
				this.mouseState = MouseState.NothingSelected;
				handleOnNothingSelected(e);
			}
		}
		else
		{
			// Otherwise, close the selection, treat it as if nothing happened.
			this.client.selectedUnit = null;
			this.mouseState = MouseState.NothingSelected;
			handleOnNothingSelected(e);
		}
	}

	/**
	 * We reach this point when the mouse clicks on a unit after the "Attack" button is selected.
	 * @param e
	 */
	private void handleOnUnitAttackSelection(MouseEvent e)
	{
		Coordinate unitCoordinate = this.client.guiMap.getCoordinateOfUnit(this.client.selectedUnit);
		Coordinate victimCoordinate = this.client.guiMap.getCoordinate(e.getX(), e.getY());
		Coordinate moveCoordinate = new Coordinate(lastClick.x, lastClick.y);
		ArrayList<Coordinate> validLocations = MoveValidator.validLocations(unitCoordinate.x, unitCoordinate.y, client.selectedUnit.getLogicalUnit(), client.guiMap.logicalGame.gameMap);
		ArrayList<Coordinate> attackableUnits = MoveValidator.getAttackableCoordinates(lastClick.x, lastClick.y, client.selectedUnit.getLogicalUnit(), client.guiMap.logicalGame.gameMap);
		// Check if the spot that we clicked on is a unit we can attack		
		if(attackableUnits.contains(victimCoordinate) && validLocations.contains(moveCoordinate)
				&& MoveValidator.isNeighbour(moveCoordinate, victimCoordinate))
		{
			// We can attack this unit.
			System.out.println("Attacking unit at (" + victimCoordinate.x + "," + victimCoordinate.y + ")" );

			//Attack code here!
			this.client.guiMap.moveAttackUnit(this.client.selectedUnit, moveCoordinate, victimCoordinate);
			/////////
			this.mouseState = MouseState.NothingSelected;
			this.client.repaint();
		}
		else
		{
			// If we get here, we simply cancel everything.	
			this.client.selectedUnit = null;
			this.mouseState = MouseState.NothingSelected;
			this.client.repaint();
		}
	}
	
	/**
	 * We reach this point when the mouse clicks on a terrain to move to after the "Attack" button is selected.
	 * @param e
	 */
	private void handleMoveOnUnitAttackSelection(MouseEvent e)
	{
		Coordinate unitCoordinate = this.client.guiMap.getCoordinateOfUnit(this.client.selectedUnit);
		Coordinate moveCoordinate= this.client.guiMap.getCoordinate(e.getX(), e.getY());
		Coordinate victimCoordinate = new Coordinate(lastClick.x, lastClick.y);
		ArrayList<Coordinate> validLocations = MoveValidator.validLocations(unitCoordinate.x, unitCoordinate.y, client.selectedUnit.getLogicalUnit(), client.guiMap.logicalGame.gameMap);
		ArrayList<Coordinate> attackableUnits = MoveValidator.getAttackableCoordinates(lastClick.x, lastClick.y, client.selectedUnit.getLogicalUnit(), client.guiMap.logicalGame.gameMap);
		// Check if the spot that we clicked on is a unit we can attack		
		if(attackableUnits.contains(victimCoordinate) && validLocations.contains(moveCoordinate)
				&& MoveValidator.isNeighbour(moveCoordinate, victimCoordinate))
		{
			// We can attack this unit.
			System.out.println("Attacking unit at (" + victimCoordinate.x + "," + victimCoordinate.y + ")" );

			//Attack code here!
			this.client.guiMap.moveAttackUnit(this.client.selectedUnit, moveCoordinate, victimCoordinate);
			/////////
			this.mouseState = MouseState.NothingSelected;
			this.client.repaint();
		}
		else
		{
			// If we get here, we simply cancel everything.		
			this.client.selectedUnit = null;
			this.mouseState = MouseState.NothingSelected;
			this.client.repaint();
		}
	}


	private void handleOnNothingSelected(MouseEvent e)
	{
		int mouseXPosition = e.getX();
		int mouseYPosition = e.getY();
		try {
			this.client.selectedTerrain = this.client.guiMap.getTerrainAt(mouseXPosition, mouseYPosition);
			this.client.selectedUnit = this.client.guiMap.getUnitAt(mouseXPosition, mouseYPosition);
			if(this.client.selectedUnit != null)
			{
				if(this.client.selectedUnit.getLogicalUnit().isActive())
				{
					this.mouseState = MouseState.UnitSelected;
				}				
			}	
			else if(this.client.selectedTerrain.getLogicalTerrain().terrainType.equals(TerrainType.Factory))
			{
				Structure factory = (Structure) this.client.selectedTerrain.getLogicalTerrain();
				if(factory.owner == this.client.guiMap.logicalGame.currentTurn)
				{
					// We open the Build Unit Window.
					Coordinate factoryLocation = client.guiMap.getCoordinate(mouseXPosition, mouseYPosition);
					FactoryWindow factoryWindow = new FactoryWindow(this.client, factoryLocation);
					System.out.println("Factory Selected!");
					this.mouseState = MouseState.NothingSelected;
				}
			}
			this.client.repaint();
		} catch (MapException e1) {
			// TODO Auto-generated catch block
			System.out.println("THIS SHOULD NEVER HAPPEN.");
			e1.printStackTrace();
		}
	}

	private void stationaryAttack(Coordinate victimCoordinate)
	{
		Coordinate unitPos = client.guiMap.getCoordinateOfUnit(client.selectedUnit);
		int distance = Math.abs(unitPos.x - victimCoordinate.x) + Math.abs(unitPos.y - victimCoordinate.y);
		if (client.selectedUnit.getLogicalUnit().getRange() >= distance){
			this.client.guiMap.AttackUnit(this.client.selectedUnit, victimCoordinate);
		}
		client.selectedUnit = null;
		this.mouseState = MouseState.NothingSelected;

		this.client.revalidate();
		this.client.repaint();
	}
}
