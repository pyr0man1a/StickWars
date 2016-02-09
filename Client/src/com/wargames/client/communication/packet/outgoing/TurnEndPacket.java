package com.wargames.client.communication.packet.outgoing;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class TurnEndPacket extends Packet {
	
	public TurnEndPacket() {
		this.ID = 0x13;
		this.size = 0x02;
	}
	
	@Override
	public byte[] toByteArray() {
		ByteBuffer buffer = ByteBuffer.allocate(this.size);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.put(this.ID);
		buffer.put(this.size);
		buffer.flip();
		return buffer.array();
	}
}
