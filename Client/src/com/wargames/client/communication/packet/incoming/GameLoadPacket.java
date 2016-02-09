package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class GameLoadPacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		byte mapID = buff.get();
		
		// Take the client's parent, create a new map, and give it to the Game Client GUI.

	}

}
