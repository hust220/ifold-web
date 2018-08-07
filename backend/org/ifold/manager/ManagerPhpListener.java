package org.ifold.manager;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;


public class ManagerPhpListener extends Thread {
	
	private static final int LISTEN_PORT = 29999;
	
	private ManagerDistributor managerDistributor;
	
	public ManagerPhpListener(Map ref){
		this.managerDistributor = (ManagerDistributor)ref.get("distributor");
	}
	
	public void run(){
		
		
		System.out.println("PhpListener: Started...");
		ServerSocket server = null;
		Socket connection;
		boolean error = false;
		
		while(true) {
			try {
				if(error || server == null) {
					if(server != null) server.close();
					server =  new ServerSocket(LISTEN_PORT);
					error = false;
				}
				connection = server.accept();
				//int b = connection.getInputStream().read();
				System.out.println("PHPListener got connection:");
				connection.close();
				synchronized(managerDistributor){managerDistributor.notify();}
			}
			catch(IOException e){
				error = true;
			}
		}
		
	}
	

}
