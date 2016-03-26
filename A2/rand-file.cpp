//Creating random Integers
//Can be in ascending, descending, or random order
//Sizes 10^2, 10^3, 10^4, 10^5 number of integers

#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class bad_filename{};

bool ascending (int i, int j) {return (i<j);}
bool descending (int i, int j) {return (i>j);}

int main()
try
{
	cout << "Enter file name: " << endl;
	string rand_file;
	cin >> rand_file;
	ofstream os {rand_file};
	if(!os) throw bad_filename{};
	cout << "Enter the number of randomized integers in your file" << endl
		 << "1. 100 Integers" << endl
		 << "2. 1000 Integers" << endl
		 << "3. 10000 Integers" << endl
		 << "4. 100000 Integers" << endl;
	int choice_int=0;
	int num_rand=0; //number of random integers in the file
	cin >> choice_int;
	
	switch (choice_int) {
	case 1:
		num_rand = 100;
		break;
	case 2:
		num_rand = 1000;
		break;
	case 3:
		num_rand = 10000;
		break;
	case 4:
		num_rand = 100000;
		break;
	default:
		cout << "Enter one of the numbers above" << endl;
		num_rand=0;
		break;
	}
	
	cout << "How do you wish for the numbers to be generated? " << endl
		 << "1. Random order" << endl
		 << "2. Increasing order" << endl
		 << "3. Decreasing order" << endl;
	int order_int=0;
	cin >> order_int;
	srand(time(NULL));
	
	vector <int> v_nums(num_rand); //declare vector of all those ints
	for(int i=0; i<v_nums.size(); ++i) { //put random ints into them
		v_nums[i] = rand()%num_rand; //range is dependent on size of user input
	}
	
	os << num_rand << "\r\n"; //Enters the number of integers to sort first
	if(order_int==1) { //output vector of ints in current order
		for(int i=0; i<v_nums.size(); ++i) {
			os << v_nums[i]; //test value for rand (between 0 and 100)
			os << "\r\n";
		}
	}
	if(order_int==2) { //sort v_nums in ascending order
		sort (v_nums.begin(), v_nums.end(), ascending);
		for(int i=0; i<v_nums.size(); ++i) {
			os << v_nums[i];
			os << "\r\n";
		}
	}
	if(order_int==3) { //sort v_nums in descending order
		sort (v_nums.begin(), v_nums.end(), descending);
		for(int i=0; i<v_nums.size(); ++i) {
			os << v_nums[i];
			os << "\r\n";
		}
	}
	if(order_int!=1 && order_int!=2 && order_int!=3){
		cout << "You did not enter a valid number for number generation";
	}
}

catch (bad_filename) {
	cerr << "Can't open input file";
}


