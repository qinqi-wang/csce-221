//Record.h
//Class that holds student records
//Author: Qinqi Wang
//CSCE 221-502 Assignment 3

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Record {
private: 
string last, first, UIN, phone_num;

public:	
Record(string l="0", string f="0", string u="0", string p="0" )
	: last(l), first(f), UIN(u), phone_num(p) {}
string get_last() const{ return last;}
string get_first() const{ return first;}
string get_UIN() const{ return UIN;}
string get_phone() const{ return phone_num;}	
};

ostream& operator<<(ostream& out, Record& r) {
	out << "Last Name: " << r.get_last() << endl
	    << "First Name: " << r.get_first() << endl
		<< "UIN: " << r.get_UIN() << endl
		<< "Phone Number: " << r.get_phone() << endl << endl;
		
	return out;
}

//f()=3, O(1)
bool operator<(const Record& r1, const Record& r2) {
	return r1.get_last() <= r2.get_last() && r1.get_first() <= r2.get_first() && r1.get_UIN() <= r2.get_UIN(); //3
	//only compares last, first, and UIN
	//The comparison <= exists in case last & first name are the same, but UIN different
}

