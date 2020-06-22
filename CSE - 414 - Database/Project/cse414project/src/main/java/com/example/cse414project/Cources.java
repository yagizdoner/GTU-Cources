package com.example.cse414project;

public class Cources {
	private String SaloonID;
	private String courceName;
	private String courceQuota;
	private String PersonID;
	
	public Cources(String s,String cn,String cq,String p) {
		this.courceName = cn;
		this.courceQuota = cq;
		this.PersonID = p;
		this.SaloonID = s;
	}
	
	public String getSaloonID() {
		return SaloonID;
	}
	public void setSaloonID(String saloonID) {
		SaloonID = saloonID;
	}
	public String getCourceName() {
		return courceName;
	}
	public void setCourceName(String courceName) {
		this.courceName = courceName;
	}
	public String getCourceQuota() {
		return courceQuota;
	}
	public void setCourceQuota(String courceQuota) {
		this.courceQuota = courceQuota;
	}
	public String getPersonID() {
		return PersonID;
	}
	public void setPersonID(String personID) {
		PersonID = personID;
	}
}
