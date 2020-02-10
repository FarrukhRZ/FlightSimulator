#include "Flight.h"

class Node {
public:
	Time deptime,arrtime;
	Date flightdate;
	string arr;
	int fare;
	string airline;
	Node* next;
	Node() {
		deptime = 0;
		arrtime = 0;
		flightdate = 0;
		arr = "";
		fare = 0;
		next = NULL;
	}
	void Display() {
			cout << arr << " ";
			flightdate.Display();
			cout << " ";
			deptime.Display();
			cout << " ";
			arrtime.Display();
			cout << " " << fare;
			cout << " " << airline;
	}
};



class FlightQueue {
	Node* front, * rear;

public:
	FlightQueue* next;
	string airline;
	int totalcost;
	float flighthours;
	bool aircheck,datecheck,transitcheck,istransit;
	Date prevdate;
	Time prevtime;
	FlightQueue() {
		front = NULL;
		rear = NULL;
		next = NULL;
		totalcost = 0;
		airline = "";
		aircheck = true;
		datecheck = false;
		transitcheck = true;
		istransit = true;
		flighthours = 0.0f; prevdate = 0; prevtime = 0;
	}
	void Enqueue(string a, Date d1, Time dept,Time arrt,string airl,int fare ) {
		Node* temp = new Node;
		if (datecheck) {
			d1.day++;
			datecheck = false;
		}
		temp->flightdate = d1;
		temp->arrtime = arrt;
		temp->deptime = dept;
		temp->arr = a;
		temp->airline = airl;
		temp->fare = fare;
		if (front == NULL) {
			front = temp;
			rear = temp;
			front->next = NULL;
			airline = airl;
			prevdate = d1;
			prevtime = arrt;
		}
		else {
			
			prevtime = arrt;
			prevdate = d1;
			if (airline != airl) {
				aircheck = false;
			}
			rear->next = temp;
			temp->next = NULL;
			rear = temp;
		}
	}
	void costcalculator() {
		Node* temp = front;
		while (temp != NULL) {
			totalcost += temp->fare;
			temp = temp->next;
		}
	}
	void timecalculator() {
		Node* temp = front;
		while (temp != NULL) {
			if (temp->arrtime < temp->deptime) {
				datecheck = true;
				float x = 24.0f - temp->deptime.hr;
				x -= (temp->deptime.min / 60.0f);
				x += float(temp->arrtime.hr);
				x += (temp->arrtime.min / 60.0f);
				flighthours += x;
			}
			else {
				float x = temp->arrtime.hr + (temp->arrtime.min / 60.0f);
				float y = temp->deptime.hr + (temp->deptime.min / 60.0f);
				x = x - y;
				flighthours += x;
			}
			temp = temp->next;
		}
	}
	void datechecking() {
		transitcheck = true;
		if (front->next == NULL) {
			istransit = false;
			return;
		}
		else {
			istransit = true;
		}
		Node* temp = front;
		while (temp != rear) {
			if (temp->next->flightdate < temp->flightdate ||(temp->next->flightdate == temp->flightdate &&temp->next->deptime < temp->arrtime)) {
				transitcheck = false;
			}
			temp = temp->next;
		}
	}

	void DequeueRear()
	{	
		if (front == NULL) {
			return;
		}
		Node* temp = front;
		while (temp->next != rear && temp != rear)
		{
			temp = temp->next;
		}
		if (temp == rear) {
			front = NULL;
			rear = NULL;
			return;
		}
		delete rear;
		rear = temp;
	}
	void clear() {
		Node* temp = front;
		while (temp != rear) {
			front = front->next;
			delete temp;
			temp = front;
		}
		delete rear;
		front = NULL;
		rear = NULL;
	}
	bool isEmpty() {
		if (front == NULL) {
			return true;
		}
		return false;
	}
	
