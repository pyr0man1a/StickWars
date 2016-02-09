package com.wargames.client.communication.packet.incoming;

import java.lang.reflect.InvocationTargetException;
import java.nio.ByteBuffer;

import javax.swing.JPanel;

public class IncomingPacketList {
	static PacketFunctor[] packetParser = new PacketFunctor[32];
	
	static
	{
		packetParser[0x01] = new LoginPacket();
		packetParser[0x02] = new AccountCreatePacket();
		packetParser[0x03] = new LobbyUpdatePacket();
		packetParser[0x04] = new LobbyChatPacket();
		packetParser[0x05] = new LobbyCountdownPacket();
		packetParser[0x06] = new PostGamePacket();
		packetParser[0x07] = new LobbyListPacket();
		packetParser[0x10] = new GameLoadPacket();
		packetParser[0x11] = new EntityUpdatePacket();
		packetParser[0x12] = new PlayerDefinitionPacket();
		packetParser[0x13] = new TurnChangePacket();
		packetParser[0x14] = new PlayerUpdatePacket();
		packetParser[0x15] = new ActionPacket();
		packetParser[0x16] = new PlayerDefeatedPacket();
		packetParser[0x17] = new GameOverPacket();
	}
	
	public static void parse(byte[] data, JPanel client)
	{
		int begin = 0;
		
		while (begin < data.length)
		{
			byte type = data[begin];
			byte size = data[begin+1];
			if (begin + size < data.length)
			{
				//trailing zeroes get cut off for some reason - java "feature"?
				
			}
			ByteBuffer buff = ByteBuffer.allocate(size);
			buff.put(data, begin+2, (begin+2)+size < data.length ? size : data.length - (begin+2));
			buff.rewind();
			try
			{
				packetParser[type].parse(buff, client);
			}
			catch (Error e)
			{
				System.out.println("Attempted to parse packet "+type+" failed!");
			}
			begin = begin+size;
		}
	}
	
}
