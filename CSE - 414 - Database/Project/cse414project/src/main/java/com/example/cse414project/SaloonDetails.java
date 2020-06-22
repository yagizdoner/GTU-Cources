package com.example.cse414project;

public class SaloonDetails {
	private String SaloonID;
	private String staffNum;
	private String customerNum;
	private String courceNum;
	private String inventoryNum;
	private String monthlyPrice;
	private String profitID;
	
	public SaloonDetails(String sId,String sN,String cN,String coN,String iN,String mP,String pr) {
		this.SaloonID = sId;
		this.staffNum = sN;
		this.customerNum = cN;
		this.courceNum = coN;
		this.inventoryNum = iN;
		this.monthlyPrice = mP;
		this.profitID = pr;
	}
	
	public String getSaloonID() {
		return SaloonID;
	}
	public void setSaloonID(String saloonID) {
		SaloonID = saloonID;
	}
	public String getStaffNum() {
		return staffNum;
	}
	public void setStaffNum(String staffNum) {
		this.staffNum = staffNum;
	}
	public String getCustomerNum() {
		return customerNum;
	}
	public void setCustomerNum(String customerNum) {
		this.customerNum = customerNum;
	}
	public String getCourceNum() {
		return courceNum;
	}
	public void setCourceNum(String courceNum) {
		this.courceNum = courceNum;
	}
	public String getInventoryNum() {
		return inventoryNum;
	}
	public void setInventoryNum(String inventoryNum) {
		this.inventoryNum = inventoryNum;
	}
	public String getMonthlyPrice() {
		return monthlyPrice;
	}
	public void setMonthlyPrice(String monthlyPrice) {
		this.monthlyPrice = monthlyPrice;
	}
	public String getProfitID() {
		return profitID;
	}
	public void setProfitID(String profitID) {
		this.profitID = profitID;
	}
}
