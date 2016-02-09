package com.wargames.client.gui;

import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import javax.swing.UIManager;

import com.wargames.client.communication.packet.incoming.IncomingPacketList;
import com.wargames.client.communication.packet.outgoing.LobbyJoinPacket;
import com.wargames.client.communication.packet.outgoing.LoginPacket;
import com.wargames.client.helpers.SocketSingleton;

public class LoginWindow extends JPanel implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JTextField username;
	private JPasswordField password;
	private JButton loginButton;
	private JFrame f;

	public LoginWindow()
	{
		username = new JTextField(16);
		this.add(username);
		password = new JPasswordField(16);
		password.setActionCommand("Login");
		password.addActionListener(this);

		this.add(password);

		loginButton = new JButton("Login");
		loginButton.setActionCommand("Login");
		loginButton.addActionListener(this);

		this.add(loginButton);

		// create application frame and set visible
		//
		f = new JFrame();
		f.setVisible(true);
		f.setResizable(true);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.add(this);
		f.setSize(800, 624);
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		username.setLocation(300,300);
		password.setLocation(300,340);
		loginButton.setLocation(400, 400);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		String cmd = e.getActionCommand();
		if(cmd.equals("Login"))
		{
			char[] input = password.getPassword();
			String inputPassword = new String(input);
			System.out.println("Password: " + inputPassword);
			System.out.println("Username: " + username.getText());
			login(username.getText(), inputPassword);
		}

	}

	public void login(String username, String password)
	{	
		byte[] data = new LoginPacket(username, password).toByteArray();
		InetAddress address;
		DatagramSocket socket;
		try {
			socket = SocketSingleton.getInstance().socket;
			PasswordValidator validator = new PasswordValidator(this);
			validator.execute();
			address = InetAddress.getByName("50.65.25.35");
			DatagramPacket packet = new DatagramPacket(data, data.length, address, 31111);
			socket.send(packet);
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public static void main(String[] args)
	{
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				UIManager.put("swing.boldMetal", Boolean.FALSE);
				new LoginWindow();
			}
		});
	}

	class PasswordValidator extends SwingWorker<Void, Integer> {

		private DatagramSocket socket;
		private JPanel client;

		public PasswordValidator(JPanel client)
		{
			this.socket = SocketSingleton.getInstance().socket;
			this.client = client;
		}

		@Override
		protected Void doInBackground() throws Exception {
			System.out.println("Starting to read...");

			try {

				// Try to read back
				byte[] initialBytes = new byte[3];
				DatagramPacket initialPacket = new DatagramPacket(initialBytes, initialBytes.length);

				socket.receive(initialPacket);
				byte[] packetData = initialPacket.getData();
				byte id = packetData[0];
				byte size = packetData[1];

				IncomingPacketList.parse(packetData, client);

				System.out.println("ID: " + id);
				System.out.println("Size: " + size);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return null;
		}

		@Override
		protected void done() {

		}

	}
}
