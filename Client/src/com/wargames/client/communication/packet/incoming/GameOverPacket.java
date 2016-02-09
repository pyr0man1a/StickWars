package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class GameOverPacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		byte winnerNumber = buff.get();
		int winnerID = buff.getInt();
		
		//TODO: do stuff with response

	}

}
