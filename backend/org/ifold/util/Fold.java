package org.ifold.util;

import java.io.Serializable;
import java.util.ArrayList;

public class Fold implements Serializable{

	public static final long serialVersionUID = 30000;
	
	public static final int STATUS_QUEUED = 1;
	public static final int STATUS_PENDING = 2;
	public static final int STATUS_RUNNING = 3;
	public static final int STATUS_PROCESSING = 4;
	public static final int STATUS_COMPLETE = 5;
	public static final int STATUS_PAUSED = 6;
	public static final int STATUS_TERMINATED = 7;
	public static final int STATUS_UNKNOWN = 8;
	
	public static final int FOLD_TYPE_UNFOLD = 1;
	public static final int FOLD_TYPE_FOLD = 2;
	public static final int FOLD_TYPE_THERMOSCAN = 3;
	public static final int FOLD_TYPE_ANNEAL = 4;
	public static final int FOLD_TYPE_PFOLD = 5;
	
	//back-end stuff
	private String sourceAddress;
	private int sourcePort;
	private String daemonAddress;
	private int daemonPort;
	private ArrayList messages;
	
	//task properties
	private String name;
	private int id;
	private int status;
	
	//task parameters
	String pdbCode;
	String pdbFileName;
	String pdbDecoyFileName;
	int foldType;
	int modelType;
	int simTime;
	int numIterations;
	float initialTemp;
	float finalTemp;
	float heatExchCo;
	float transTemp;
	float[] temps;
	
	//pdb File data
	byte[] pdbData;
	byte[] pdbDecoyData;
	
	//output parameters
	int trajMin;
	int trajMax;
	int trajInterval;
	boolean contactFreqMap;
	boolean cvVsTemp;
	int equilOffset;
	boolean energyVsTemp;
	boolean energyVsTime;
	boolean radiusVsTime;
	boolean mov;
	boolean echoRms;
	
	public boolean getEchoRms() {
		return echoRms;
	}

	public void setEchoRms(boolean echoRms) {
		this.echoRms = echoRms;
	}

	public boolean getMov() {
		return mov;
	}

	public void setMov(boolean mov) {
		this.mov = mov;
	}

	public Fold(){
		this.messages = new ArrayList();
	}
	
	public void setParameters(
			int foldType,
			int modelType,
			int simTime,
			int numIterations,
			float initialTemp,
			float finalTemp,
			float heatExchCo,
			float transTemp,
			float[] temps,
			int trajMax,
			int trajMin,
			int trajInterval,
			boolean contactFreqMap,
			boolean cvVsTemp,
			int equilOffset,
			boolean energyVsTemp,
			boolean energyVsTime,
			boolean radiusVsTime,
			boolean mov,
			boolean echoRms,
			String pdbDecoyFileName,
			byte[] pdbDecoyData
			){
		this.foldType = foldType;
		this.modelType = modelType;
		this.simTime = simTime;
		this.numIterations = numIterations;
		this.initialTemp = initialTemp;
		this.finalTemp = finalTemp;
		this.heatExchCo = heatExchCo;
		this.transTemp = transTemp;
		this.temps = temps;
		this.trajMin = trajMin;
		this.trajMax = trajMax;
		this.trajInterval = trajInterval;
		this.contactFreqMap = contactFreqMap;
		this.cvVsTemp = cvVsTemp;
		this.equilOffset = equilOffset;
		this.energyVsTemp = energyVsTemp;
		this.energyVsTime = energyVsTime;
		this.radiusVsTime = radiusVsTime;
		this.mov = mov;
		this.echoRms = echoRms;
		this.pdbDecoyFileName = pdbDecoyFileName;
		this.pdbDecoyData = pdbDecoyData;
	}
	
	public Fold(String name,int id,int status){
		this.name = name;
		this.id = id;
		this.status = status;
		this.messages = new ArrayList();
	}
	
	
	public void setPDB(String pdbCode,String pdbFileName,byte[] pdbData){
		this.pdbCode = pdbCode;
		this.pdbFileName = pdbFileName;
		this.pdbData = pdbData;
	}
	
	public void setPFold(String pdbDecoyFileName,byte[] pdbDecoyData,float transTemp,int numIterations){
		this.foldType = Fold.FOLD_TYPE_PFOLD;
		this.pdbDecoyFileName = pdbDecoyFileName;
		this.pdbDecoyData = pdbDecoyData;
		this.transTemp = transTemp;
		this.numIterations = numIterations;
	}
	
