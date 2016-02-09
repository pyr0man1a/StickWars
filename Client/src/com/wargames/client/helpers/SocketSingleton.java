package com.wargames.client.helpers;

import java.net.DatagramSocket;
import java.net.SocketException;

public class SocketSingleton {
	private static SocketSingleton instance = null;
	public DatagramSocket socket;
	
	private SocketSingleton()
	{
		try {
			this.socket = new DatagramSocket();
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static synchronized SocketSingleton getInstance()
	{
		if(instance == null)
		{
			instance = new SocketSingleton();
		}
		return instance;
	}

}
