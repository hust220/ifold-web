package org.ifold.manager;

import java.util.Map;
import java.util.Set;

import org.ifold.daemon.DaemonMonitor;
import org.ifold.util.Fold;
import org.ifold.util.message.Message;
import org.ifold.util.message.NewMessage;

public class ManagerDistributor extends Thread {
	
	//time that distributor waits to start another cycle
	private static final long DISTRIBUTOR_CYCLE_WAIT = 180000;
	//time to wait before probing daemon
	private static final long DAEMON_STATUS_WAIT = 900000;
	
	
	Map daemonMap;
	String address;
	int port;
	ManagerUtil managerUtil;
	
	public ManagerDistributor(Map ref){
		daemonMap = (Map)ref.get("daemonMap");
		address = (String)ref.get("address");
		port = ((Integer)ref.get("port")).intValue();
		managerUtil = (ManagerUtil)ref.get("util");
	}
	
	public void run(){
	

		while(true) {
			Set keySet = daemonMap.keySet();
			Object[] set = keySet.toArray();
			System.out.println("Distributor: Cycle");
			for(int i = 0; i < set.length ;i++ ){
				String key = (String)set[i];
				ManagerDaemonThread mDT = (ManagerDaemonThread)(daemonMap.get(key));
				Message m = null;
				//if the thread is not currently sending a message
				if(!mDT.isOutstanding()) {
					long elapsed = System.currentTimeMillis() - mDT.getBusyTimestamp();
					switch(mDT.getMonitorStatus()){
						case DaemonMonitor.STATUS_UNKNOWN: {
							//unknown status
							System.out.println("\t"+key+": UNKNOWN");
							break;
						}
						
						case DaemonMonitor.STATUS_WAITING:{
							//the status is waiting, so send a new job
							int action = managerUtil.getAction(mDT);
							if (action == ManagerDaemonThread.ACTION_ACCEPT){
								Fold f = managerUtil.getNextFold();
								if(f != null && action == ManagerDaemonThread.ACTION_ACCEPT){
									System.out.println("\t"+key+": WAITING: Sending new Fold: "+f.getId());
									f.setSource(address,port);
									m = new NewMessage(f);
								}
								else {
									System.out.println("\t"+key+": STILL WAITING: Task:"+f);
								}
							}
							else {
								System.out.println("\t"+key+": STILL WAITING: Action:"+action);
							}
							break;
						}
						
						case DaemonMonitor.STATUS_BUSY:{
							System.out.println("\t"+key+": BUSY");
							break;
						}
						
					}
					//if a message was created, send it
					if(m != null)sendMessage(mDT,m);
					//else if some amount of time has elapsed, probe the daemon
					else if(elapsed > DAEMON_STATUS_WAIT) sendMessage(mDT,new Message());
				}
			}
			synchronized(this){
				System.out.println("Distributor: Done");
				try{this.wait(DISTRIBUTOR_CYCLE_WAIT);}
				catch(InterruptedException i){}
			}
		}
		
	}
	
	
	
	private void sendMessage(ManagerDaemonThread mDT, Message m){
		mDT.setOutstanding(true);
		mDT.setBusyTimestamp(System.currentTimeMillis());
		m.setSrc(address,port);
		mDT.sendMessage(m);
	}
}
