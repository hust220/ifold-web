package org.ifold.test;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;

import org.ifold.util.message.Message;

public class TestListener extends Thread{

	/**
	 * @param args
	 */
	public TestListener() {
		



	}
	
	public void run() {
		try {
			ServerSocket ss = new ServerSocket(12000);
			while (true) {
				//System.out.println("TestListener: listening...");
				Socket s = ss.accept();
				//System.out.println("TestListener: Got Connection...");
				TestSocketThread st = new TestSocketThread(s);
				st.start();
				}
			}
		catch(IOException e){
			
		}
		
	}

}