	public void setUnfold(float initialTemp,float finalTemp,float heatExchCo,int simTime,int trajModelType,int trajMin,int trajMax,int trajInterval,boolean energyVsTemp,boolean energyVsTime,boolean radiusVsTime){
		this.foldType = Fold.FOLD_TYPE_UNFOLD;
		this.initialTemp = initialTemp;
		this.finalTemp = finalTemp;
		this.heatExchCo = heatExchCo;
		this.simTime = simTime;
		this.trajMin = trajMin;
		this.trajMax = trajMax;
		this.trajInterval = trajInterval;
		this.energyVsTemp = energyVsTemp;
		this.energyVsTime = energyVsTime;
		this.radiusVsTime = radiusVsTime;
	}
	
	
	public void setAnneal(float initialTemp,float finalTemp,float heatExchCo,int numIterations,int simTime,int trajModelType,int trajMin,int trajMax,int trajInterval,boolean energyVsTemp,boolean energyVsTime,boolean radiusVsTime){
		this.foldType = Fold.FOLD_TYPE_ANNEAL;
		this.initialTemp = initialTemp;
		this.finalTemp = finalTemp;
		this.heatExchCo = heatExchCo;
		this.numIterations = numIterations;
		this.simTime = simTime;
		this.trajMin = trajMin;
		this.trajMax = trajMax;
		this.trajInterval = trajInterval;
		this.energyVsTemp = energyVsTemp;
		this.energyVsTime = energyVsTime;
		this.radiusVsTime = radiusVsTime;
	}
	
	
	public void setThermoscan(float[] temps,float heatExchCo,int simTime,int trajModelType,int trajMin,int trajMax,int trajInterval,boolean energyVsTemp,boolean contactFreqMap,boolean cvVsTemp,int equilOffset){
		this.temps = temps;
		this.heatExchCo = heatExchCo;
		this.simTime = simTime;
		this.trajMin = trajMin;
		this.trajMax = trajMax;
		this.trajInterval = trajInterval;
		this.energyVsTemp = energyVsTemp;
		this.contactFreqMap = contactFreqMap;
		this.cvVsTemp = cvVsTemp;
		this.equilOffset = equilOffset;
	}
	
	
	
	
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public String getSourceAddress() {
		return sourceAddress;
	}

	public int getSourcePort() {
		return sourcePort;
	}

	public void setSource(String a,int p){
		sourceAddress = a;
		sourcePort = p;
	}
	
	public void setDaemon(String a,int p){
		daemonAddress = a;
		daemonPort = p;
	}

	public String getDaemonAddress() {
		return daemonAddress;
	}

	public int getDaemonPort() {
		return daemonPort;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public float getFinalTemp() {
		return finalTemp;
	}

	public int getFoldType() {
		return foldType;
	}

	public float getHeatExchCo() {
		return heatExchCo;
	}

	public float getInitialTemp() {
		return initialTemp;
	}

	public int getNumIterations() {
		return numIterations;
	}

	public String getPdbCode() {
		return pdbCode;
	}

	public String getPdbDecoyFileName() {
		return pdbDecoyFileName;
	}

	public String getPdbFileName() {
		return pdbFileName;
	}

	public int getSimTime() {
		return simTime;
	}

	public float getTransTemp() {
		return transTemp;
	}

	public byte[] getPdbData() {
		return pdbData;
	}

	public byte[] getPdbDecoyData() {
		return pdbDecoyData;
	}

	public void setFoldType(int foldType) {
		this.foldType = foldType;
	}

	public void setPdbCode(String pdbCode) {
		this.pdbCode = pdbCode;
	}

	public void setPdbDecoyFileName(String pdbDecoyFileName) {
		this.pdbDecoyFileName = pdbDecoyFileName;
	}

	public void setPdbFileName(String pdbFileName) {
		this.pdbFileName = pdbFileName;
	}

	public void setTransTemp(float transTemp) {
		this.transTemp = transTemp;
	}

	public void setPdbDecoyData(byte[] pdbDecoyData) {
		this.pdbDecoyData = pdbDecoyData;
	}

	public void setNumIterations(int numIterations) {
		this.numIterations = numIterations;
	}

	public void setPdbData(byte[] pdbData) {
		this.pdbData = pdbData;
	}
	
	public void addMessage(String msg){
		messages.add(msg);
	}
	
	public ArrayList getMessages(){
		return messages;
	}

	public int getModelType() {
		return modelType;
	}

	public int getTrajInterval() {
		return trajInterval;
	}

	public int getTrajMax() {
		return trajMax;
	}

	public int getTrajMin() {
		return trajMin;
	}

}
