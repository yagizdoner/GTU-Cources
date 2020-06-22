package com.example.cse414project;

public class Person {
	public Person(String pID,String nm,String sm, String ino,String gen,
			String bdate, String bloo, String cNum, String aID, String sta){
		this.AddressID = aID;
		this.birthdate = bdate;
		this.blood = bloo;
		this.contactNumber = cNum;
		this.gender = gen;
		this.IdentityNo = ino;
		this.name = nm;
		this.PersonID = pID;
		this.status = sta;
		this.surname = sm; 
	}
	
	private String PersonID;
	private String name;
	private String surname;
	private String IdentityNo;
	private String gender;
	private String birthdate;
	private String blood;
	private String contactNumber;
	private String AddressID;
	private String status;
	
	public String getPersonID() {
		return PersonID;
	}
	public void setPersonID(String personID) {
		PersonID = personID;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSurname() {
		return surname;
	}
	public void setSurname(String surname) {
		this.surname = surname;
	}
	public String getGender() {
		return gender;
	}
	public void setGender(String gender) {
		this.gender = gender;
	}
	public String getIdentityNo() {
		return IdentityNo;
	}
	public void setIdentityNo(String identityNo) {
		IdentityNo = identityNo;
	}
	public String getBirthdate() {
		return birthdate;
	}
	public void setBirthdate(String birthdate) {
		this.birthdate = birthdate;
	}
	public String getBlood() {
		return blood;
	}
	public void setBlood(String blood) {
		this.blood = blood;
	}
	public String getContactNumber() {
		return contactNumber;
	}
	public void setContactNumber(String contactNumber) {
		this.contactNumber = contactNumber;
	}
	public String getAddressID() {
		return AddressID;
	}
	public void setAddressID(String addressID) {
		AddressID = addressID;
	}
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
}
