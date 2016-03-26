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


bool ascending (int i, int j) {return (i<j);}
bool descending (int i, int j) {return (i>j);}

void generate(int A[], int size, int order_int) 
{	
	for(int i=0; i<size; ++i) { //put random ints into them
		A[i] = rand()%1000; //range is dependent on size of user input
	}
	
	if(order_int==2) { //sort v_nums in ascending order
		sort(A, A+size, ascending);
	}
	else if(order_int==3) { //sort v_nums in descending order
		sort(A, A+size, descending);
	}
	if(order_int!=1 && order_int!=2 && order_int!=3){
		cout << "You did not enter a valid number for number generation";
	}
}

