package com.example.cse414project;

public class Staff {
	private String personID;
	private String saloonID;
	private String price;
	
	public Staff(String p,String s,String pr) {
		this.personID = p;
		this.price = pr;
		this.saloonID = s;
	}
	
	public String getPersonID() {
		return personID;
	}
	public void setPersonID(String personID) {
		this.personID = personID;
	}
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
	public String getSaloonID() {
		return saloonID;
	}
	public void setSaloonID(String saloonID) {
		this.saloonID = saloonID;
	}
}
