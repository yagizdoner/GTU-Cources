package com.example.cse414project;

public class Inventory {
	private String saloonID;
	private String inventoryName;
	private String inventoryNumber;
	private String inventoryValue;
	
	public Inventory(String s,String na,String nu,String v) {
		this.inventoryName = na;
		this.inventoryNumber = nu;
		this.inventoryValue = v;
		this.saloonID = s;
	}
	
	public String getSaloonID() {
		return saloonID;
	}
	public void setSaloonID(String saloonID) {
		this.saloonID = saloonID;
	}
	public String getInventoryName() {
		return inventoryName;
	}
	public void setInventoryName(String inventoryName) {
		this.inventoryName = inventoryName;
	}
	public String getInventoryNumber() {
		return inventoryNumber;
	}
	public void setInventoryNumber(String inventoryNumber) {
		this.inventoryNumber = inventoryNumber;
	}
	public String getInventoryValue() {
		return inventoryValue;
	}
	public void setInventoryValue(String inventoryValue) {
		this.inventoryValue = inventoryValue;
	}
}
