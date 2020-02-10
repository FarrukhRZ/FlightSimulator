#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
struct Date {
	int day, month, year;
	Date(int d = 0, int m = 0, int y = 0) {
		day = d;
		month = m;
		year = y;
	}
	void setdate(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}
	bool operator==(const Date& d1) {
		if (day == d1.day && month == d1.month && year == d1.year) {
			return true;
		}
		return false;
	}
	bool operator<(const Date& d1) {
		if (day < d1.day) {
			return true;
		}
		else if (month < d1.month) {
			return true;
		}
		return false;
	}
	void Display() {
		cout << day << "/" << month << "/" << year;
	}
};
struct Time {
	int hr, min;
	Time(int h = 0, int m = 0) {
		hr = h;
		min = m;
	}
	void SetTime(int h, int m) {
		hr = h;
		min = m;
	}
	bool operator==(const Time& t1) {
		if (hr == t1.hr && min == t1.min) {
			return true;
		}
		return false;
	}
	void Display() {
		cout << hr << ":" << min << ":" << "00";
	}
	bool operator<(const Time& t1) {
		if (hr < t1.hr) {
			return true;
		}
		else if (hr == t1.hr && min < t1.min) {
			return true;
		}
		else {
			return false;
		}
	}
};
class Flight {
public:
	string cityname;
	string airline;
	int fare;
	Date date;
	Time deptime;
	Time arrtime;
	Flight* next;
	Flight(string city = "", int day = 0, int month = 0, int year = 0, int dHour = 0, int dMin = 0, int aHour = 0, int aMin = 0, int cost = 0, string ss1 = ""):date(day,month,year),deptime(dHour,dMin),arrtime(aHour,aMin)
	{
		airline = ss1;
		cityname = city;
		fare = cost;
		next = NULL;	
	}
	Date getdate() {
		return date;
	}
	Time getarrtime() {
		return arrtime;
	}
	Time getdeptime() {
		return deptime;
	}
	string getairline() {
		return airline;
	}
	string getcityname() {
		return cityname;
	}
	int getcost() {
		return fare;
	}
	bool operator==(Flight& f1) {
		if ((this->airline == f1.getairline()) && this->arrtime == f1.getarrtime() && this->date == f1.getdate() && this->deptime == f1.getdeptime() && this->cityname == f1.getcityname()) {
			return true;
		}
		return false;
	}
	Flight operator =(Flight& obj)
	{
		this->airline = obj.airline;
		this->arrtime = obj.arrtime;
		this->cityname = obj.cityname;
		this->date = obj.date;
		this->deptime = obj.deptime;
		this->fare = obj.fare;
		return *this;
	}

	void Display() {
		cout << cityname<<" ";
		date.Display();
		cout << " ";
		deptime.Display();
		cout << " ";
		arrtime.Display();
		cout << " " << fare;
		cout << " " << airline;
	}
};


