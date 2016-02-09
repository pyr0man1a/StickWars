package com.wargames.client.communication.packet.outgoing;

import java.nio.ByteBuffer;


public class LoginPacket extends Packet {

	private String username;
	private String password;
	
	public LoginPacket(String username, String password) {
		this.ID = 0x01;
		this.size = 0x1C;
		this.username = username;
		this.password = password;
	}
	
	@Override
	public byte[] toByteArray() {
		ByteBuffer buffer = ByteBuffer.allocate(this.size);
		buffer.put(this.ID);
		buffer.put(this.size);
		int padlength = 10 - this.username.length();
		buffer.put(this.username.getBytes());
		for (int i = 0; i < padlength; i++)
		{
			buffer.put((byte) 0x00);
		}
		padlength = 16 - this.password.length();
		buffer.put(this.password.getBytes());
		for (int i = 0; i < padlength; i++)
		{
			buffer.put((byte) 0x00);
		}
		buffer.flip();
		return buffer.array();
	}
}
