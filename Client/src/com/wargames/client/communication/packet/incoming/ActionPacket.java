package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class ActionPacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		short initiatorID = buff.getShort();
		byte xPos = buff.get();
		byte yPos = buff.get();
		byte action = buff.get();
		short targetID = buff.getShort();
		byte dmgInit = buff.get();
		byte returndmg = buff.get();
		
		//TODO: do stuff with response

	}

}
