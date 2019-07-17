#include <bits/stdc++.h> 
using namespace std; 

class customerHistory {
public:
	string source, destination;
	int cabId, fare;
	customerHistory(string source, string destination, int cabId, int fare) {
		this->source = source;
		this->destination = destination;
		this->cabId = cabId;
		this->fare = fare;
	}
};

class cabHistory {
public:
	string source, destination;
	int customerId, fare, zulaCommission;
	cabHistory(string source, string destination, int customerId, int fare) {
		this->source = source;
		this->destination = destination;
		this->customerId = customerId;
		this->fare = fare;
		this->zulaCommission = (fare / 10) * 3;
	}
};

class Cab {
public:
	int id, age, curLocId, noOfRides, earnings;
	string name, password, curLocName;
	char gender;
	bool rest;
	vector<cabHistory> history;
	Cab(int id, string name, string password, int age, char gender, int curLocId, string curLocName) {
		this->id = id;
		this->age = age;
		this->name = name;
		this->password = password;
		this->gender = gender;
		this->curLocId = curLocId;
		this->curLocName = curLocName;
		this->rest = false;
		this->noOfRides = 0;
		this->earnings = 0;
	}
};

class Customer {
public:
	int id, age, noOfRides, totalFare;
	string name, password;
	char gender;
	vector<customerHistory> history;
	Customer(int id, string name, string password, int age, char gender) {
		this->id = id;
		this->age = age;
		this->name = name;
		this->password = password;
		this->gender = gender;
		this->noOfRides = 0;
		this->totalFare = 0;
	}
};

class Connection {
public:
	string name;
	int distance;
	Connection(string name, int distance) {
		this->name = name;
		this->distance = distance;
	}
};

class Location {
public:
	int id;
	string name;
	vector<Connection> connections;
	Location(int id, string name, vector<Connection> connections) {
		this->id = id;
		this->name = name;
		this->connections = connections;
	}
};

vector<Cab> cabs;
vector<Customer> customers;
vector<Location> locations;
vector<vector<int>> shortestPath;

int isPathAvailable(int srcId, string destName) {
	for (int i = 0; i < locations[srcId].connections.size(); i++)
		if (locations[srcId].connections[i].name == destName)
			return locations[srcId].connections[i].distance;
	return -1;
}

void allSourceShortestPath() {
	shortestPath.resize(locations.size(), vector<int>(locations.size(), INT_MAX));
	for (int k = 0; k < locations.size(); k++) {
		for (int i = 0; i < locations.size(); i++) {
			for (int j = 0; j < locations.size(); j++) {
				int x = isPathAvailable(locations[i].id, locations[k].name);
				int y = isPathAvailable(locations[k].id, locations[j].name);
				if (x != -1 && y != -1 && shortestPath[i][j] > x + y)
					shortestPath[i][j] = x + y;
			}
		}
	}
}

void init() {
	cabs.push_back(Cab(1, "aaa", "111", 43, 'M', 4, "D"));
	cabs.push_back(Cab(2, "bbb", "222", 31, 'M', 7, "G"));
	cabs.push_back(Cab(3, "ccc", "333", 38, 'F', 8, "H"));
	cabs.push_back(Cab(4, "ddd", "444", 28, 'F', 1, "A"));


	customers.push_back(Customer(1, "zz", "99", 25, 'F'));
	customers.push_back(Customer(2, "yy", "88", 61, 'M'));
	customers.push_back(Customer(3, "xx", "77", 22, 'M'));
	customers.push_back(Customer(4, "ww", "66", 36, 'F'));


	vector<Connection> c;
	c.push_back(Connection("C", 4));
	locations.push_back(Location(1, "A", c));
	c.clear();

	c.push_back(Connection("A", 4));
	c.push_back(Connection("D", 3));
	locations.push_back(Location(2, "C", c));
	c.clear();

	c.push_back(Connection("C", 3));
	c.push_back(Connection("F", 2));
	locations.push_back(Location(3, "D", c));
	c.clear();

	c.push_back(Connection("D", 2));
	c.push_back(Connection("B", 6));
	locations.push_back(Location(4, "F", c));
	c.clear();

	c.push_back(Connection("F", 6));
	c.push_back(Connection("G", 3));
	locations.push_back(Location(5, "B", c));
	c.clear();

	c.push_back(Connection("B", 3));
	c.push_back(Connection("H", 2));
	locations.push_back(Location(6, "G", c));
	c.clear();

	c.push_back(Connection("G", 2));
	c.push_back(Connection("E", 3));
	locations.push_back(Location(7, "H", c));
	c.clear();

	c.push_back(Connection("H", 3));
	locations.push_back(Location(8, "E", c));
	c.clear();
}

