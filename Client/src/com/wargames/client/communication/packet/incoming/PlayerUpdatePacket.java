package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class PlayerUpdatePacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		int money = buff.getInt();
		int score = buff.getInt();
		
		//TODO: do stuff with response

	}

}
