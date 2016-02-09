package com.wargames.client.communication.packet.outgoing;

/**
 * All Packets sent and received should follow this basic structure.
 * @author Clinton
 *
 */
abstract class Packet {
	protected byte ID;
	protected byte size;
	
	int getSize()
	{
		return size;
	}
	
	int getID()
	{
		return ID;
	}
	
	public abstract byte[] toByteArray();
}
