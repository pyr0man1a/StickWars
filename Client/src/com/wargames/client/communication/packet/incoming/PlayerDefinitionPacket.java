package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class PlayerDefinitionPacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		int id = buff.getInt();
		byte[] name = new byte[10];
		for (int j = 0; j < 10; j++)
		{
			name[j] = buff.get();
		}
		byte color = buff.get();
		byte team = buff.get();
		byte number = buff.get();
		
		//TODO: do stuff with response

	}


}
