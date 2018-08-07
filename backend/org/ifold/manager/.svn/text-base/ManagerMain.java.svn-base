package org.ifold.manager;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class ManagerMain {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		try {
			
			// get local address
			String address = InetAddress.getLocalHost().getHostAddress();
			System.out.println("Main: address: " + address);
			
			// Map to store Daemon object references
			Map daemonMap = Collections.synchronizedMap(new HashMap());
			
			// Map to provide references to threads
			Map referenceMap = Collections.synchronizedMap(new HashMap());

			referenceMap.put("dbAddress","jdbc:mysql://152.23.193.101/ifold");
			referenceMap.put("dbLogin","manager");
			referenceMap.put("dbPassword","manag3r");
			referenceMap.put("address", address);
			referenceMap.put("port", new Integer(30000));
			referenceMap.put("phpPort", new Integer(29999));
			referenceMap.put("daemonMap", daemonMap);

			ManagerUtil util = new ManagerUtil(referenceMap);
			referenceMap.put("util", util);
			ManagerDistributor mD = new ManagerDistributor(referenceMap);
			referenceMap.put("distributor", mD);
			ManagerDaemonListener mL = new ManagerDaemonListener(referenceMap);
			referenceMap.put("daemonListener", mL);
			ManagerPhpListener mPL = new ManagerPhpListener(referenceMap);
			referenceMap.put("phpListener", mPL);
			
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("manager.properties")));
			String line = br.readLine();
			while (line != null) {
				String[] vals = line.split(":");
				String hostName = vals[0];
				int port = Integer.parseInt(vals[1]);
				String key = hostName + ":" + port;
				System.out.println(key);
				ManagerDaemonThread mDT = new ManagerDaemonThread(referenceMap,hostName, port);
				mDT.start();
				daemonMap.put(key, mDT);
				line = br.readLine();
			}

			

			mL.start();
			mD.start();
			mPL.start();

		} catch (IOException e) {
		}

	}
}
