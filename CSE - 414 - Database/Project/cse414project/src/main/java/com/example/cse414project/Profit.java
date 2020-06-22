package com.example.cse414project;

public class Profit {
	private String profit;
	private String ProfitID;

	public Profit(String i, String p) {
		this.profit = p;
		this.ProfitID = i;
	}
	
	public String getProfit() {
		return profit;
	}

	public void setProfit(String profit) {
		this.profit = profit;
	}

	public String getProfitID() {
		return ProfitID;
	}

	public void setProfitID(String profitID) {
		ProfitID = profitID;
	}
	
}
