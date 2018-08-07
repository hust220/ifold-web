package org.ifold.test;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.Socket;

import org.ifold.util.message.Message;
import org.ifold.util.message.StatusMessage;

public class TestSocketThread extends Thread{
	
	Socket sock;
	
	public TestSocketThread(Socket s){
		sock = s;
	}
	
	public void run(){
		//System.out.println("SocketThread: Running");
		try {
			ObjectInputStream ois = new ObjectInputStream(sock.getInputStream());
			//System.out.println("SocketThread: Reading Object");
			Object o = ois.readObject();
			Message m = (Message)o;
			if(m.getType() == Message.TYPE_STATUS){
				System.out.println("SocketThread: Got Job Update:"+((StatusMessage)(m)).getFold()   );
			}
			sock.close();
		}
		catch(IOException e){
		}
		catch(ClassNotFoundException e){
		}
		
		
	}

}