void driverLogin() {
	cout << "DRIVER LOGIN" << endl;
	cout << "Enter the driver name: ";
	string name, password;
	int pos = -1;
	bool flag = false;
	while (!flag) {
		getline(cin, name);
		for (int i = 0; i < cabs.size(); i++) {
			if (cabs[i].name == name) {
				flag = true;
				pos = i;
				break;
			}
		}
		if (!flag)
			cout << "Enter a valid driver name: ";
	}
	cout << "Enter the password: ";
	getline(cin, password);
	if (cabs[pos].password == password) {
		cout << "Welcome " << cabs[pos].name << endl;
	} else {
		cout << "Invalid password" << endl;
	}
}

void driverSignUp() {
	cout << "DRIVER SIGN-UP" << endl;
	int id = cabs.size() + 1, age, curLocId;
	string name, password, tempPassword, curLocName;
	char gender;
	cout << "Enter name: ";
	getline(cin, name);
	cout << "Enter age: ";
	cin >> age;
	cout << "Enter gender: ";
	cin >> gender;
	cout << "Enter password: ";
	getline(cin, password);
	cout << "Re-enter your password: ";
	getline(cin, tempPassword);
	if (password != tempPassword) {
		cout << "Password doesn't match" << endl;
		return;
	}
	cout << "Enter your current location name: ";
	bool flag = false;
	while (!flag) {
		getline(cin, curLocName);
		for (int i = 0; i < locations.size(); i++) {
			if (locations[i].name == curLocName) {
				flag = true;
				curLocId = locations[i].id;
				break;
			}
		}
		if (!flag)
			cout << "Enter your valid current location name: ";
	}
	cabs.push_back(Cab(id, name, password, age, gender, curLocId, curLocName));
	int pos = cabs.size() - 1;
	cout << "Welcome " << cabs[pos].name << endl;
	cout << "Successfully signed up" << endl;
}

void customersLogin() {
	cout << "CUSTOMER LOGIN" << endl;
	cout << "Enter the customer name: ";
	string name, password;
	int pos = -1;
	bool flag = false;
	while (!flag) {
		getline(cin, name);
		for (int i = 0; i < customers.size(); i++) {
			if (customers[i].name == name) {
				flag = true;
				pos = i;
				break;
			}
		}
		if (!flag)
			cout << "Enter a valid customer name: ";
	}
	cout << "Enter the password: ";
	getline(cin, password);
	if (customers[pos].password == password) {
		cout << "Welcome " << customers[pos].name << endl;
	} else {
		cout << "Invalid Password" << endl;
	}
}

void customerSignUp() {
	cout << "CUSTOMER SIGN-UP" << endl;
	int id = customers.size() + 1, age;
	string name, password, tempPassword;
	char gender;
	cout << "Enter name: ";
	getline(cin, name);
	cout << "Enter age: ";
	cin >> age;
	cout << "Enter gender: ";
	cin >> gender;
	cout << "Enter password: ";
	cin >> password;
	cout << "Re-enter your password: ";
	getline(cin, tempPassword);
	if (password != tempPassword) {
		cout << "Password doesn't match" << endl;
		return;
	}
	customers.push_back(Customer(id, name, password, age, gender));
	int pos = customers.size() - 1;
	cout << "Welcome " << customers[pos].name << endl;
	cout << "Successfully signed up" << endl;
}

