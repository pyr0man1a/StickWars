package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class PostGamePacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		int id = buff.getInt();
		byte color = buff.get();
		byte team = buff.get();
		byte winner = buff.get(); //bool
		int score = buff.getInt();
		byte wins = buff.get();
		byte losses = buff.get();
		
		//TODO: do stuff with response
		
	}

}
