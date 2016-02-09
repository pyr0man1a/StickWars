package com.wargames.client.communication.packet.incoming;

import java.nio.ByteBuffer;
import java.util.ArrayList;

import javax.swing.JPanel;

import com.wargames.client.model.Lobby;

public class LobbyListPacket extends PacketFunctor {

	@Override
	public void parse(ByteBuffer buff, JPanel client) {
		byte numlobbies = buff.get();
		ArrayList<Lobby> lobbies = new ArrayList<Lobby>();
		for (int i = 0; i < numlobbies; i++)
		{
			short id = buff.getShort();
			byte size = buff.get();
			byte maxSize = buff.get();
			byte mapID = buff.get();
			byte[] name = new byte[10];
			for (int j = 0; j < 10; j++)
			{
				name[j] = buff.get();
			}
			
			
			//TODO: do stuff with response
			Lobby newLobby = new Lobby(id, size, maxSize, mapID, new String(name));
			lobbies.add(newLobby);
		}
		
		// Get rid of current Login Window, and show the lobby window.
		
	}

}