bool isCabAvailable() {
	for (int i = 0; i < cabs.size(); i++)
		if (!cabs[i].rest)
			return true;
	return false;
}

void printAvailableCabs() {
	cout << left << setw(10) << "Id" << setw(10) << "Location" << endl;
	for (int i = 0; i < cabs.size(); i++) {
		if (!cabs[i].rest) {
			cout << left << setw(10) << cabs[i].id << setw(10) << cabs[i].curLocName << endl;
		}
	}
}

void changeRestValue(int id) {
	for (int i = 0; i < cabs.size(); i++)
		if (cabs[i].id != id+1 && cabs[i].rest)
			cabs[i].rest = false;
}

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
	if (a.second == b.second) {
		return a.first.second < b.first.second;
	}
	return a.second < b.second;
}

void hailCab() {
	int customerId;
	cout << "Enter your customerId: ";
	cin >> customerId;
	if (customerId < 1 || customerId > customers.size()) {
		cout << "Enter a valid customerId" << endl;
		return;
	}
	string source, destination;
	int srcId = -1, destId = -1;
	cout << "Enter a pickup location: ";
	cin.ignore();
	getline(cin, source);
	cout << "Enter a drop location: ";
	getline(cin, destination);
	if (source == destination) {
		cout << "Please try to choose the valid locations" << endl;
		return;
	}
	for (int i = 0; i < locations.size(); i++) {
		if (locations[i].name == source)
			srcId = i;
		if (locations[i].name == destination)
			destId = i;
		if (srcId != -1 && destId != -1)
			break;
	}
	if (srcId == -1 || destId == -1) {
		cout << "Please try to choose the valid locations" << endl;
		return;
	}
	if (isCabAvailable()) {
		printAvailableCabs();
		vector<pair<pair<int, int>, int>> availableCabs; // {{id, noOfRides}, dist}
		for (int i = 0; i < cabs.size(); i++) {
			if (!cabs[i].rest) {
				availableCabs.push_back({{cabs[i].id, cabs[i].noOfRides}, shortestPath[destId][cabs[i].curLocId-1]});
			}
		}
		sort(availableCabs.begin(), availableCabs.end(), comp);
		int cabId = availableCabs[0].first.first - 1;
		cabs[cabId].curLocId = destId;
		cabs[cabId].curLocName = destination;
		cabs[cabId].noOfRides++;
		cabs[cabId].earnings += 10 * availableCabs[0].second;
		cabs[cabId].rest = true;
		customers[customerId].noOfRides++;
		customers[customerId].totalFare += 10 * availableCabs[0].second;
		cabs[cabId].history.push_back(cabHistory(source, destination, customerId, availableCabs[0].second * 10));
		customers[customerId-1].history.push_back(customerHistory(source, destination, cabId + 1, availableCabs[0].second * 10));
		changeRestValue(cabId);
		cout << "Journey Initalized.\nEnjoy your Journey." << endl;
	} else {
		cout << "Sorry right now there is no available cabs right now" << endl;
	}
}

void customerRideSummary() {
	int id;
	cout << "Enter the customer id: ";
	cin >> id;
	if (id < 1 || id > customers.size()) {
		cout << "Enter a valid customer id" << endl;
		return;
	}
	id -= 1;
	cout << "CUSTOMER SUMMARY" << endl;
	cout << "Customer Id: " << customers[id].id << endl;
	cout << "Customer Name: " << customers[id].name << endl;
	cout << "Trip Details" << endl;
	cout << left << setw(10) << "Source" << setw(10) << "Destination" << setw(10) << "Cab Detail" << setw(10) << "Fare" << endl;
	for (int j = 0; j < customers[id].history.size(); j++)
		cout << left << setw(10) << customers[id].history[j].source << setw(10) << customers[id].history[j].destination << setw(10) << customers[id].history[j].cabId << setw(10) << customers[id].history[j].fare << endl;
}

