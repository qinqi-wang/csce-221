/*My_vec.cpp
Joseph Sapp
Header file for a vector data structure.
*/

#include "My_vec.h"
#include <cstring>

//My_vec::My_vec() : capacity(8), size(0) {}

//Initialize My_vec with size 0 and capacity 8
My_vec::My_vec(){
	size = 0;
	capacity = 8;
	ptr = new char[capacity];
	//point to new template T
}

//Copy to new
My_vec::My_vec(const My_vec& vec){
	if (!vec.is_empty()){
        	size = vec.size;
		capacity = vec.capacity;
		ptr = new char[capacity];
		for (int i = 0; i < capacity; i++)
                	ptr[i] = vec.ptr[i];
	}
}



My_vec::~My_vec() { delete ptr; }

My_vec& My_vec::operator=(const My_vec& vec){
	if (this != &vec){
		delete ptr;
		this->size = vec.size;
		this->capacity = vec.capacity;
		ptr = new char[capacity];
		memcpy(ptr, vec.ptr, vec.size);
	}
	return *this;
}

int My_vec::get_size() const { return size; }
int My_vec::get_capacity() const { return capacity; }
bool My_vec::is_empty() const { return ( size == 0 ); } //Returns true/false

// CONST = unchangable, next function for that
char& My_vec::operator[](int i) const{
	//Easy way to check if requested char exists with
	//If conditional 
	if (i < size && i >= 0){
		return ptr[i];
	}
	throw "Error in scope";
}

char& My_vec::operator[](int i){
	// DOUBLE CHECK THIS
	if (i < size && i >= 0){
		return ptr[i];
	}
	throw "Error in scope";
}

char& My_vec::elem_at_rank(int r) const {
	if (r >= 0 && r < size){
		return ptr[r];
	}
	throw "Error in scope";
}

void My_vec::insert_at_rank(int r, const char& elem){
	if (r > size || r < 0){
		throw "Error in scope";
	}
	if (size == capacity){
		capacity = capacity * 2; //Increases size of cap
		char* temp = new char[capacity];
		memcpy(temp, ptr, size);
		delete ptr;
		ptr = temp;
	}
	int i = size;
	while (i > r){
		ptr[i] = ptr[i-1];
		i--;
	}
	ptr[r] = elem;
	++size;
}

void My_vec::replace_at_rank(int r, const char& elem){
	if (r >= 0 && r < size){
		ptr[r] = elem;
	}
	else {
		throw "Error in scope";
	}
}

void My_vec::remove_at_rank(int r){
	if (r >= 0 && r < size){
		while (r + 1 < size){
			ptr[r] = ptr[r+1];
				r++;
		}
		--size;
	}
	else {
		throw "Error in scope";
	}
}

ostream& operator<<(ostream& out, const My_vec& vec){ //out or cout?
	int size = vec.get_size();
	out<<"[";
	for (int i = 0; i < size; i++){
		out<< vec[i] << " ";
	}
	out<<"]"<<endl;
	return out;
}

int find_max_index(const My_vec& v, int size){
	int v_size = v.get_size();
	if (size > v_size){
		throw "Error in scope";
	}
	else if (size ==1){
		return 0;
	}
	else {
		int prev = 0;
		int next = 1;
		while (next < size){
			if (v[prev] < v[next]){
				prev = next;
			}
			next++;
		}
		return prev;
	}
}

void sort_max(My_vec& vec){
	int size = vec.get_size();
	My_vec temp;
	while(size > 0){
		int max = find_max_index(vec, size);
		//Can't get this to work. Out of bounds, ABORT TRAP 6?
		//Error with [] operator, fixed
		temp.insert_at_rank(0, vec[max]);
		vec.remove_at_rank(max);
		--size;
	}
	vec = temp;	
}


