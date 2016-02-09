package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class LobbyUpdatePacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		byte maxSize = buff.get();
		byte mapID = buff.get();
		byte players = buff.get();
		
		for (int i = 0; i < players; i++)
		{
			int id = buff.getInt();
			byte team = buff.get();
			byte color = buff.get();
			byte[] name = new byte[10];
			for (int j = 0; j < 10; j++)
			{
				name[j] = buff.get();
			}
			
			//TODO: do stuff with response
			
		}

	}

}
