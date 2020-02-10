#pragma once
#include"Flight.h"
#include "Queue.h"

#include"City.h"
// structure to store edges
class FlightGraph {
public:
	Queuelist* ql;
	City* head; //adjacency list as array of pointers
	// Constructor
	FlightGraph(string fname) {
		head = NULL;
		ifstream fileread;
		ql = new Queuelist;
		string str;
		fileread.open(fname);
		while (getline(fileread, str))
		{
			str += ' ';
			int count = 0;
			int index = 0;
			string ss[7];

			for (int i = 0; i < 7; i++) {
				for (; (str[count] != ' '); count++) {
					ss[index] += str[count];
				}
				index++;
				count++;
			}

			index = 0;
			count=2;

			string stringtemp[8];
			int inttemp[8];

			while(count< 6){
				string output;
				string date = ss[count];
				date += '/';
				int b = 0;

				while (date[b] != '\0')
				{
					if (date[b] == '/' || date[b] == ':')
					{
						stringtemp[index] = output;
						output = "";
						index++;
						b++;
					}
				
					if (date[b] != '\0')
					{
						output += date[b];
						b++;
					}
				}
				count++;
			}
			for (int a = 0; a < 8; a++)
			{
				inttemp[a] = stoi(stringtemp[a]);

			}
			Insert(ss[0], ss[1], inttemp[0], inttemp[1], inttemp[2], inttemp[3], inttemp[4], inttemp[5], inttemp[6], inttemp[7],ss[6]);
		}
	}
	void Insert(string dep, string arr, int day, int month, int year, int dHour, int dSec, int aHour, int aMin, int cost, string airline) {
		if (head == NULL) {
			City* temp = new City(dep, arr, day, month, year, dHour, dSec, aHour, aMin, cost, airline);
			head = temp;
			//cout << temp->getname();
		}
		else {
			City* arrtemp = head;
			City* temp = head;
			while (temp->getname() != dep && temp->next != NULL) {
				temp = temp->next;
			}
			while (arrtemp->next != NULL && arrtemp->getname() != arr) {
				arrtemp = arrtemp->next;
			}
			if (arrtemp->next == NULL && arrtemp->getname() != arr && arr == "Sydney")
			{
				City* sydney=new City(arr,"",0,0,0,0,0,0,0,0,"");
				arrtemp->next = sydney;
				arrtemp = arrtemp->next;

			}
			if (temp->getname() == dep) {
				Flight* ftemp1 = new Flight(arr, day, month, year, dHour, dSec, aHour, aMin, cost, airline);
				temp->addflight(ftemp1);
			}
			else {
				City* tempcity = new City(dep, arr, day, month, year, dHour, dSec, aHour, aMin, cost, airline);
				temp->next = tempcity;
				//cout << temp->getname()<<endl;
			}
		}
		return;
	}
	void Display() {
		City* temp = head;
		while (temp != NULL) {
			cout << temp->getname() << endl;
			Flight* ftemp = temp->flights;
			while (ftemp != NULL) {
				ftemp->Display();
				cout << "\n";
				ftemp = ftemp->next;

			}
			temp = temp->next;
		}
		return;
	}

	// Destructor
	~FlightGraph() {
		delete[] head;
	}
	void DisplayFlights(string dep = "", string arr = "",int order=1, City* ctemp = NULL, FlightQueue* fq = NULL) {
		City* temp;
		if (ctemp == NULL) {
			temp = head;
			fq = new FlightQueue;
			while (temp->getname() != dep) {
				temp = temp->next;
			}
		}
		else {
			temp = ctemp;
		}
		Flight* ftemp = temp->flights;
		temp->visited = true;
		while (ftemp != NULL) {
			City* destination = head;
			while (destination->getname() != ftemp->getcityname()) {
				destination = destination->next;
			}
			if (ftemp->getcityname() == arr) {
				fq->Enqueue(ftemp->getcityname(), ftemp->getdate(), ftemp->getdeptime(), ftemp->getarrtime(), ftemp->getairline(), ftemp->getcost());
				fq->datechecking();
				if (fq->transitcheck) {
					fq->totalcost = 0;
					fq->flighthours = 0.0f;
					fq->costcalculator();
					fq->timecalculator();
					FlightQueue* hadi = new FlightQueue;
					*hadi = fq;
					ql->insert(hadi,order);
				}
				fq->DequeueRear();
			}
			else if (destination->visited==true || destination->flights==NULL) {
			}
			else {
				fq->Enqueue(ftemp->getcityname(),ftemp->getdate(),ftemp->getdeptime(),ftemp->getarrtime(),ftemp->getairline(),ftemp->getcost());
				DisplayFlights(ftemp->getcityname(), arr,order, destination, fq);
			}
			ftemp = ftemp->next;
		}
		fq->DequeueRear();
		temp->visited = false;
		return;
	}
	void adjusttimeandhotel(string fname) {
		ifstream fileread;
		fileread.open(fname);
		string temp;
			while (getline(fileread, temp)) {
				temp += ' ';
				string cityname;
				int time,hotelcharge;
				int a = 0;
				string temp1;
				for (int c = 0; c < 3; c++) {
					while (temp[a] != ' ') {
						temp1 += temp[a];
						a++;
					}
					if (c == 0) {
						cityname = temp1;
						temp1 = "";
					}
					else if(c==1) {
						time = stoi(temp1);
						temp1 = "";
					}
					else {
						hotelcharge = stoi(temp1);
						temp1 = "";
						City* check = head;
						while (check != NULL) {
							if (check->getname() == cityname) {
								check->timezone = time;
								check->hotelcharge = hotelcharge;
								check->adjustflight();

							}
							check = check->next;
						}
						temp1 = "";
					}
					a++;
				}
		}
	}

	void costdisplay(int ftype,string airline,string transit,int d) {
		ql->Display(ftype,airline,transit,d);
	}
};