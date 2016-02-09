#include "TerrainBuilder.h"


TerrainBuilder::TerrainBuilder(TerrainType type)
{
	switch (type){
		case TerrainType::Plain:
			buildPlain();
			break;
		case TerrainType::Mountain:
			buildMountain();
			break;
		case TerrainType::Road:
			buildRoad();
			break;
		case TerrainType::Sea:
			buildSea();
			break;
		case TerrainType::Wood:
			buildWood();
			break;
		case TerrainType::HQ:
			buildHQ();
			break;
		case TerrainType::Factory:
			buildFactory();
			break;
		case TerrainType::City:
			buildCity();
			break;
		case TerrainType::Airport:
			void buildAirport();
			break;
		case TerrainType::Error:
		default:
			m_type = TerrainType::Error;
			m_income = NULL;
			m_defense = NULL;
			m_moveCost = *(new MoveCost());
			break;
	}
}

TerrainBuilder::~TerrainBuilder()
{
}


Terrain *TerrainBuilder::getResult(){
	if (m_type == TerrainType::Error)
		return NULL;
	return new Terrain(m_type, m_income, m_defense, m_moveCost);
}

uint8 setOwner(){
	// TODO: get current player # from game and return it
	return 0;
}

void TerrainBuilder::buildPlain(){
	m_type = TerrainType::Plain;
	m_income = 0;
	m_defense = 1;
	m_moveCost[MobilityType::Foot] = 1;
	m_moveCost[MobilityType::Tread] = 1;
	m_moveCost[MobilityType::Tire] = 2;
}

void TerrainBuilder::buildMountain(){
	m_type = TerrainType::Mountain;
	m_income = 0;
	m_defense = 4;
	m_moveCost[MobilityType::Foot] = 2;
}

void TerrainBuilder::buildRoad(){
	m_type = TerrainType::Road;
	m_income = 0;
	m_defense = 0;
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		m_moveCost[static_cast<MobilityType>(i)] = 1;	
}

void TerrainBuilder::buildSea(){
	m_type = TerrainType::Sea;
	m_income = 0;
	m_defense = 0;
	m_moveCost[MobilityType::Boat] = 1;
}

void TerrainBuilder::buildWood(){
	m_type = TerrainType::Wood;
	m_income = 0;
	m_defense = 3;
	m_moveCost[MobilityType::Foot] = 1;
	m_moveCost[MobilityType::Tread] = 2;
	m_moveCost[MobilityType::Tire] = 3;
}

void TerrainBuilder::buildHQ(){
	m_type = TerrainType::HQ;
	m_income = 1000;
	m_defense = 4;
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		m_moveCost[static_cast<MobilityType>(i)] = 1;
}

void TerrainBuilder::buildFactory(){
	m_type = TerrainType::Factory;
	m_income = 1000;
	m_defense = 3;
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		m_moveCost[static_cast<MobilityType>(i)] = 1;
}

void TerrainBuilder::buildCity(){
	m_type = TerrainType::City;
	m_income = 1000;
	m_defense = 2;
	for (int i = 0; i < MobilityType::MobilityTypeCount; i++)
		m_moveCost[static_cast<MobilityType>(i)] = 1;
}

void TerrainBuilder::buildAirport(){
	// TODO?
}