	bool display(int x=3,string airline="Any",string transit="Any",int d=0) {
		Node* temp = front;
		int check = 0;
		if ((x == 1) && !istransit && (airline == front->airline || airline == "Any")&&(d==0||d==front->flightdate.day)) {
			front->Display();
			cout << " " << totalcost << " " << flighthours << endl;
			return 1;
		}
		else if (x == 2 && istransit && ((aircheck && front->airline==airline)|| airline == "Any") && (d == 0 || d == front->flightdate.day)) {
			bool transcheck = false;
			temp = front;
			while (temp!= NULL && temp->next != rear) {
				if (temp->arr == transit) {
					transcheck = true;
				}
				temp = temp->next;
			}
			temp = front;
			while (temp != NULL) {
				if (transit == "Any") {
					temp->Display();
					cout << " ";
					check++;
				}
				else {
					if (transcheck) {
						temp->Display();
						cout << " ";
						check++;
					}
				}
				temp = temp->next;
			}
			if ((transcheck || transit == "Any") && (d == 0 || d == front->flightdate.day)) {
				cout << " " << totalcost << " " << flighthours << endl;
			}
		}
		else if (x==3&&((aircheck==true && front->airline == airline) || airline == "Any")&&(d == 0 || d == front->flightdate.day)){
				while (temp != NULL) {
					temp->Display();
					cout << " ";
					temp = temp->next;
				}
				check++;
				cout << " " << totalcost << " " << flighthours << endl;		
		}
		if (check == 0) 
			return false;
		return true;
	}
	int queuelength() {
		int x = 0;
		while (front != rear) {
			x++;
			front = front->next;
		}
		return x;
	}
	~FlightQueue() {
		clear();
		delete front;
		delete rear;
	}
	FlightQueue& operator=(FlightQueue* f1) {
		Node* temp = f1->front;
		Node* n1 = new Node;
		*n1 = *temp;
		f1->rear->next=NULL;
		totalcost = f1->totalcost;
		flighthours = f1->flighthours;
		aircheck = f1->aircheck;
		datecheck = f1->datecheck;
		transitcheck=f1->transitcheck;
		prevdate=f1->prevdate;
		prevtime=f1->prevtime;
		front = n1;
		istransit = f1->istransit;
		Node* temp2 = front;
		temp = temp->next;
		while (temp!=NULL) {
			n1 = new Node;
			*n1 = *temp;
			temp2->next = n1;
			temp2 = temp2->next;
			temp = temp->next;
		}
		rear = n1;
		rear->next = NULL;
		return *this;
	}
};

class Queuelist {
public:
	FlightQueue* head;
	FlightQueue* last;
	Queuelist() {
		head = NULL;
		last = NULL;
	}
	void insert(FlightQueue* fq,int x=1) {
		if (head == NULL) {
			head = fq;
			last = fq;
			last->next = NULL;
		}
		else {
			FlightQueue* temp = head;
			if (x == 1) {
				if (fq->totalcost < temp->totalcost) {
					head = fq;
					fq->next = temp;
					last = temp;
				}
				else {
					while (temp->next != NULL && !(fq->totalcost < temp->next->totalcost)) {
						temp = temp->next;
					}
						fq->next = temp->next;
						temp->next = fq;

				}
			}
			else {
				if (fq->flighthours < temp->flighthours) {
					head = fq;
					fq->next = temp;
					last = temp;
				}
				else {
					while (temp->next != NULL && !(fq->flighthours < temp->next->flighthours)) {
						temp = temp->next;
					}
						fq->next = temp->next;
						temp->next = fq;

				}
			}
		}
	}
	
	void Display(int x = 3, string airline = "Any", string transit = "Any", int date=0) {
		FlightQueue* temp = head;
		if (temp == NULL) {
			cout << "No such flights are available\n";
			return;
		}
		bool check=false;
		while (temp != NULL) {
			bool tempcheck=temp->display(x,airline,transit,date);
			temp = temp->next;
			if (tempcheck == true)
				check = true;
		}
		if (check == 0) {
			cout << "No such flights are available\n";
		}
	}
};

