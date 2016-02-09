package com.wargames.client.communication.packet.outgoing;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class LobbyActionPacket extends Packet {

	private byte action;
	
	public LobbyActionPacket(byte action) {
		this.ID = 0x05;
		this.size = 0x03;
		this.action = action;
	}
	
	@Override
	public byte[] toByteArray() {
		ByteBuffer buffer = ByteBuffer.allocate(this.size);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.put(this.ID);
		buffer.put(this.size);
		buffer.put(this.action);
		buffer.flip();
		return buffer.array();
	}

}
