package org.ifold.util.message;

import java.io.Serializable;
import java.net.Socket;


/*
 * Message class
 * This class is used to transport messages over 
 * Sockets between a Daemon instance and a Manager 
 * instance.  This class contains the information 
 * requried for message.  It is extended in other 
 * more specific classes to help determine which 
 * type of message is being sent.
 */
public class Message implements Serializable {

	static final long serialVersionUID = 0;
	
	public static final int TYPE_STATUS = 0;
	public static final int TYPE_NEW = 2;
	public static final int TYPE_UNKNOWN = 1;
	
	
	//daemon will ALWAYS send response back to server that sent the message
	private String destAddress;
	private int destPort;
	private String srcAddress;
	private int srcPort;
	private Socket socket;
	private int type;
	
	public Message(){
		this.type = Message.TYPE_UNKNOWN;
	}
	
	public Message(int type) {
		this.type = type;
	}
	
	public int getType() {
		return type;
	}
	
	public void setType(int type) {
		this.type = type;
	}


	public String getDestAddress() {
		return destAddress;
	}

	public int getDestPort() {
		return destPort;
	}

	public String getSrcAddress() {
		return srcAddress;
	}

	public int getSrcPort() {
		return srcPort;
	}

	public Socket getSocket() {
		Socket temp = socket;
		socket = null;
		return temp;
	}
	
	public boolean hasSocket(){
		if(socket != null)return true;
		else return false;
	}

	public void setSocket(Socket socket) {
		this.socket = socket;
	}
	
	public void setDest(String n,int p){
		this.destAddress = n;
		this.destPort = p;
	}

	public void setSrc(String n,int p){
		this.srcAddress = n;
		this.srcPort = p;
	}
}
