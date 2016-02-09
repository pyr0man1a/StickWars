package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;

import javax.swing.JPanel;

/**
 * All Packets sent should follow this basic structure.
 * @author Clinton
 *
 */
public abstract class PacketFunctor {
	
	public abstract void parse(ByteBuffer buff, JPanel client);
}
