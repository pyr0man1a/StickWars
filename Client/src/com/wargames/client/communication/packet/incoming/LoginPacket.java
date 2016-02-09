package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import com.wargames.client.gui.MainGui;

public class LoginPacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		byte response = buff.get();
		int wins = buff.getInt();
		int losses = buff.getInt();
		
		//TODO: do stuff with response
		System.out.println("Response: " + response);
		System.out.println("Wins: " + wins);
		System.out.println("Losses: " + losses);
		
		if(response == 1)
		{
			System.out.println("Logged in.");
			JFrame topframe = (JFrame) SwingUtilities.getWindowAncestor(client);
			topframe.dispose();
			new MainGui();
		}
	}

}
