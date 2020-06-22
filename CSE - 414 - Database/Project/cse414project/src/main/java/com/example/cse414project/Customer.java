package com.example.cse414project;

public class Customer {
	private String personID;
	private String SaloonID;
	private String membership;
	private String weight;
	private String height;
	
	public Customer(String p,String s,String m,String w,String h) {
		this.height = h;
		this.membership = m;
		this.personID = p;
		this.SaloonID = s;
		this.weight = w;
	}
	
	public String getPersonID() {
		return personID;
	}
	public void setPersonID(String personID) {
		this.personID = personID;
	}
	public String getSaloonID() {
		return SaloonID;
	}
	public void setSaloonID(String saloonID) {
		SaloonID = saloonID;
	}
	public String getWeight() {
		return weight;
	}
	public void setWeight(String weight) {
		this.weight = weight;
	}
	public String getMembership() {
		return membership;
	}
	public void setMembership(String membership) {
		this.membership = membership;
	}
	public String getHeight() {
		return height;
	}
	public void setHeight(String height) {
		this.height = height;
	}	
}
