package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class AccountCreatePacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		byte response = buff.get();
		
		System.out.println(response);
		
		//TODO: do stuff with response

	}

}
