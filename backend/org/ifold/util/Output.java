package org.ifold.util;

import java.io.Serializable;

public class Output implements Serializable{
	
	public static final long serialVersionUID = 30001;
	
	public static final int TYPE_CONTACT_FREQ_MAP = 1;
	public static final int TYPE_CV_VS_TEMP = 2;
	public static final int TYPE_ENERGY_VS_TEMP = 3;
	public static final int TYPE_ENERGY_VS_TIME = 4;
	public static final int TYPE_RADIUS_VS_TIME = 5;
	public static final int TYPE_PFOLD_REPORT = 6;
	public static final int TYPE_ANNEAL_REPORT = 7;
	public static final int TYPE_TRAJECTORY = 8;
	public static final int TYPE_MOV = 9;
	public static final int TYPE_ECHO_RMS = 10;
	public static final int TYPE_UNKNOWN = 256;
	
	public static final int MODEL_TYPE_ONE = 1;
	public static final int MODEL_TYPE_TWO = 2;
	public static final int MODEL_TYPE_FOUR = 3;
	public static final int MODEL_TYPE_QUASI = 4;
	public static final int MODEL_TYPE_ALL = 5;
	
	private int foldId;
	private int type;
	private String fileName;
	private byte[] data;
	
	public byte[] getData() {
		return data;
	}

	public String getFilename() {
		return fileName;
	}

	public int getType() {
		return type;
	}

	public int getFoldId(){
		return foldId;
	}
	
	public Output(int type,int foldId, String fileName, byte[] data) {
		this.type = type;
		this.fileName = fileName;
		this.data = data;
		this.foldId = foldId;
	}
	
}
