
// main_gen.cpp
//Tests all functionality of the generic My_vec class.

#include <iostream>
#include <stdexcept>
#include <vector>
#include "My_vec_gen.h"

int main()
try{
  
	cout << "Part 1" << endl;
	My_vec<int> v_int;
	v_int.insert_at_rank(0, 1);
	cout << v_int;
	cout << "v_int's size:" << v_int.get_size() << endl << endl;
	
	cout << "Part 2" << endl;
	v_int.insert_at_rank(0, 2);
	cout << v_int;
	cout << "v_int's size:" << v_int.get_size() << endl << endl;
		
	cout << "Part 3" << endl;
	v_int.insert_at_rank(10, 3);
	cout << v_int;
	cout << "v_int's capacity:" << v_int.get_capacity() << endl << endl;
	
	cout << "Part 4" << endl;
	v_int.remove_at_rank(2);
	cout << v_int;
	cout << "v_int's size:" << v_int.get_size() << endl << endl;

	cout << "Part 5" << endl;
	v_int.replace_at_rank(2, 4);
	cout << v_int;
	cout << "v_int's size:" << v_int.get_size() << endl << endl;

	cout << "Part 6" << endl;
	My_vec<int> v_int1(v_int);
	cout << v_int1 << endl;
	v_int1.replace_at_rank(2, 5);
	cout << v_int1;

	cout << "Part 7" << endl;
	My_vec<int> v_int2;
	v_int2.insert_at_rank(0, 6);
	cout << v_int2;
	cout << "v_int2's size:" << v_int2.get_size() << endl << endl;

	cout << "Part 8" << endl;
	v_int2 = v_int1;
	cout << v_int2;
	cout << "v_int2's size:" << v_int2.get_size() << endl << endl;

	int big_num1 = find_max_index(v_int2, 10);
	cout << "Part 9, Max index in v_int2: " << big_num1 << endl;
	sort_max(v_int2);
	cout << "Part 10, Sorted Vector:" << endl << v_int2;
	cout << "v_int2's capacity: " << v_int2.get_capacity() << endl;

	cout << "Part 11: " << endl;
	v_int2.replace_at_rank(14, 7);
	cout << v_int2; 

	
	//----------------------------------------------------------------------------

	cout << "Part 1" << endl;
	My_vec<double> v_double;
	v_double.insert_at_rank(0, 1.1);
	cout << v_double;
	cout << "v_double's size:" << v_double.get_size() << endl << endl;
	
	cout << "Part 2" << endl;
	v_double.insert_at_rank(0, 2.2);
	cout << v_double;
	cout << "v_double's size:" << v_double.get_size() << endl << endl;
		
	cout << "Part 3" << endl;
	v_double.insert_at_rank(10, 3.3);
	cout << v_double;
	cout << "v_double's size:" << v_double.get_size() << endl << endl;
	
	cout << "Part 4" << endl;
	v_double.remove_at_rank(2);
	cout << v_double;
	cout << "v_double's size:" << v_double.get_size() << endl << endl;

	cout << "Part 5" << endl;
	v_double.replace_at_rank(2, 4.4);
	cout << v_double;
	cout << "v_double's size:" << v_double.get_size() << endl << endl;

	cout << "Part 6" << endl;
	My_vec<double> v_double1(v_double);
	cout << v_double1 << endl;
	v_double1.replace_at_rank(2, 5.5);
	cout << v_double1;

	cout << "Part 7" << endl;
	My_vec<double> v_double2;
	v_double2.insert_at_rank(0, 6.6);
	cout << v_double2;
	cout << "v_double2's size:" << v_double2.get_size() << endl << endl;

	cout << "Part 8" << endl;
	v_double2 = v_double1;
	cout << v_double2;
	cout << "v_double2's size:" << v_double2.get_size() << endl << endl;

	int big_num2 = find_max_index(v_double2, 10);
	cout << "Part 9: " << big_num2 << endl;
	sort_max(v_double2);
	cout << "Part 10:" << endl << v_double2;
	cout << "v_double2's capacity: " << v_double2.get_capacity() << endl;

	cout << "Part 11: " << endl;
	v_double2.replace_at_rank(14, 7.7);
	cout << v_double2;

	//-----------------------------------------------------------------------------------

	cout << "Part 1" << endl;
	My_vec<string> v_string;
	v_string.insert_at_rank(0, "ab");
	cout << v_string;
	cout << "v_string's size:" << v_string.get_size() << endl << endl;
	
	cout << "Part 2" << endl;
	v_string.insert_at_rank(0, "cd");
	cout << v_string;
	cout << "v_string's size:" << v_string.get_size() << endl << endl;
		
	cout << "Part 3" << endl;
	v_string.insert_at_rank(10, "ef");
	cout << v_string;
	cout << "v_string's size:" << v_string.get_size() << endl << endl;
	
	cout << "Part 4" << endl;
	v_string.remove_at_rank(2);
	cout << v_string;
	cout << "v_string's size:" << v_string.get_size() << endl << endl;

	cout << "Part 5" << endl;
	v_string.replace_at_rank(2, "gh");
	cout << v_string;
	cout << "v_string's size:" << v_string.get_size() << endl << endl;

	cout << "Part 6" << endl;
	My_vec<string> v_string1(v_string);
	cout << v_string1 << endl;
	v_string1.replace_at_rank(2, "ij");
	cout << v_string1;

	cout << "Part 7" << endl;
	My_vec<string> v_string2;
	v_string2.insert_at_rank(0, "kl");
	cout << v_string2;
	cout << "v_string2's size:" << v_string2.get_size() << endl << endl;

	cout << "Part 8" << endl;
	v_string2 = v_string1;
	cout << v_string2;
	cout << "v_string2's size:" << v_string2.get_size() << endl << endl;

	int big_num3 = find_max_index(v_string2, 10);
	cout << "Max index in v_string2: " << big_num2 << endl;
	sort_max(v_string2);
	cout << "Sorted Vector:" << endl << v_string2;
	cout << "v_string2's capacity: " << v_string2.get_capacity() << endl;

	cout << "v_string2 with r=14 elem=7.0: " << endl;
	v_string2.replace_at_rank(14, "mn");
	cout << v_string2;	

}

catch(exception &error){
	cerr << "Error: " << error.what() << endl;
}
catch(bad_size){
	cerr << "Error: Your size was larger than the capacity of your vector." << endl;
}
catch(bad_input) {
	cerr << "Error: You cannot delete an element outside the vector." << endl;
}