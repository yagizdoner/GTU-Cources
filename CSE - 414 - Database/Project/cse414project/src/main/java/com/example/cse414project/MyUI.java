
/************************************
 *    YAĞIZ DÖNER					*
 * 									*
 *    141044062						*
 *    								*
 *    CSE 414 - DATABASE - PROJECT  *
 * 									*
 ***********************************/



package com.example.cse414project;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import javax.servlet.annotation.WebServlet;
import com.vaadin.annotations.Theme;
import com.vaadin.annotations.VaadinServletConfiguration;
import com.vaadin.server.Page;
import com.vaadin.server.VaadinRequest;
import com.vaadin.server.VaadinServlet;
import com.vaadin.ui.Button;
import com.vaadin.ui.Grid;
import com.vaadin.ui.HorizontalLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Window;

/**
 * This UI is the application entry point. A UI may either represent a browser window 
 * (or tab) or some part of an HTML page where a Vaadin application is embedded.
 * <p>
 * The UI is initialized using {@link #init(VaadinRequest)}. This method is intended to be 
 * overridden to add component to the user interface and initialize non-component functionality.
 */
@Theme("mytheme")
public class MyUI extends UI {

	private static final long serialVersionUID = 1L;
	HorizontalLayout hlayout = new HorizontalLayout();
	VerticalLayout vlayout = new VerticalLayout();
	HorizontalLayout hlayout1 = new HorizontalLayout();
	Label label = new Label();
	List<Saloon> saloons = new ArrayList<Saloon>();
	List<Address> addresses = new ArrayList<Address>(); 
	List<SaloonDetails> saloondetails = new ArrayList<SaloonDetails>(); 
	List<Profit> profits = new ArrayList<Profit>(); 
	List<Person> people = new ArrayList<Person>();
	List<Customer> customers = new ArrayList<Customer>(); 
	List<Staff> staffs = new ArrayList<Staff>(); 
	List<Cources> cources = new ArrayList<Cources>(); 
	List<Manager> managers = new ArrayList<Manager>(); 
	List<Inventory> inventories = new ArrayList<Inventory>(); 
	
    @Override
    protected void init(VaadinRequest vaadinRequest) {
    	
    	// READ DATABASE for Initialization
    	try {
    		Class.forName("org.h2.Driver");
    		Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
    		
    		String data = "select * from saloon";
    		PreparedStatement statement = connection.prepareStatement(data);
    		ResultSet set = statement.executeQuery();
    		while(set.next()) {
    			String sId = set.getString("saloonid");
    			String name = set.getString("saloonname");
    			String cNum = set.getString("contactnumber");
    			String aId = set.getString("addressid");
    			Saloon s = new Saloon(sId,name,cNum,aId);
    			saloons.add(s);
    		}
    		set.close();
    		
    		data = "select * from address";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String aId = set.getString("addressid");
    			String pro = set.getString("provience");
    			String dist = set.getString("district");
    			String det = set.getString("detail");
    			Address s = new Address(aId,pro,dist,det);
    			addresses.add(s);
    		}
    		set.close();
    		
    		data = "select * from saloondetail";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String sid = set.getString("saloonid");
    			String st = set.getString("staffnumber");
    			String cu = set.getString("customernumber");
    			String co = set.getString("courcenumber");
    			String in = set.getString("inventorynumber");
    			String pri = set.getString("price");
    			String pro = set.getString("profitid");
    			SaloonDetails s = new SaloonDetails(sid,st,cu,co,in,pri,pro);
    			saloondetails.add(s);
    		}
    		set.close();
    		
