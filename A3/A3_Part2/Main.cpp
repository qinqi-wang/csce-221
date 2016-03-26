//Main File for Part 2
//Qinqi Wang
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include "TemplateDoublyLinkedList.h"
//Function that dumps phonebook contents onto terminal
void output_phonebook(vector<DoublyLinkedList<Record>> v) {
	for(int i = 0; i<v.size(); ++i) {
		cout << v[i];
	}
}
//Searches the phonebook with last name as input, then first name and UIN if necessary
Record search_phonebook(DoublyLinkedList<Record> dr, string last) {
	DListNode<Record> *current = dr.getFirst();
	Record r; //the record we want to return
	Record dummy_r; //the record returned if an error occurs
	int match=0; //number of matching last names
	while(current != dr.getAfterLast()) { //iterate through whole linked list
		if(last==current->getElem().get_last()) { //if a match is found, continue iterating
			match++;
			r = current->getElem();
		}	
		current = current->getNext();
    }
	if(match > 1) { //if there are two or more people with the same last name...
		cout << "Please enter the first name for further clarification" << endl;
		string first;
		cin >> first;
		current = dr.getFirst(); //reset current
		match=0; //reset match
		while(current != dr.getAfterLast()) { //iterate through whole linked list
			if(first==current->getElem().get_first() && last==current->getElem().get_last()) { //if a match is found, continue iterating
				match++;
				r = current->getElem();
			}
			current = current->getNext();
		}
		if(match > 1) {
			cout << "Enter the UIN for further clarification" << endl;
			string UIN;
			cin >> UIN;
			current = dr.getFirst();
			match=0; //another reset
			while(current != dr.getAfterLast()) {
				if(UIN == current->getElem().get_UIN()) { 
					r = current->getElem();
					match++;
					return r;
				}
				current = current->getNext();
			}
			if(match==0) {
				return dummy_r;
			}
		}
		else if(match==1)return r;
		else if(match==0) {
			return dummy_r;
		}
	}
	else if(match==1)return r;
	else if(match==0) {
		return dummy_r;
	}
}

class bad_file{}; //thrown if filename is bad
class bad_search{}; //thrown if searchterm is bad
int main()
try
{
	vector<DoublyLinkedList<Record>> phoneBook(26); //each element in the vector corresponds to a letter
	cout << "Enter file name: " << endl;
	string book_file;
	cin >> book_file;
	ifstream ifs {book_file};
	if(!ifs) throw bad_file{}; //if the input stream cannot be read, an exception is thrown
	while(ifs) {
		string last, first, UIN, phone_num;
		ifs >> last >> first >> UIN >> phone_num; //read in 4 strings
		if(!ifs) break; //stops input once all the data has been read
		int vec_index = last[0]-'A'; //gets vector index based on ascii values
		Record r(last, first, UIN, phone_num); //creates new Record based on strings from file
		phoneBook[vec_index].insertOrderly(r); //inserts the Records and sorts them accordingly
	}

	//searching begins here
	cout << "Type in a last name to search for it: " << endl;
	string search_l;
	cin >> search_l;
	int s_index = search_l[0]-'A'; //last name has to be capitalized, exception is thrown if not
	if(s_index < 0) throw bad_search{};
	Record s = search_phonebook(phoneBook[s_index], search_l);
	if(s.get_first()=="0") throw bad_search{}; //does a check for the dummy record
	cout << s;

	//output_phonebook(phoneBook); //dumps phoneBook if desired
}
catch(bad_file) {
	cerr << "Bad File Name";
}
catch(bad_search) {
	cerr << "Did not find a result, don't forget to capitalize your names!";
}
