package com.wargames.client.gui;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainGui extends JPanel implements ActionListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 4059868460110309749L;
	public JFrame f;
	public Image imgBackground;
	public JButton localGameButton;
	
	public MainGui()
	{
		URL urlBackgroundImg = getClass().getResource("/com/wargames/client/gui/img/mainBackground.png");
		this.imgBackground = new ImageIcon(urlBackgroundImg).getImage();
		
		this.localGameButton = new JButton("New Local Game");
		localGameButton.addActionListener(this);
		this.add(localGameButton);
		
		// create application frame and set visible
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
		g.drawImage(this.imgBackground, 0, 0, null);
		localGameButton.setLocation(400, 300);
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new MainGui();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		this.f.dispose();
		new GameClientGui();
	}

}
