package com.wargames.client.communication.packet.outgoing;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ChatPacket extends Packet {

	private String message;
	
	public ChatPacket(String message) {
		this.ID = 0x04;
		this.size = (byte) ((message.length() > 30 ? 30 : message.length()) + 0x02);
		this.message = message;
	}
	
	@Override
	public byte[] toByteArray() {
		ByteBuffer buffer = ByteBuffer.allocate(this.size);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.put(this.ID);
		buffer.put(this.size);
		buffer.put(this.message.getBytes());
		buffer.flip();
		return buffer.array();
	}

}
