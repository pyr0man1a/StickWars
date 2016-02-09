package com.wargames.client.communication.packet.outgoing;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ActionPacket extends Packet {
	
	private short UID, TUID;
	private byte xpos, ypos, action;
	
	public ActionPacket(short UID, byte xpos, byte ypos, byte action, short TUID) {
		this.ID = 0x13;
		this.size = 0x02;
		this.UID = UID;
		this.TUID = TUID;
		this.xpos = xpos;
		this.ypos = ypos;
		this.action = action;
	}
	
	@Override
	public byte[] toByteArray() {
		ByteBuffer buffer = ByteBuffer.allocate(this.size);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.put(this.ID);
		buffer.put(this.size);
		buffer.putShort(this.UID);
		buffer.put(this.xpos);
		buffer.put(this.ypos);
		buffer.put(this.action);
		buffer.putShort(this.TUID);
		buffer.flip();
		return buffer.array();
	}
}
