package com.wargames.client.gui;

import java.awt.Image;
import java.net.URL;

import javax.swing.ImageIcon;

import com.wargames.client.model.*;

public class GuiTerrain {
	private Terrain logicalTerrain;
	private Image img;
	private int x;
	private int y;
	
	public GuiTerrain(Terrain terrain, int x, int y)
	{
		this.logicalTerrain = terrain;
		
		// Assign the img based on terrain type.
		String filename = "";
		
		switch(terrain.terrainType)
		{
			case Plain:
				filename = "grass.png";
				break;
			case Mountain:
				filename = "mountain.png";
				break;
			case Sea:
				filename = "water01.png";
				break;
			case Wood:
				filename = "trees.png";
				break;
			case Road:
				break;
			case Factory:
				Structure structureFactory = (Structure) this.logicalTerrain;
				String factoryColor = structureFactory.getColor();
				filename = "factory_" + factoryColor.toLowerCase() + ".png";
				break;
			case HQ:
				Structure structureHQ = (Structure) this.logicalTerrain;
				String hqColor = structureHQ.getColor();
				filename = "hq_" + hqColor.toLowerCase() + ".png";
				break;
			case City:
				Structure structureCity = (Structure) this.logicalTerrain;
				String cityColor = structureCity.getColor();
				filename = "city_" + cityColor.toLowerCase() + ".png";
				break;
		}
		URL urlTerrainImage = getClass().getResource("/com/wargames/client/gui/img/" + filename);
		this.img = new ImageIcon(urlTerrainImage).getImage();
		this.x = x;
		this.y = y;
	}
	
	public Terrain getLogicalTerrain()
	{
		return this.logicalTerrain;
	}
	
	public Image getImage()
	{
		return this.img;
	}
	
	public int getX()
	{
		return this.x;
	}
	
	public int getY()
	{
		return this.y;
	}
}
