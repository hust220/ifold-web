package org.ifold.util.message;

import org.ifold.util.Fold;

/*
 * NewMessage class
 * This class is an extension of the generic 
 * Message class.  Its purpose is to relay a 
 * new Fold object to a Daemon instance.
 */
public class NewMessage extends Message {
	
	private Fold fold;
	
	public NewMessage(){
		super(Message.TYPE_NEW);
	}

	public NewMessage(Fold f){
		super(Message.TYPE_NEW);
		fold = f;
	}
	
	public Fold getFold(){
		return fold;
	}
	
	public void setFold(Fold f){
		fold = f;
	}
}
