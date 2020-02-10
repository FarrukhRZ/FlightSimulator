// FlightSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"FlightGraph.h"

using namespace std;

int main() {
	FlightGraph* f1=new FlightGraph("C:\\Users\\Hp Pc\\Downloads\\Flights.txt");
	//f1->Display();
	string c1 = "Islamabad", c2 = "Newyork", c3 = "Sydney", c4 = "Berlin", c5 = "Paris", c6 = "Singapore", c7 = "Amsterdam", c8 = "Seoul", c9 = "Tokyo", c10 = "Hongkong",c11="London";
	
	cout << "Welcome to H&F Travels\n";
	cout <<c1<<"\n"<<c2<< "\n"<<c3<< "\n"<<c4<< "\n"<<c5<< "\n"<<c6<< "\n"<<c7<< "\n"<<c8<< "\n"<<c9<< "\n"<<c10<< "\n"<<c11<<endl;
	string depcity, arrcity;
	cout<< "Choose your city of departure\n";
	cin >> depcity;
	cout << "Select you city of arrival\n";
	cin >> arrcity;
	cout << "Do you want your flight at a specific date of December 2019?\n1: Yes\n2:No\n";
	int date;
	cin >> date;
	if (date == 1) {
		date =35;
		while (date < 0 || date >= 31) {
			cout << "Enter correct day of travel\n";
			cin >> date;
		}
	}
	else {
		date = 0;
	}
	cout << "Select your flight type\n1: Direct\n2: Transit\n3:Any\n";
	int ftype;
	cin >> ftype;
	string transit = depcity;
	if (ftype == 2) {
		while (transit == depcity || transit == arrcity) {
			cout << "Select your transit city\n";
			cin >> transit;
		}
	}
	string atype="";
	cout << "Choose your preffered airline\n1: Qatar\n2: Emirates\n3: ANA\n 4: Any\n";
	cin >> atype;
	cout << "Finally choose the sorting order\n1:Economical\n2:Quickest\n";
	int order;
	cin >> order;
	f1->adjusttimeandhotel("C:\\Users\\Hp Pc\\Downloads\\timezone.txt");
	f1->DisplayFlights(depcity,arrcity,order);
	f1->costdisplay(ftype,atype,transit,date);
	//cout << filereading("C:\\Users\\Hp Pc\\Downloads\\highscore.txt")<<endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
