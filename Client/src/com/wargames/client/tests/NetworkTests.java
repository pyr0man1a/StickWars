package com.wargames.client.tests;

import static org.junit.Assert.*;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;

import org.junit.Before;
import org.junit.Test;

import com.wargames.client.communication.packet.outgoing.*;
import com.wargames.client.communication.packet.incoming.IncomingPacketList;

public class NetworkTests {

	private DatagramSocket socket;
	
	private final String Address = "127.0.0.1";
	private final int PORT = 31111;
	
	@Before
	public void setUp() throws Exception {
		socket = new DatagramSocket();
	}

	@Test
	public void testAccountCreation() {
		byte[] data = new LoginPacket("TestAcc", "testpass").toByteArray();
		byte[] data2 = new LobbyJoinPacket((short)1234).toByteArray();
				
		InetAddress address;
		try {
			address = InetAddress.getByName(Address);
			DatagramPacket packet = new DatagramPacket(data, data.length, address, PORT);
			socket.send(packet);
			packet = new DatagramPacket(data2, data2.length, address, PORT);
			socket.send(packet);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// Try to read back
		byte[] initialBytes = new byte[3];
		DatagramPacket initialPacket = new DatagramPacket(initialBytes, initialBytes.length);
		try {
			socket.receive(initialPacket);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			
		byte[] packetData = initialPacket.getData();
		byte id = packetData[0];
		byte size = packetData[1];
		
		IncomingPacketList.parse(packetData);
		
		System.out.println("ID: " + id);
		System.out.println("Size: " + size);
	}
	
	@Test
	public void testByteInitializer()
	{
		byte[] newByteArray = new byte[5];
		String zero = "0";
		
		byte[] zeroBytes = zero.getBytes();
		for(int i = 0; i < zeroBytes.length; i++)
		{
			newByteArray[i] = zeroBytes[i];
		}
		
		for(int i = 0; i < newByteArray.length; i++)
		{
			System.out.println("Byte Value:"+ newByteArray[i]);
		}
		
		short testValue = 8;
		int provenValue = (int) testValue;
		
		System.out.println("Short: " + testValue);
		System.out.println("Int: " + provenValue);
	}

}
