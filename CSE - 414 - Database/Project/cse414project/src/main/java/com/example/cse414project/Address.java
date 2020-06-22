package com.example.cse414project;

public class Address {
	private String addressID;
	private String provience;
	private String district;
	private String detail;
	
	public Address(String a, String p, String d, String de) {
		this.addressID = a;
		this.detail = de;
		this.provience = p;
		this.district = d;
	}

	public String getDetail() {
		return detail;
	}

	public void setDetail(String detail) {
		this.detail = detail;
	}

	public String getDistrict() {
		return district;
	}

	public void setDistrict(String district) {
		this.district = district;
	}

	public String getProvience() {
		return provience;
	}

	public void setProvience(String provience) {
		this.provience = provience;
	}

	public String getAddressID() {
		return addressID;
	}

	public void setAddressID(String addressID) {
		this.addressID = addressID;
	}

}
