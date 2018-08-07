package org.ifold.test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

import org.ifold.util.Fold;
import org.ifold.util.message.NewMessage;

public class TestManager {

	/**
	 * @param args
	 */
	
	public static String localHost = "localhost";
	public static int localPort = 12000;
	
	public static String remoteHost = "localhost";
	public static int remotePort = 11000;
	
	
	public static void main(String[] args) {

		TestListener t = new TestListener();
		t.start();

		while (true) {
		
		try {
			System.out.println("TestManager: Watingforinput:");
			(new BufferedReader(new InputStreamReader(System.in))).readLine();
		NewMessage n = new NewMessage();
		n.setFold(new Fold());
		//n.setHostName(localHost);
		//n.setHostPort(localPort);
		//System.out.println("TestManager: opening socket");
		Socket sc = new Socket(remoteHost,remotePort);
		ObjectOutputStream oos = new ObjectOutputStream(sc.getOutputStream());
		//System.out.println("TestManager: writing message...");
		oos.writeObject(n);
		//System.out.println("TestManager: listening for immmediate reply");
		ObjectInputStream ois = new ObjectInputStream(sc.getInputStream());
		Object o = ois.readObject();
		System.out.println("TestManager: got STATUS message back");
		sc.close();
	
		}
		catch(IOException e){
			System.out.println("TestManager: IOExcep");
		}
		catch(ClassNotFoundException f){
			System.out.println("TestManager: ClassNotFoundExcep");
		}

		}
	}

}
