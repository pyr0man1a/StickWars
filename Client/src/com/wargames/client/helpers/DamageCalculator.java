package com.wargames.client.helpers;

import com.wargames.client.model.*;

public class DamageCalculator {
	public static int calculateDamage(Unit attacker, Unit defender, Terrain defenderTerrain)
	{
		float decimalDamage = getDamageStat(attacker,defender) * attacker.health / 100;
		int damage = Math.round(decimalDamage);
		System.out.println("Damage: " + damage);
		return damage;
	}

	public static int getDamageStat(Unit attacker, Unit defender)
	{
		switch(attacker.getUnitType())
		{
		case SOLDIER:
			switch(defender.getUnitType()){
			case SOLDIER:
				return 55;
			case TANK:
				return 5;
			case ARTILLERY:
				return 10;
			}
			break;
		case TANK:
			switch(defender.getUnitType()){
			case SOLDIER:
				return 75;
			case TANK:
				return 55;
			case ARTILLERY:
				return 70;
			}
			break;
		case ARTILLERY:
			switch(defender.getUnitType()){
			case SOLDIER:
				return 90;
			case TANK:
				return 70;
			case ARTILLERY:
				return 75;
			}
			break;
		}
		return 50;
	}

}
