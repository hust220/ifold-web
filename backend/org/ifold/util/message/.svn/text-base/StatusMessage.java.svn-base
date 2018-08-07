package org.ifold.util.message;

import org.ifold.util.Fold;
import org.ifold.util.Output;

/*
 * Status Message
 * This is an extension of the Message class.  This 
 * class is used by both the Manager and the Daemon.  
 * It is sent by the Daemin to transmit information 
 * about the status of the Daemon and the current Fold.  
 * It is sent by the Manager as a way to trigger a response 
 * from the Daemon (When used in this manner it contains 
 * no meaningful data).
 */
public class StatusMessage extends Message {
	

	private int monitorStatus;
	private Fold fold;
	private Output output;
	//also include uptime, errors, etc?
	
	
	public StatusMessage(int mStat, Fold f ,Output out){
		super(Message.TYPE_STATUS);
		this.monitorStatus = mStat;
		this.output = out;
		fold = f;
	}
	
	public StatusMessage(Fold f){
		fold = f;
	}
	
	public Output getOutput(){
		return output;
	}

	public Fold getFold() {
		return fold;
	}

	public int getMonitorStatus() {
		return monitorStatus;
	}

	public void setFold(Fold fold) {
		this.fold = fold;
	}

	public void setMonitorStatus(int monitorStatus) {
		this.monitorStatus = monitorStatus;
	}

	public void setOutput(Output output) {
		this.output = output;
	}



	

	
	

}
