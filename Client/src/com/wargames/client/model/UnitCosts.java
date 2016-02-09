package com.wargames.client.model;

public class UnitCosts {

	public static int getSoldierCost()
	{
		return 1500;
	}
	
	public static int getTankCost()
	{
		return 7000;
	}
	
	public static int getUnitCost(UnitType type){
		switch (type){
			case SOLDIER:
				return getSoldierCost();
			case TANK:
				return getTankCost();
		}
		return 0;
	}
}
