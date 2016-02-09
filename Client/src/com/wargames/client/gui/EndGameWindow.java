package com.wargames.client.gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import com.wargames.client.model.Player;

public class EndGameWindow extends JDialog implements ActionListener{
	private GameClientGui client;
	private Player winner;
	private JPanel myPanel;
	
	public EndGameWindow(GameClientGui client, Player winner)
	{
		this.client = client;
		this.winner = winner;
		
		myPanel = new JPanel();
		getContentPane().add(myPanel);
		myPanel.setLayout(new GridLayout(4, 1));
		myPanel.setBorder(new EmptyBorder(10,10,10,10));
		JLabel headerLabel = new JLabel("Game Over");
		myPanel.add(headerLabel);
		
		JLabel winnerLabel = new JLabel(winner.color.toUpperCase() + " Team won!");
		myPanel.add(winnerLabel);
		
		JButton newGameButton = new JButton("New Game?");
		newGameButton.addActionListener(this);
		myPanel.add(newGameButton);
		
		JButton exitButton = new JButton("Exit");
		exitButton.addActionListener(this);
		myPanel.add(exitButton);
		
		this.setLocationRelativeTo(client.f);
		this.setUndecorated(true);
		pack();
		setVisible(true);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		JButton selectedButton = (JButton) e.getSource();
		switch(selectedButton.getText())
		{
			case "Exit":
				this.client.f.dispose();
				break;
			case "New Game?":
				this.client.f.dispose();
				new GameClientGui();
				break;
		}
		this.dispose();
	}

}