/*My_vec.cpp
Qinqi Wang
221 - Section 502
Implementation file for a vector data structure.
*/
/*
#include "My_vec.h"
 //used for throwing exceptions


My_vec::My_vec(): //constructor with no inputs
	size(0), capacity(10), ptr(new char[capacity]) {}
	
My_vec::My_vec(int sz): size(sz), capacity(2*sz), ptr(new char[capacity]) //constructor with input to determine size
{
	for(int i = 0; i<size; ++i) {
		ptr[i] = '0';
	}
}
	
My_vec::~My_vec() //destructor
{
	delete ptr;
}
	
My_vec::My_vec(const My_vec& vec): //copy constructor
	size(vec.size), capacity(vec.capacity), ptr(new char[vec.capacity])
{
	for(int i = 0; i<vec.size; ++i) {
		ptr[i] = vec.ptr[i];
	}
}

My_vec& My_vec::operator=(const My_vec& vec) //overloaded = operators
{
	char* copy = new char[vec.capacity];
	for(int i = 0; i<vec.size; ++i) {
		copy[i] = vec.ptr[i];
	}
	
	delete[] ptr;
	
	ptr = copy;
	size = vec.size;
	capacity = vec.capacity;
	
	return *this;
}

int My_vec::get_size() const
{
	return size;
}

int My_vec::get_capacity() const
{
	return capacity;
}

char& My_vec::operator[](int i) const
{
	return ptr[i];
}

char& My_vec::operator[](int i) 
{
	return ptr[i];
}

bool My_vec::is_empty() const
{
	return size==0;
}

char& My_vec::elem_at_rank(int r) const
{
	return ptr[r];
}

void My_vec::insert_at_rank(int r, const char& elem) //insert a number at a position
{
	if(r >= capacity) { //create larger vector if r is larger than capacity
		
		int newalloc = r*2;
		
		char* copy = new char[newalloc];
		
		for(int i = 0; i<size; ++i) {
			copy[i] = ptr[i];
		}
		
		delete[] ptr;
		ptr = copy;
		capacity = newalloc;
	}
	
	if(size >= capacity) {
	char* copy = new char[capacity*2];
		
		for(int i = 0; i<size; ++i) {
			copy[i] = ptr[i];
		}
		
		delete[] ptr;
		ptr = copy;
		capacity = capacity*2;
	}
	
	if (r > size && r <= capacity) //if r is inbetween size and capacity, replace values
	{
		for(int i = r; i >= size; --i)
		{
			ptr[i] = ',';
		}
		
		size = r; 
	}
	
	for(int i = size-1; i >= r; i--) //shift elements up
	{
		ptr[i+1] = ptr[i];
	}
	
	ptr[r] = elem;
	size++;
}

void My_vec::replace_at_rank(int r, const char& elem)
{
	if(size > capacity) { //size can NEVER be larger than capacity, at least when replacing elements
		throw bad_size{};
	}
	
	int newalloc = 0;
	
	if(r >= capacity) { //create larger vector if r is larger than capacity

		newalloc = r*2;
		
		char* copy = new char[newalloc];
		
		for(int i = 0; i<size; ++i) {
			copy[i] = ptr[i];
		}
		
		delete[] ptr;
		ptr = copy;
		capacity = newalloc;
	}
	
	if (r >= size && r < capacity) //if r is inbetween size and capacity, replace values
	{
		for(int i = r; i >= size; --i)
		{
			ptr[i] = ',';
		}
		
		size = r + 1;  //something's wrong here ---- FIXED
	}
	 
	ptr[r] = elem; //replace value
}

void My_vec::remove_at_rank(int r)
{
	if(r > size) {
		throw bad_input{};
	}
	
	if(size > capacity) { //size can NEVER be larger than capacity
		throw bad_size{};
	}
	
	for(int i = r; i < size-1; ++i) //shift elements back
	{
		ptr[i] = ptr[i+1];
	}
	
	size = size - 1; //remove one element
}

//---------------------------------

ostream& operator<<(ostream& out, const My_vec& vec)
{
	for(int i = 0; i<vec.get_size(); ++i ) {
		out << "[" << vec[i] << "]" << endl;
	}
	return out;
}

int find_max_index(const My_vec& v,int size)
{
	// check for invalid input for size
	int big_num = 0;
	for(int i = 1; i<v.get_size(); ++i)
	{
		if(v[big_num] < v[i]) { //set the larger value to the max_index
			big_num = i;
		}
	}
	return big_num;
}

void sort_max(My_vec& vec) //bubble sort
{
	int n = vec.get_size();
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < n-i; ++j) {
			if (vec[j] > vec[j+1]) {
				swap(vec[j], vec[j+1]);
			}
		} 
	}
}
*/