void cabRideSummary() {
	int id;
	cout << "Enter the cab id: ";
	cin >> id;
	if (id < 1 || id > cabs.size()) {
		cout << "Enter a valid cab id" << endl;
		return;
	}
	id -= 1;
	cout << "CAB SUMMARY" << endl;
	cout << "Cab id: " << cabs[id].id << endl;
	cout << "Cab Driver Name: " << cabs[id].name << endl;
	cout << "Trip Details" << endl;
	cout << left << setw(10) << "Source" << setw(10) << "Destination" << setw(10) << "Cab Detail" << setw(10) << "Fare" << setw(20) << "ZULA Commission" << endl;
	for (int i = 0; i < cabs[id].history.size(); i++)
		cout << left << setw(10) << cabs[id].history[i].source << setw(10) << cabs[id].history[i].destination << setw(10) << cabs[id].history[i].customerId << setw(10) << cabs[id].history[i].fare << setw(20) << cabs[id].history[i].zulaCommission << endl;
}

void adminCabSummary() {
	cout << "ADMIN CAB SUMMARY" << endl;
	for (int i = 0; i < cabs.size(); i++) {
		cout << "Cab id: " << cabs[i].id << endl;
		cout << "Cab Driver Name: " << cabs[i].name << endl;
		cout << "Total Number of Trips: " << cabs[i].noOfRides << endl;
		cout << "Total Fare Collected: " << cabs[i].earnings << endl;
		cout << "Total ZULA Commission: " << (cabs[i].earnings / 10) * 3 << endl;
		cout << "Trip Details" << endl;
		cout << left << setw(10) << "Source" << setw(10) << "Destination" << setw(10) << "Cab Detail" << setw(10) << "Fare" << setw(20) << "ZULA Commission" << endl;
		for (int j = 0; j < cabs[i].history.size(); j++)
			cout << left << setw(10) << cabs[i].history[j].source << setw(10) << cabs[i].history[j].destination << setw(10) << cabs[i].history[j].customerId << setw(10) << cabs[i].history[j].fare << setw(20) << cabs[i].history[j].zulaCommission << endl;
	}
}

void adminCustomerSummary() {
	cout << "ADMIN CUSTOMER SUMMARY" << endl;
	for (int i = 0; i < customers.size(); i++) {
		cout << "Customer Id: " << customers[i].id << endl;
		cout << "Customer Name: " << customers[i].name << endl;
		cout << "Total Number of Trips: " << customers[i].noOfRides << endl;
		cout << "Total Fare Given: " << customers[i].totalFare << endl;
		cout << "Trip Details" << endl;
		cout << left << setw(10) << "Source" << setw(10) << "Destination" << setw(10) << "Cab Detail" << setw(10) << "Fare" << endl;
		for (int j = 0; j < customers[i].history.size(); j++)
			cout << left << setw(10) << customers[i].history[j].source << setw(10) << customers[i].history[j].destination << setw(10) << customers[i].history[j].cabId << setw(10) << customers[i].history[j].fare << endl;
	}
}

int main(void) { 
	init();
	allSourceShortestPath();
	while (true) {
		cout << "**** MENU ****" << endl;
		cout << "1. Hail A Cab" << endl;
		cout << "2. Customer Rides Summary" << endl;
		cout << "3. Cab Rides Summary" << endl;
		cout << "4. Admin Customers Ride Summary" << endl;
		cout << "5. Admin Cabs Ride Summary" << endl;
		int choice;
		cout << "Enter your choice: ";
		cin >> choice;
		switch(choice) {
			case 1:
				hailCab();
				break;
			case 2:
				customerRideSummary();
				break;
			case 3:
				cabRideSummary();
				break;
			case 4:
				adminCustomerSummary();
				break;
			case 5:
				adminCabSummary();
				break;
			default:
				cout << "Enter a valid choice" << endl;
				break;
		}
	}
} 