    		data = "select * from profit";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String pId = set.getString("profitid");
    			String pro = set.getString("monthlyprofit");
    			Profit s = new Profit(pId,pro);
    			profits.add(s);
    		}
    		set.close();
    		
    		data = "select * from person";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String pid = set.getString("personid");
    			String n = set.getString("name");
    			String su = set.getString("surname");
    			String i = set.getString("identityno");
    			String g = set.getString("gender");
    			String b = set.getString("birthdate");
    			String bl = set.getString("blood");
    			String c = set.getString("contactnumber");
    			String aid = set.getString("addressid");
    			String st = set.getString("status");
    			Person s = new Person(pid,n,su,i,g,b,bl,c,aid,st);
    			people.add(s);
    		}
    		set.close();
    		
    		data = "select * from customer";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String pid = set.getString("personid");
    			String sid = set.getString("saloonid");
    			String mem = set.getString("membership");
    			String we = set.getString("weight");
    			String he = set.getString("height");
    			Customer s = new Customer(pid,sid,mem,we,he);
    			customers.add(s);
    		}
    		set.close();
    		
    		data = "select * from staff";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String pid = set.getString("personid");
    			String sid = set.getString("saloonid");
    			String pri = set.getString("price");
    			Staff s = new Staff(pid,sid,pri);
    			staffs.add(s);
    		}
    		set.close();
    		
    		data = "select * from cource";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String sid = set.getString("personid");
    			String cn = set.getString("courcename");
    			String cq = set.getString("courcequota");
    			String pid = set.getString("saloonid");
    			Cources s = new Cources(pid,cn,cq,sid);
    			cources.add(s);
    		}
    		set.close();
    		
    		data = "select * from manager";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String pid = set.getString("personid");
    			String sid = set.getString("saloonid");
    			String pri = set.getString("price");
    			Manager s = new Manager(pid,sid,pri);
    			managers.add(s);
    		}
    		set.close();
    	
    		data = "select * from inventory";
    		statement = connection.prepareStatement(data);
    		set = statement.executeQuery();
    		while(set.next()) {
    			String sid = set.getString("saloonid");
    			String na = set.getString("inventoryname");
    			String nu = set.getString("inventorynumber");
    			String val = set.getString("inventoryvalue");
    			Inventory s = new Inventory(sid,na,nu,val);
    			inventories.add(s);
    		}
    		set.close();
    	}
    	catch(SQLException e1){
    		e1.printStackTrace();
    	}
    	catch(ClassNotFoundException e2) {
    		e2.printStackTrace();
    	}
    	
    	
        // TABLES -----------------------------------------------------------------------------
    	
    	// SALOON
    	Grid<Saloon> saloonGrid = new Grid<>();
    	saloonGrid.setSizeFull();
    	saloonGrid.setCaption("SALOONS");
    	saloonGrid.addColumn(Saloon::getSaloonID).setCaption("Saloon ID");
    	saloonGrid.addColumn(Saloon::getSaloonName).setCaption("Saloon Name");
    	saloonGrid.addColumn(Saloon::getContactNum).setCaption("Contact Number");
    	saloonGrid.addColumn(Saloon::getAddressID).setCaption("Address ID");
    	saloonGrid.setItems(saloons);
    	
    	// PROFIT DETAIL
    	Grid<Profit> profitGrid = new Grid<>();
    	profitGrid.setSizeFull();
    	profitGrid.setCaption("PROFITS");
    	profitGrid.addColumn(Profit::getProfitID).setCaption("Profit ID");
    	profitGrid.addColumn(Profit::getProfit).setCaption("Monthly Profit");
    	profitGrid.setItems(profits);
    	
        // ADDRESS
    	Grid<Address> addressGrid = new Grid<>();
    	addressGrid.setSizeFull();
    	addressGrid.setCaption("ADDRESSES");
    	addressGrid.addColumn(Address::getAddressID).setCaption("Address ID");
    	addressGrid.addColumn(Address::getProvience).setCaption("Provience");
    	addressGrid.addColumn(Address::getDistrict).setCaption("District");
    	addressGrid.addColumn(Address::getDetail).setCaption("Detail");
    	addressGrid.setItems(addresses);
    	
    	// SALOON DETAIL
    	Grid<SaloonDetails> saloonDetailGrid = new Grid<>();
    	saloonDetailGrid.setSizeFull();
    	saloonDetailGrid.setCaption("SALOON DETAILS");
    	saloonDetailGrid.addColumn(SaloonDetails::getSaloonID).setCaption("Saloon ID");
    	saloonDetailGrid.addColumn(SaloonDetails::getStaffNum).setCaption("Number of Staff");
    	saloonDetailGrid.addColumn(SaloonDetails::getCustomerNum).setCaption("Number of Customer");
    	saloonDetailGrid.addColumn(SaloonDetails::getCourceNum).setCaption("Number of Cource");
    	saloonDetailGrid.addColumn(SaloonDetails::getInventoryNum).setCaption("Number of Inventory");
    	saloonDetailGrid.addColumn(SaloonDetails::getMonthlyPrice).setCaption("Monthly Price");
    	saloonDetailGrid.addColumn(SaloonDetails::getProfitID).setCaption("Profit ID");
    	saloonDetailGrid.setItems(saloondetails);
    	
    	// PERSON
    	Grid<Person> personGrid = new Grid<>();
    	personGrid.setSizeFull();
    	personGrid.setCaption("PEOPLE");
    	personGrid.addColumn(Person::getPersonID).setCaption("Person ID");
    	personGrid.addColumn(Person::getName).setCaption("Name");
    	personGrid.addColumn(Person::getSurname).setCaption("Surname");
    	personGrid.addColumn(Person::getIdentityNo).setCaption("Identity No");
    	personGrid.addColumn(Person::getGender).setCaption("Gender");
    	personGrid.addColumn(Person::getBirthdate).setCaption("Birth Date");
    	personGrid.addColumn(Person::getBlood).setCaption("Blood");
    	personGrid.addColumn(Person::getContactNumber).setCaption("Contact Number");
    	personGrid.addColumn(Person::getAddressID).setCaption("Address ID");
    	personGrid.addColumn(Person::getStatus).setCaption("Status");
    	personGrid.setItems(people);
    	
    	// CUSTOMER
    	Grid<Customer> customerGrid = new Grid<>();
    	customerGrid.setSizeFull();
    	customerGrid.setCaption("CUSTOMERS");
    	customerGrid.addColumn(Customer::getPersonID).setCaption("Person ID");
    	customerGrid.addColumn(Customer::getSaloonID).setCaption("Saloon ID");
    	customerGrid.addColumn(Customer::getMembership).setCaption("Membership");
    	customerGrid.addColumn(Customer::getWeight).setCaption("Weight");
    	customerGrid.addColumn(Customer::getHeight).setCaption("Height");
    	customerGrid.setItems(customers);
    	
    	// STAFF
    	Grid<Staff> staffGrid = new Grid<>();
    	staffGrid.setSizeFull();
    	staffGrid.setCaption("STAFFS");
    	staffGrid.addColumn(Staff::getPersonID).setCaption("Person ID");
    	staffGrid.addColumn(Staff::getSaloonID).setCaption("Saloon ID");
    	staffGrid.addColumn(Staff::getPrice).setCaption("Price");
    	staffGrid.setItems(staffs);
    	
    	// COURCES
    	Grid<Cources> courceGrid = new Grid<>();
    	courceGrid.setSizeFull();
    	courceGrid.setCaption("COURCES");
    	courceGrid.addColumn(Cources::getSaloonID).setCaption("Saloon ID");
    	courceGrid.addColumn(Cources::getCourceName).setCaption("Cource Name");
    	courceGrid.addColumn(Cources::getCourceQuota).setCaption("Quota");
    	courceGrid.addColumn(Cources::getPersonID).setCaption("Cource Staff ID");
    	courceGrid.setItems(cources);
    	  	
    	// MANAGER
    	Grid<Manager> managerGrid = new Grid<>();
    	managerGrid.setSizeFull();
    	managerGrid.setCaption("MANAGERS");
    	managerGrid.addColumn(Manager::getPersonID).setCaption("Person ID");
    	managerGrid.addColumn(Manager::getSaloonID).setCaption("Saloon ID");
    	managerGrid.addColumn(Manager::getPrice).setCaption("Price");
    	managerGrid.setItems(managers);
    	
    	// INVENTORY
    	Grid<Inventory> inventoryGrid = new Grid<>();
    	inventoryGrid.setSizeFull();
    	inventoryGrid.setCaption("INVENTORIES");
    	inventoryGrid.addColumn(Inventory::getSaloonID).setCaption("Saloon ID");
    	inventoryGrid.addColumn(Inventory::getInventoryName).setCaption("Inventory Name");
    	inventoryGrid.addColumn(Inventory::getInventoryNumber).setCaption("Inventory Number");
    	inventoryGrid.addColumn(Inventory::getInventoryValue).setCaption("Inventory Value");
    	inventoryGrid.setItems(inventories);
    	
    	
    // BUTTONS ---------------------------------------------------------------------------
    	
    	// SALOON
    	Button button = new Button("Saloon");
    	button.addClickListener(e ->{
    		// Create a sub-window and set the content
            Window subWindow = new Window("Add Customer");
            VerticalLayout subContent = new VerticalLayout();
            VerticalLayout subContent1 = new VerticalLayout();
            HorizontalLayout subContent2 = new HorizontalLayout();
            subContent2.addComponents(subContent1,subContent);
            subWindow.setContent(subContent2);
            
            // Detail Class
            final TextField montlyPrice = makeTextField("Enter Monthly Price:","90%");
            // number of 's initial -> 0;
            final TextField profitId = makeTextField("Enter Profit ID:","90%");   
            // monthly profit initial -> 0;
            
            // Saloon
            final TextField saloonID = makeTextField("Enter Saloon ID:","90%");
            final TextField saloonName = makeTextField("Enter Saloon Name:","90%");
            final TextField contactNum = makeTextField("Enter Contact Number:","90%");
            final TextField addressID = makeTextField("Enter Address ID:","90%");
            
            // Address
            final TextField provience = makeTextField("Enter Provience:","90%");
            final TextField district = makeTextField("Enter District:","90%");
            final TextField detail = makeTextField("Enter Detail:","90%");
            
            Button button6 = new Button("ADD SALOON");
            subContent.addComponents(profitId,montlyPrice,provience,district,detail);
            subContent1.addComponents(saloonID,saloonName,contactNum,addressID,button6);
            // Center it in the browser window
            subWindow.center();
            subWindow.setWidth("30%");
            // Open it in the UI
            addWindow(subWindow);
            
            button6.addClickListener(h ->{
            	
            	try {
					Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
					
					String query1 = "insert into saloondetail values(?,?,?,?,?,?,?)";
					String query2 = "insert into address values(?,?,?,?)";
					String query3 = "insert into saloon values(?,?,?,?)";
					String query4 = "insert into profit values(?,?)";
					PreparedStatement statement1 = connection.prepareStatement(query1);
					PreparedStatement statement2 = connection.prepareStatement(query2);
					PreparedStatement statement3 = connection.prepareStatement(query3);
					PreparedStatement statement4 = connection.prepareStatement(query4);
					
					statement1.setString(1, saloonID.getValue());
					statement1.setString(2, "0");
					statement1.setString(3, "0");
					statement1.setString(4, "0");
					statement1.setString(5, "0");
					statement1.setString(6, montlyPrice.getValue());
					statement1.setString(7, profitId.getValue());
					
					statement2.setString(1, addressID.getValue());
					statement2.setString(2, provience.getValue());
					statement2.setString(3, district.getValue());
					statement2.setString(4, detail.getValue());
					
					statement3.setString(1, saloonID.getValue());
					statement3.setString(2, saloonName.getValue());
					statement3.setString(3, contactNum.getValue());
					statement3.setString(4, addressID.getValue());
					
					statement4.setString(1, profitId.getValue());
					statement4.setString(2, "0");
					
					statement1.execute();
					statement2.execute();
					statement3.execute();
					statement4.execute();
					
		    		Page.getCurrent().reload();
				} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
				
            });
    	});
    	
    	// CUSTOMER
    	Button button1 = new Button("Customer");
    	button1.addClickListener(e ->{
    		// Create a sub-window and set the content
            Window subWindow = new Window("Add Customer");
            VerticalLayout subContent = new VerticalLayout();
            VerticalLayout subContent1 = new VerticalLayout();
            VerticalLayout subContent3 = new VerticalLayout();
            HorizontalLayout subContent2 = new HorizontalLayout();
            subContent2.addComponents(subContent,subContent1,subContent3);
            subWindow.setContent(subContent2);
            // Person Class
            final TextField personID = makeTextField("Enter Person ID:","90%");
            final TextField name = makeTextField("Enter Name:","90%");
            final TextField surname = makeTextField("Enter Surame:","90%");
            final TextField identity = makeTextField("Enter Identity No:","90%");
            final TextField gender = makeTextField("Enter Gender:","90%");
            final TextField birthdate = makeTextField("Enter BirthDate:","90%");
            final TextField blood = makeTextField("Enter Blood:","90%");
            final TextField contactNum = makeTextField("Enter Contact Number:","90%");
            final TextField addressID = makeTextField("Enter Address ID:","90%");
            // Customer
            final TextField saloonID = makeTextField("Enter Saloon:","90%");
            final TextField membership = makeTextField("Enter Membership (1,3,6,12):","90%");
            final TextField weight = makeTextField("Enter Weight:","90%");
            final TextField height = makeTextField("Enter Height:","90%");
            // Address
            final TextField provience = makeTextField("Enter Provience:","90%");
            final TextField district = makeTextField("Enter District:","90%");
            final TextField detail = makeTextField("Enter Detail:","90%");
       
            Button button6 = new Button("ADD CUSTOMER");
            subContent.addComponents(name,surname,identity,gender,birthdate,blood,contactNum);
            subContent1.addComponents(personID,saloonID,membership,weight,height,button6);
            subContent3.addComponents(addressID,provience,district,detail);
            // Center it in the browser window
            subWindow.center();
            subWindow.setWidth("40%");
            // Open it in the UI
            addWindow(subWindow);
            
            button6.addClickListener(h ->{
            	
            	try {
					Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
					
					String query1 = "insert into person values(?,?,?,?,?,?,?,?,?,?)";
					String query2 = "insert into customer values(?,?,?,?,?)";
					String query3 = "insert into address values(?,?,?,?)";
					PreparedStatement statement1 = connection.prepareStatement(query1);
					PreparedStatement statement2 = connection.prepareStatement(query2);
					PreparedStatement statement3 = connection.prepareStatement(query3);
					
					statement1.setString(1, personID.getValue());
					statement1.setString(2, name.getValue());
					statement1.setString(3, surname.getValue());
					statement1.setString(4, identity.getValue());
					statement1.setString(5, gender.getValue());
					statement1.setString(6, birthdate.getValue());
					statement1.setString(7, blood.getValue());
					statement1.setString(8, contactNum.getValue());
					statement1.setString(9, addressID.getValue());
					statement1.setString(10, "customer");
					
					statement2.setString(1, personID.getValue());
					statement2.setString(2, saloonID.getValue());
					statement2.setString(3, membership.getValue());
					statement2.setString(4, weight.getValue());
					statement2.setString(5, height.getValue());
					
					statement3.setString(1, addressID.getValue());
					statement3.setString(2, provience.getValue());
					statement3.setString(3, district.getValue());
					statement3.setString(4, detail.getValue());
					
					statement1.execute();
					statement2.execute();
					statement3.execute();
					
					// Trigger 1
					String data = "select customernumber from saloondetail where saloonid = ?";
					PreparedStatement statement = connection.prepareStatement(data);
					statement.setString(1, saloonID.getValue());
		    		ResultSet set = statement.executeQuery();
		    		while(set.next()) {
		    			String customer = set.getString("customernumber");
		    			int newCustomer = Integer.parseInt(customer) + 1;
		    			String queryNew = "UPDATE saloondetail SET customernumber = ? WHERE saloonid = ?";
						PreparedStatement statementNew = connection.prepareStatement(queryNew);
						statementNew.setString(1, Integer.toString(newCustomer));
						statementNew.setString(2, saloonID.getValue());
						statementNew.execute();
		    		}
		    		set.close();
		    		
		    		// Trigger 5
					String dataP = "select * from saloondetail where saloonid = ?";
					PreparedStatement statementP = connection.prepareStatement(dataP);
					statementP.setString(1, saloonID.getValue());
		    		ResultSet setP = statementP.executeQuery();
		    		while(setP.next()) {
		    			String price = setP.getString("price");
		    			String proId = setP.getString("profitid");
		    			int monthlyPrice = Integer.parseInt(price);
		    			String dataPro = "select monthlyprofit from profit where profitid = ?";
		    			PreparedStatement sid = connection.prepareStatement(dataPro);
		    			sid.setString(1, proId);
		    			ResultSet setId = sid.executeQuery();
		    			while(setId.next()) {
		    				String oldPro = setId.getString("monthlyprofit");
		    				int old = Integer.parseInt(oldPro);
		    				String queryNew = "UPDATE profit SET monthlyprofit = ? WHERE profitid = ?";
							PreparedStatement statementNew = connection.prepareStatement(queryNew);
							statementNew.setString(1, Integer.toString(old+monthlyPrice));
							statementNew.setString(2, proId);
							statementNew.execute();
		    			}
		    			setId.close();
		    		}
		    		setP.close();
		    		
					Page.getCurrent().reload();
				} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
				
            });
    	});
    	
    	// STAFF
    	Button button2 = new Button("Staff");
    	button2.addClickListener(e ->{
    		// Create a sub-window and set the content
            Window subWindow = new Window("Add Staff");
            VerticalLayout subContent = new VerticalLayout();
            VerticalLayout subContent1 = new VerticalLayout();
            HorizontalLayout subContent2 = new HorizontalLayout();
            subContent2.addComponents(subContent1,subContent);
            subWindow.setContent(subContent2);
            // Person Class
            final TextField personID = makeTextField("Enter Person ID:","90%");
            final TextField name = makeTextField("Enter Name:","90%");
            final TextField surname = makeTextField("Enter Surame:","90%");
            final TextField identity = makeTextField("Enter Identity No:","90%");
            final TextField gender = makeTextField("Enter Gender:","90%");
            final TextField birthdate = makeTextField("Enter BirthDate:","90%");
            final TextField blood = makeTextField("Enter Blood:","90%");
            final TextField contactNum = makeTextField("Enter Contact Number:","90%");
            final TextField addressID = makeTextField("Enter Address ID:","90%");
            
            // Staff
            final TextField saloonID = makeTextField("Enter Saloon ID:","90%");
            final TextField price = makeTextField("Enter Price:","90%");
            
            // Address
            final TextField provience = makeTextField("Enter Provience:","90%");
            final TextField district = makeTextField("Enter District:","90%");
            final TextField detail = makeTextField("Enter Detail:","90%");
       
            Button button6 = new Button("ADD STAFF");
            subContent.addComponents(price,personID,name,surname,identity,provience,district,detail);
            subContent1.addComponents(saloonID,gender,birthdate,blood,contactNum,addressID,button6);
            // Center it in the browser window
            subWindow.center();
            subWindow.setWidth("30%");
            // Open it in the UI
            addWindow(subWindow);
            
            button6.addClickListener(h ->{
            	
            	try {
					Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
					
					String query1 = "insert into person values(?,?,?,?,?,?,?,?,?,?)";
					String query2 = "insert into staff values(?,?,?)";
					String query3 = "insert into address values(?,?,?,?)";
					PreparedStatement statement1 = connection.prepareStatement(query1);
					PreparedStatement statement2 = connection.prepareStatement(query2);
					PreparedStatement statement3 = connection.prepareStatement(query3);
					
					statement1.setString(1, personID.getValue());
					statement1.setString(2, name.getValue());
					statement1.setString(3, surname.getValue());
					statement1.setString(4, identity.getValue());
					statement1.setString(5, gender.getValue());
					statement1.setString(6, birthdate.getValue());
					statement1.setString(7, blood.getValue());
					statement1.setString(8, contactNum.getValue());
					statement1.setString(9, addressID.getValue());
					statement1.setString(10, "staff");
					
					statement2.setString(1, personID.getValue());
					statement2.setString(2, saloonID.getValue());
					statement2.setString(3, price.getValue());
					
					statement3.setString(1, addressID.getValue());
					statement3.setString(2, provience.getValue());
					statement3.setString(3, district.getValue());
					statement3.setString(4, detail.getValue());
					
					statement1.execute();
					statement2.execute();
					statement3.execute();
					
					// Trigger 2
					String data = "select staffnumber from saloondetail where saloonid = ?";
					PreparedStatement statement = connection.prepareStatement(data);
					statement.setString(1, saloonID.getValue());
		    		ResultSet set = statement.executeQuery();
		    		while(set.next()) {
		    			String customer = set.getString("staffnumber");
		    			int newCustomer = Integer.parseInt(customer) + 1;
		    			String queryNew = "UPDATE saloondetail SET staffnumber = ? WHERE saloonid = ?";
						PreparedStatement statementNew = connection.prepareStatement(queryNew);
						statementNew.setString(1, Integer.toString(newCustomer));
						statementNew.setString(2, saloonID.getValue());
						statementNew.execute();
		    		}
		    		set.close();
		    		
		    		// Trigger 6
					String dataP = "select profitid from saloondetail where saloonid = ?";
					PreparedStatement statementP = connection.prepareStatement(dataP);
					statementP.setString(1, saloonID.getValue());
					String priceS = price.getValue();
		    		ResultSet setP = statementP.executeQuery();
		    		while(setP.next()) {
		    			String proId = setP.getString("profitid");
		    			String dataPro = "select monthlyprofit from profit where profitid = ?";
		    			PreparedStatement sid = connection.prepareStatement(dataPro);
		    			sid.setString(1, proId);
		    			ResultSet setId = sid.executeQuery();
		    			while(setId.next()) {
		    				String oldPro = setId.getString("monthlyprofit");
		    				int old = Integer.parseInt(oldPro);
		    				String queryNew = "UPDATE profit SET monthlyprofit = ? WHERE profitid = ?";
							PreparedStatement statementNew = connection.prepareStatement(queryNew);
							statementNew.setString(1, Integer.toString(old-Integer.parseInt(priceS)));
							statementNew.setString(2, proId);
							statementNew.execute();
		    			}
		    			setId.close();
		    		}
		    		setP.close();
		    		
					Page.getCurrent().reload();
				} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
				
            });
    	});
    	
    	// COURCE
    	Button button3 = new Button("Cource");
    	button3.addClickListener(e ->{
    		// Create a sub-window and set the content
            Window subWindow = new Window("Add Cource");
            VerticalLayout subContent = new VerticalLayout();
            subWindow.setContent(subContent);
            // Put some components in it
            final TextField saloonID = makeTextField("Enter Saloon ID:","90%");
            final TextField courceName = makeTextField("Enter Cource Name:","90%");
            final TextField courceQuota = makeTextField("Enter Cource Quota:","90%");
            final TextField personID = makeTextField("Enter Person ID:","90%");
            Button button6 = new Button("ADD COURCE");
            subContent.addComponents(saloonID,courceName,courceQuota,personID,button6);
            // Center it in the browser window
            subWindow.center();
            subWindow.setWidth("20%");
            // Open it in the UI
            addWindow(subWindow);

            button6.addClickListener(h ->{
            	
            	try {
					Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
					
					String query3 = "insert into cource values(?,?,?,?)";
					PreparedStatement statement3 = connection.prepareStatement(query3);
					
					statement3.setString(1, personID.getValue());
					statement3.setString(2, courceName.getValue());
					statement3.setString(3, courceQuota.getValue());
					statement3.setString(4, saloonID.getValue());
					
					statement3.execute();
					
					// Trigger 3
					String data = "select courcenumber from saloondetail where saloonid = ?";
					PreparedStatement statement = connection.prepareStatement(data);
					statement.setString(1, saloonID.getValue());
		    		ResultSet set = statement.executeQuery();
		    		while(set.next()) {
		    			String customer = set.getString("courcenumber");
		    			int newCustomer = Integer.parseInt(customer) + 1;
		    			String queryNew = "UPDATE saloondetail SET courcenumber = ? WHERE saloonid = ?";
						PreparedStatement statementNew = connection.prepareStatement(queryNew);
						statementNew.setString(1, Integer.toString(newCustomer));
						statementNew.setString(2, saloonID.getValue());
						statementNew.execute();
		    		}
		    		set.close();
		    		
					Page.getCurrent().reload();
				} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
				
            });            
    	});
    	
    	// INVENTORY
    	Button button4 = new Button("Inventory");
    	button4.addClickListener(e ->{
    		// Create a sub-window and set the content
            Window subWindow = new Window("Add Inventory");
            VerticalLayout subContent = new VerticalLayout();
            subWindow.setContent(subContent);
            // Put some components in it
            final TextField saloonID = makeTextField("Enter Saloon ID:","90%");
            final TextField inventoryName = makeTextField("Enter Inventory Name:","90%");
            final TextField inventoryNumber = makeTextField("Enter Inventory Number:","90%");
            final TextField inventoryValue = makeTextField("Enter Inventory Value:","90%");
            Button button6 = new Button("ADD INVENTORY");
            subContent.addComponents(saloonID,inventoryName,inventoryNumber,inventoryValue,button6);
            // Center it in the browser window
            subWindow.center();
            subWindow.setWidth("20%");
            // Open it in the UI
            addWindow(subWindow);

            button6.addClickListener(h ->{
            	
            	try {
					Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
					
					String query3 = "insert into inventory values(?,?,?,?)";
					PreparedStatement statement3 = connection.prepareStatement(query3);
					
					statement3.setString(1, saloonID.getValue());
					statement3.setString(2, inventoryName.getValue());
					statement3.setString(3, inventoryNumber.getValue());
					statement3.setString(4, inventoryValue.getValue());
					
					statement3.execute();
					
					// Trigger 4
					String data = "select inventorynumber from saloondetail where saloonid = ?";
					PreparedStatement statement = connection.prepareStatement(data);
					statement.setString(1, saloonID.getValue());
		    		ResultSet set = statement.executeQuery();
		    		while(set.next()) {
		    			String customer = set.getString("inventorynumber");
		    			int newCustomer = Integer.parseInt(customer) + Integer.parseInt(inventoryNumber.getValue());
		    			String queryNew = "UPDATE saloondetail SET inventorynumber = ? WHERE saloonid = ?";
						PreparedStatement statementNew = connection.prepareStatement(queryNew);
						statementNew.setString(1, Integer.toString(newCustomer));
						statementNew.setString(2, saloonID.getValue());
						statementNew.execute();
		    		}
		    		set.close();
		    		
					Page.getCurrent().reload();
            	} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
				
            });
    	});
    	
    	// MANAGER
    	Button button5 = new Button("Manager");
    	button5.addClickListener(e ->{
    		// Create a sub-window and set the content
            Window subWindow = new Window("Add Manager");
            VerticalLayout subContent = new VerticalLayout();
            VerticalLayout subContent1 = new VerticalLayout();
            HorizontalLayout subContent2 = new HorizontalLayout();
            subContent2.addComponents(subContent1,subContent);
            subWindow.setContent(subContent2);
            // Person Class
            final TextField personID = makeTextField("Enter Person ID:","90%");
            final TextField name = makeTextField("Enter Name:","90%");
            final TextField surname = makeTextField("Enter Surame:","90%");
            final TextField identity = makeTextField("Enter Identity No:","90%");
            final TextField gender = makeTextField("Enter Gender:","90%");
            final TextField birthdate = makeTextField("Enter BirthDate:","90%");
            final TextField blood = makeTextField("Enter Blood:","90%");
            final TextField contactNum = makeTextField("Enter Contact Number:","90%");
            final TextField addressID = makeTextField("Enter Address ID:","90%");
            
            // Manager
            final TextField saloonID = makeTextField("Enter Saloon ID:","90%");
            final TextField price = makeTextField("Enter Price:","90%");
            
            // Address
            final TextField provience = makeTextField("Enter Provience:","90%");
            final TextField district = makeTextField("Enter District:","90%");
            final TextField detail = makeTextField("Enter Detail:","90%");
       
            Button button6 = new Button("ADD MANAGER");
            subContent.addComponents(price,personID,name,surname,identity,provience,district,detail);
            subContent1.addComponents(saloonID,gender,birthdate,blood,contactNum,addressID,button6);
            // Center it in the browser window
            subWindow.center();
            subWindow.setWidth("30%");
            // Open it in the UI
            addWindow(subWindow);
            
            button6.addClickListener(h ->{
            	
            	try {
					Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
					
					String query1 = "insert into person values(?,?,?,?,?,?,?,?,?,?)";
					String query2 = "insert into manager values(?,?,?)";
					String query3 = "insert into address values(?,?,?,?)";
					PreparedStatement statement1 = connection.prepareStatement(query1);
					PreparedStatement statement2 = connection.prepareStatement(query2);
					PreparedStatement statement3 = connection.prepareStatement(query3);
					
					statement1.setString(1, personID.getValue());
					statement1.setString(2, name.getValue());
					statement1.setString(3, surname.getValue());
					statement1.setString(4, identity.getValue());
					statement1.setString(5, gender.getValue());
					statement1.setString(6, birthdate.getValue());
					statement1.setString(7, blood.getValue());
					statement1.setString(8, contactNum.getValue());
					statement1.setString(9, addressID.getValue());
					statement1.setString(10, "manager");
					
					statement2.setString(1, personID.getValue());
					statement2.setString(2, saloonID.getValue());
					statement2.setString(3, price.getValue());
					
					statement3.setString(1, addressID.getValue());
					statement3.setString(2, provience.getValue());
					statement3.setString(3, district.getValue());
					statement3.setString(4, detail.getValue());
					
					statement1.execute();
					statement2.execute();
					statement3.execute();
					
					// Trigger 7
					String dataP = "select profitid from saloondetail where saloonid = ?";
					PreparedStatement statementP = connection.prepareStatement(dataP);
					statementP.setString(1, saloonID.getValue());
					String priceS = price.getValue();
		    		ResultSet setP = statementP.executeQuery();
		    		while(setP.next()) {
		    			String proId = setP.getString("profitid");
		    			String dataPro = "select monthlyprofit from profit where profitid = ?";
		    			PreparedStatement sid = connection.prepareStatement(dataPro);
		    			sid.setString(1, proId);
		    			ResultSet setId = sid.executeQuery();
		    			while(setId.next()) {
		    				String oldPro = setId.getString("monthlyprofit");
		    				int old = Integer.parseInt(oldPro);
		    				String queryNew = "UPDATE profit SET monthlyprofit = ? WHERE profitid = ?";
							PreparedStatement statementNew = connection.prepareStatement(queryNew);
							statementNew.setString(1, Integer.toString(old-Integer.parseInt(priceS)));
							statementNew.setString(2, proId);
							statementNew.execute();
		    			}
		    			setId.close();
		    		}
		    		setP.close();
		    		
					Page.getCurrent().reload();
				} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
				
            });
    	});
    	
	// DELETE --------------------------------------------------------------------
    	
    	Button buttonDel = new Button("Sil");
    	
		saloonGrid.addSelectionListener(e->{
    		Optional<Saloon> saloonSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			// delete a saloon and all other related
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			
					String pid = "-";
					// delete profit
					String queryGet = "select profitid from saloondetail where saloonid = "+saloonSel.get().getSaloonID();
	    			PreparedStatement s = connection.prepareStatement(queryGet);
	    			ResultSet setP = s.executeQuery();
	    			while(setP.next()) {
	    				pid = setP.getString("profitid");
	    			}
	    			setP.close();
	    			// delete manager person
    				queryGet = "select * from manager where saloonid = "+saloonSel.get().getSaloonID();
	    			s = connection.prepareStatement(queryGet);
	    			setP = s.executeQuery();
	    			while(setP.next()) {
	    				pid = setP.getString("personid");
	    				String q = "select * from person where personid = "+ pid;
	    				PreparedStatement qs = connection.prepareStatement(q);
	    				ResultSet qrs = qs.executeQuery();
	    				while(qrs.next()) {
	    					String addr = qrs.getString("addressid");
	    					String nq = "delete from address where addressid = "+addr;
	    					PreparedStatement state = connection.prepareStatement(nq);
							state.execute();
	    				}
	    				qrs.close();
	    				String newQuery = "delete from person where personid = "+pid;
	    				PreparedStatement statementNew = connection.prepareStatement(newQuery);
						statementNew.execute();
	    			}
	    			setP.close();
	    			
	    			// delete staff person
	    			queryGet = "select * from staff where saloonid = "+saloonSel.get().getSaloonID();
	    			s = connection.prepareStatement(queryGet);
	    			setP = s.executeQuery();
	    			while(setP.next()) {
	    				pid = setP.getString("personid");
	    				String q = "select * from person where personid = "+ pid;
	    				PreparedStatement qs = connection.prepareStatement(q);
	    				ResultSet qrs = qs.executeQuery();
	    				while(qrs.next()) {
	    					String addr = qrs.getString("addressid");
	    					String nq = "delete from address where addressid = "+addr;
	    					PreparedStatement state = connection.prepareStatement(nq);
							state.execute();
	    				}
	    				qrs.close();
	    				String newQuery = "delete from person where personid = "+pid;
	    				PreparedStatement statementNew = connection.prepareStatement(newQuery);
						statementNew.execute();
	    			}
	    			setP.close();
	    			
	    			// delete customer person
	    			queryGet = "select * from customer where saloonid = "+saloonSel.get().getSaloonID();
	    			s = connection.prepareStatement(queryGet);
	    			setP = s.executeQuery();
	    			while(setP.next()) {
	    				pid = setP.getString("personid");
	    				String q = "select * from person where personid = "+ pid;
	    				PreparedStatement qs = connection.prepareStatement(q);
	    				ResultSet qrs = qs.executeQuery();
	    				while(qrs.next()) {
	    					String addr = qrs.getString("addressid");
	    					String nq = "delete from address where addressid = "+addr;
	    					PreparedStatement state = connection.prepareStatement(nq);
							state.execute();
	    				}
	    				qrs.close();
	    				String newQuery = "delete from person where personid = "+pid;
	    				PreparedStatement statementNew = connection.prepareStatement(newQuery);
						statementNew.execute();
	    			}
	    			setP.close();
	    			
	    			// delete others
	    			String query1 = "delete from saloon where saloonid = "+saloonSel.get().getSaloonID();
	    			String query2 = "delete from address where addressid = "+saloonSel.get().getAddressID();
	    			String query3 = "delete from saloondetail where saloonid = "+saloonSel.get().getSaloonID();
	    			String query4 = "delete from profit where profitid = "+pid;
	    			String query5 = "delete from customer where saloonid = "+saloonSel.get().getSaloonID();
	    			String query6 = "delete from staff where saloonid = "+saloonSel.get().getSaloonID();
	    			String query7 = "delete from manager where saloonid = "+saloonSel.get().getSaloonID();
	    			String query8 = "delete from inventory where saloonid = "+saloonSel.get().getSaloonID();
	    			String query9 = "delete from cource where saloonid = "+saloonSel.get().getSaloonID();
	    			
	    			PreparedStatement s1 = connection.prepareStatement(query1);
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			PreparedStatement s3 = connection.prepareStatement(query3);
	    			PreparedStatement s4 = connection.prepareStatement(query4);
	    			PreparedStatement s5 = connection.prepareStatement(query5);
	    			PreparedStatement s6 = connection.prepareStatement(query6);
	    			PreparedStatement s7 = connection.prepareStatement(query7);
	    			PreparedStatement s8 = connection.prepareStatement(query8);
	    			PreparedStatement s9 = connection.prepareStatement(query9);
	    			s1.execute();
	    			s2.execute();
	    			s3.execute();
	    			s4.execute();
	    			s5.execute();
	    			s6.execute();
	    			s7.execute();
	    			s8.execute();
	    			s9.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}	
    		});
		});
    	
    	addressGrid.addSelectionListener(e->{
    		Optional<Address> addressSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from address where addressid = "+addressSel.get().getAddressID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	saloonDetailGrid.addSelectionListener(e->{
    		Optional<SaloonDetails> saloonDetailSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from saloondetail where saloonid = "+saloonDetailSel.get().getSaloonID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	profitGrid.addSelectionListener(e->{
    		Optional<Profit> profitSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from profit where profitid = "+profitSel.get().getProfitID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	personGrid.addSelectionListener(e->{
    		Optional<Person> personSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from person where personid = "+personSel.get().getPersonID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	customerGrid.addSelectionListener(e->{
    		Optional<Customer> customerSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from customer where personid = "+customerSel.get().getPersonID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	staffGrid.addSelectionListener(e->{
    		Optional<Staff> staffSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from staff where personid = "+staffSel.get().getPersonID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	courceGrid.addSelectionListener(e->{
    		Optional<Cources> courceSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from cource where saloonid= "+courceSel.get().getSaloonID()
	    							+" AND personid = "+courceSel.get().getPersonID()
	    							+" AND courcename = '"+courceSel.get().getCourceName()+"'";
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	managerGrid.addSelectionListener(e->{
    		Optional<Manager> managerSel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from manager where personid = "+managerSel.get().getPersonID();
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    	inventoryGrid.addSelectionListener(e->{
    		Optional<Inventory> inventorySel = e.getFirstSelectedItem();
    		buttonDel.addClickListener(l->{
    			try {
	    			Class.forName("org.h2.Driver");
					Connection connection = DriverManager.getConnection("jdbc:h2:~/test","sa","");
	    			String query2 = "delete from inventory where saloonid= "+inventorySel.get().getSaloonID()
	    							+" AND inventorynumber = "+inventorySel.get().getInventoryNumber()
	    							+" AND inventoryname = '"+inventorySel.get().getInventoryName()+"'";
	    			PreparedStatement s2 = connection.prepareStatement(query2);
	    			s2.execute();
	    			
	    			Page.getCurrent().reload();
    			} catch (ClassNotFoundException e1) {
					e1.printStackTrace();
				} catch (SQLException e1) {
					e1.printStackTrace();
				}
    		});
    	});
    	
    // MAIN ------------------------------------------------------------------------
    	HorizontalLayout hl = new HorizontalLayout();
    	HorizontalLayout h2 = new HorizontalLayout();
    	HorizontalLayout h3 = new HorizontalLayout();
    	HorizontalLayout h4 = new HorizontalLayout();
    	hl.addComponents(saloonGrid, addressGrid, profitGrid);
    	h2.addComponents(staffGrid, managerGrid);
    	h3.addComponents(inventoryGrid,courceGrid);
    	h4.addComponents(customerGrid,saloonDetailGrid);
    	hl.setSizeFull();
    	h2.setSizeFull();
    	h3.setSizeFull();
    	h4.setSizeFull();
    	hlayout1.addComponents(button,button1,button2,button3,button4,button5,buttonDel);
        vlayout.addComponents(hlayout1,hl,h4,personGrid,h2,h3);
        setContent(vlayout);
    }
    
    
    private TextField makeTextField(String textCaption, String width) {
    	TextField ret = new TextField();
    	ret.setCaption(textCaption);
    	ret.setWidth(width);
    	return ret;
    }

    @WebServlet(urlPatterns = "/*", name = "MyUIServlet", asyncSupported = true)
    @VaadinServletConfiguration(ui = MyUI.class, productionMode = false)
    public static class MyUIServlet extends VaadinServlet {
    }
}
