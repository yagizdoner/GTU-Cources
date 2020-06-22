package com.example.cse414project;

public class Manager {
	private String PersonID;
	private String price;
	private String SaloonID;
	
	public Manager(String p, String pr, String ad) {
		this.PersonID = p;
		this.price = pr;
		this.SaloonID = ad;
	}
	
	public String getPersonID() {
		return PersonID;
	}
	public void setPersonID(String personID) {
		PersonID = personID;
	}
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}

	public String getSaloonID() {
		return SaloonID;
	}

	public void setSaloonID(String saloonID) {
		SaloonID = saloonID;
	}
	
	
}
