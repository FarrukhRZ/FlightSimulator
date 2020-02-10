#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"Flight.h"

class City {
	string name;
public:
	bool visited;
	City* next;
	Flight* flights;
	int edgecount;
	int timezone;
	int hotelcharge;
	City(string dep, string arr="", int day = 0, int month = 0, int year = 0, int dHour = 0, int dMin = 0, int aHour = 0, int aMin = 0, int cost = 0, string ss1 = 0, City* dest = NULL) {
		name = dep;
		hotelcharge = 0;
		timezone = 0;
		visited = false;
		if (arr == "") {
			flights = NULL;

		}
		else {
			flights = new Flight(arr, day, month, year, dHour, dMin, aHour, aMin, cost,ss1);
		}
	}
	void addflight(Flight* f1) {
		Flight* temp = flights;
		if (flights == NULL) {
			flights = f1;
			return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = f1;
	}

	int getedgecount() {
		return edgecount;
	}

	string getname() {
		return name;
	}
	void adjustflight() {
		Flight* temp = flights;
		while (temp != NULL) {
			temp->arrtime.hr += timezone;
			temp->deptime.hr += timezone;
			if (temp->arrtime.hr >= 24) {
				temp->arrtime.hr -= 24;
			}
			else if (temp->arrtime.hr < 0) {
				temp->arrtime.hr += 24;
			}
			if (temp->deptime.hr >= 24) {
				temp->deptime.hr -= 24;
				temp->date.day += 1;
			}
			else if (temp->deptime.hr < 0) {
				temp->deptime.hr -= 24;
				temp->date.day--;
			}
			temp = temp->next;
		}
	}
};
