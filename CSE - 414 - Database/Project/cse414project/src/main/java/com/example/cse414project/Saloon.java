package com.example.cse414project;

public class Saloon {

	public Saloon(String sln, String nm, String num, String add) {
		this.AddressID=add;
		this.contactNum=num;
		this.SaloonID=sln;
		this.saloonName=nm;
	}
	
	private String SaloonID;
	private String saloonName;
	private String contactNum;
	private String AddressID;
	
	public String getSaloonName() {
		return saloonName;
	}
	public void setSaloonName(String saloonName) {
		this.saloonName = saloonName;
	}
	public String getSaloonID() {
		return SaloonID;
	}
	public void setSaloonID(String saloonID) {
		SaloonID = saloonID;
	}
	public String getContactNum() {
		return contactNum;
	}
	public void setContactNum(String contactNum) {
		this.contactNum = contactNum;
	}
	public String getAddressID() {
		return AddressID;
	}
	public void setAddressID(String addressID) {
		AddressID = addressID;
	}
}
