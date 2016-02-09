package com.wargames.client.communication.packet.outgoing;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class LobbyJoinPacket extends Packet{

	private short lobbyID;
	
	public LobbyJoinPacket(short lobbyID) {
		this.ID = 0x03;
		this.size = 0x04;
		this.lobbyID = lobbyID;
	}
	
	@Override
	public byte[] toByteArray() {
		ByteBuffer buffer = ByteBuffer.allocate(this.size);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.put(this.ID);
		buffer.put(this.size);
		buffer.putShort(this.lobbyID);
		buffer.flip();
		return buffer.array();
	}

}
