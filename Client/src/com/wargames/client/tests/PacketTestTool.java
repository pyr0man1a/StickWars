package com.wargames.client.tests;

import java.io.Console;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.Scanner;

import com.wargames.client.communication.packet.incoming.IncomingPacketList;
import com.wargames.client.communication.packet.outgoing.LoginPacket;

public class PacketTestTool {

	public static void main(String[] args) {
		DatagramSocket socket;
		try {
			socket = new DatagramSocket();

			
			String Address = "127.0.0.1";
			int PORT = 31111;
			
			byte[] data = new LoginPacket("TestAcc", "testpass").toByteArray();
					
			InetAddress address;
			try {
				address = InetAddress.getByName(Address);
				DatagramPacket packet = new DatagramPacket(data, data.length, address, PORT);
				socket.send(packet);
			} catch (UnknownHostException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			boolean quit = false;
			Scanner console = new Scanner(System.in);
			
			while (!quit)
			{
				System.out.println("Enter packet type: ");
				byte type = (byte)console.nextInt();
				System.out.println("Enter packet size: ");
				byte size = (byte)console.nextInt();
				byte[] packet = new byte[size];
				packet[0] = type;
				packet[1] = size;
				for (int i = 0; i < size-2; i++)
				{
					System.out.println("Enter packet data ("+i+"): ");
					packet[i+2] = (byte)console.nextInt();
				}
				try {
					address = InetAddress.getByName(Address);
					DatagramPacket datagram = new DatagramPacket(packet, packet.length, address, PORT);
					socket.send(datagram);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				socket.setSoTimeout(5000);
				while (true)
				{
					byte[] buffer = new byte[256];
					DatagramPacket response = new DatagramPacket(buffer, buffer.length);
					try {
						socket.receive(response);
					} catch (SocketTimeoutException e){
						break;
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					byte[] packetData = response.getData();
					for (int i = 0; i < packetData[1]; i++ )
					{
						System.out.print(packetData[i]+" ");
						if (i % 16 == 15)
						{
							System.out.println("");
						}
					}
				}
				
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
	
		} catch (SocketException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

}
