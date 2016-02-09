#pragma once

enum UnitType : int {
	Infantry = 0,
	Tank = 1,
	Artillery = 2,
	Recon = 3,
	Bike = 4,
	Rockets = 5,
	Mech = 6,
	Fighter = 7,
	Duster = 8,
	Bomber = 9,
	Transport_Copter = 10,
	Battleship = 11,
	Cruiser = 12,
	Submarine = 13,
	Lander = 14,
	UnitTypeCount = 15,
	Invalid = -1
};

enum MobilityType : int {
	Foot = 0,
	Tire = 1,
	Tread = 2,
	Air = 3,
	Boat = 4,
	MobilityTypeCount = 5,
	None = -1
};

enum TerrainType : int {
	Plain = 0,
	Mountain = 1,
	Road = 2,
	Sea = 3,
	Wood = 4,
	HQ = 5,
	Factory = 6,
	City = 7,
	Airport = 8,
	TerrainTypeCount = 9,
	Error = -1
};

enum DamageType : int {
	NoDamage,
	Bullet,
	Concussive
};