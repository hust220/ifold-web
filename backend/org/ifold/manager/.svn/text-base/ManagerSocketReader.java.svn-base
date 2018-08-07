package org.ifold.manager;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.Socket;
import java.util.Map;

import org.ifold.util.Output;
import org.ifold.util.message.Message;
import org.ifold.util.message.StatusMessage;

public class ManagerSocketReader extends Thread {

	Socket socket;
	Map daemonMap;
	ManagerDistributor managerDistributor;
	Map referenceMap;
	
	public ManagerSocketReader(Map ref,Socket s){
		referenceMap = ref;
		socket = s;
		daemonMap = (Map)ref.get("daemonMap");
		managerDistributor = (ManagerDistributor)ref.get("distributor");
	}
	
	public synchronized void run(){
		
		ManagerDaemonThread daemonThread = null;
		//System.out.println("SocketReader: Started...");
		try {
		ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
		Object o = ois.readObject();
		socket.close();
		Message m = (Message)o;
		//System.out.println("SocketReader: got message");
		daemonThread = (ManagerDaemonThread)daemonMap.get(m.getSrcAddress()+":"+m.getSrcPort());
		
		if(daemonThread != null){
			int type = m.getType();
			switch(type){
				case Message.TYPE_STATUS:
				{
					//System.out.println("SocketReader: Status Message");
					StatusMessage s = (StatusMessage)m; 
					int fs= 999;
					if (s.getFold() != null)fs = s.getFold().getStatus();
					System.out.println("SocketReader: "+s.getMonitorStatus()+":"+fs  +" From "+s.getSrcAddress()+":"+s.getSrcPort());
					 if(!daemonThread.isOutstanding()) {
						 daemonThread.setMonitorStatus(s.getMonitorStatus());
						 daemonThread.setFold(s.getFold());
						 //set the fold obj in the DB to the correct status
						 while ( !((ManagerUtil)referenceMap.get("util")).updateFold(s.getFold()) ) {
						 }
						 while ( !((ManagerUtil)referenceMap.get("util")).updateDaemon(daemonThread) ) {
						 }
					 }
					 //now process output
					 if(s.getOutput() != null){
						 //Update DB table where output type and fold id match, then save output
						 Output out = s.getOutput();
						 ((ManagerUtil)referenceMap.get("util")).updateOutput(s.getOutput());
						 String fileName = out.getFoldId()+"-"+out.getType()+"-"+out.getFilename();
						 System.out.println("SocketReader: OUTPUT:"+out.getFilename()+": "+out.getData().length);
						 writeFile(fileName,out.getData());
					 }
				break;
				}
				default:{
					//we got something other than a status message, should never happen
					break;
				}
			}
		}
		else {
			//we got a message from a daemon thats not registered, so register it!
			System.out.println("SocketReader: Daemon "+m.getSrcAddress()+":"+m.getSrcPort()+ " not currently registered.");
			String hostName = m.getSrcAddress();
			int port =m.getSrcPort();
			String key = hostName + ":" + port;
			System.out.println(key);
			ManagerDaemonThread mDT = new ManagerDaemonThread(referenceMap,hostName, port);
			mDT.start();
			daemonMap.put(key, mDT);
			
			//we also need to re-write the properties file
		}
		
		}
		catch(IOException e){
			//error in recieving message, do nothing, terminate
		}
		catch(ClassNotFoundException c){
			
		}
		
		synchronized(managerDistributor) {
			managerDistributor.notify();
		}
		
	}
	
	
	private boolean writeFile(String fileName,byte[] data){
		//System.out.println("MSR: writeFile: "+fileName);
		File f = new File(fileName);
		try {
			FileOutputStream fos = new FileOutputStream(f);
			fos.write(data);
			fos.flush();
			fos.close();
			System.out.println("MSR: writeFile: success");
			return true;
		}
		catch(FileNotFoundException e){System.out.println("MSR: writeFile: FileNotFoundException");}
		catch(IOException e){System.out.println("MSR: writeFile: IOException");}
		f.delete();
		System.out.println("MSR: writeFile: failure");
		return false;
	
	}
	
}
