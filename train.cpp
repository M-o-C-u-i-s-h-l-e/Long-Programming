// Application For Reservation and Cancellation of Train Tickets

#include <bits/stdc++.h>
using namespace std;

class passenger {
public:
	string name;
	map<int, int> bookings;	// {trainId, noOfTickets}
	passenger(string name, int trainId, int noOfTickets) {
		this->name = name;
		this->bookings[trainId] = noOfTickets;
	}
};

map<pair<string, string>, int> trains;	// {{source, destination}, id}
map<int, pair<string, string>> trainIds;	// {id, {source, destination}}
map<string, passenger> passengers;

void init() {
	trains[{"A", "B"}] = 1;
	trains[{"B", "C"}] = 2;
	trains[{"C", "D"}] = 3;
	trains[{"D", "E"}] = 4;
	trains[{"A", "C"}] = 5;
	trains[{"A", "D"}] = 6;
	trains[{"A", "E"}] = 7;
	trains[{"B", "D"}] = 8;
	trains[{"B", "E"}] = 9;
	trains[{"C", "E"}] = 10;

	trainIds[1] = {"A", "B"};
	trainIds[2] = {"B", "C"};
	trainIds[3] = {"C", "D"};
	trainIds[4] = {"D", "E"};
	trainIds[5] = {"A", "C"};
	trainIds[6] = {"A", "D"};
	trainIds[7] = {"A", "E"};
	trainIds[8] = {"B", "D"};
	trainIds[9] = {"B", "E"};
	trainIds[10] = {"C", "E"};
}

void reservation() {
	string name, phoneNo, source, destination;
	int tickets;
	cout << "Enter Your Name: ";
	cin >> name;
	cout << "Enter Your Phone Number: ";
	cin >> phoneNo;
	auto passengerDB = passengers.find(phoneNo);
	if (passengerDB != passengers.end() && passengerDB->second.name != name) {
		cout << "Enter The Valid Name.\n";
		return;
	}
	cout << "Enter The Source: ";
	cin >> source;
	cout << "Enter The Destination: ";
	cin >> destination;
	if (trains.find({source, destination}) == trains.end()) {
		cout << "Enter The Valid Source And Destination.\n";
		return;
	}
	cout << "Enter The Number of Tickets: ";
	cin >> tickets;
	if (passengerDB == passengers.end()) {
		passenger *p = new passenger(name, trains[{source, destination}], tickets);
		passengers.insert({phoneNo, *p});
	} else {
		passengerDB->second.bookings[trains[{source, destination}]] += tickets;
	}
}

void cancellation() {
	string phoneNo, source, destination;
	int noOfTickets;
	cout << "Enter Your Phone Number: ";
	cin >> phoneNo;
	auto passengerDB = passengers.find(phoneNo);
	if (passengerDB == passengers.end()) {
		cout << "Enter The Valid Phone Number.\n";
		return;
	}
	cout << "Enter Source: ";
	cin >> source;
	cout << "Enter Destination: ";
	cin >> destination;
	if (trains.find({source, destination}) == trains.end() || passengerDB->second.bookings.find(trains[{source, destination}]) == passengerDB->second.bookings.end()) {
		cout << "Enter The Valid Source And Destination.\n";
		return;
	}
	cout << "Enter Number of Tickets to Cancel: ";
	cin >> noOfTickets;
	if (passengerDB->second.bookings[trains[{source, destination}]] < noOfTickets) {
		cout << "Enter Valid Number of Tickets to Cancel.\n";
		return;
	}
	passengerDB->second.bookings[trains[{source, destination}]] -= noOfTickets;
	if (passengerDB->second.bookings[trains[{source, destination}]] == 0)
		passengerDB->second.bookings.erase(trains[{source, destination}]);
	if (passengerDB->second.bookings.size() == 0)
		passengers.erase(phoneNo);
}

void print() {
	cout << "**** DATABASE ****\n";
	cout << left << setw(12) << "Name" << setw(12) << "Phone No" << setw(12) << "Source" << setw(12) << "Destination" << setw(12) << "No Of Tickets" << endl << endl;
	for (auto itr = passengers.begin(); itr != passengers.end(); itr++) {
		int i = 0;
		for (auto it = itr->second.bookings.begin(); it != itr->second.bookings.end(); it++, i++) {
			if (i == 0)
				cout << left << setw(12) << itr->second.name << setw(12) << itr->first;
			else
				cout << setw(12) << " " << setw(12) << " ";
			cout << left << setw(12) << trainIds[it->first].first << setw(12) << trainIds[it->first].second << setw(12) << it->second << endl;
		}
		cout << endl;
	}
}

int main(void) {
	init();
	while (true) {
		cout << "**** MENU ****\n";
		cout << "1. Resevation.\n2. Cancellation.\n";
		int choice;
		cin >> choice;
		switch(choice) {
			case 1:
				reservation();
				break;
			case 2:
				cancellation();
				break;
			case 3:
				exit(0);
			default:
				cout << "Enter A Valid Choice.\n";
				break;
		}
		cout << endl;
		if (choice == 1 || choice == 2)
			print();
	}
}
