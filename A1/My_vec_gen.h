/*My_vec_gen.h
Qinqi Wang
221 - Section 502
Header file for a vector data structure.
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class My_vec {
	
	//member variables
	int size, capacity;
	T *ptr;
	
public:	
	//member functions
	My_vec();
	My_vec(int sz);
	~My_vec();
	My_vec(const My_vec<T>& vec);
	My_vec& operator=(const My_vec<T>& vec);
	int get_size() const;
	int get_capacity() const;
	T& operator[](int i) const;
	T& operator[](int i);
	bool is_empty() const;
	T& elem_at_rank(int r) const;
	void insert_at_rank(int r, const T& elem);
	void replace_at_rank(int r, const T& elem);
	void remove_at_rank(int r);
	
};
	
class bad_size{};
class bad_input{};

template <typename T>
ostream& operator<<(ostream& out, const My_vec<T>& vec);
	
template <typename T>
int find_max_index(const My_vec<T>& v,int size);
	
template <typename T>
void sort_max(My_vec<T>& vec);
	
template <typename T>
My_vec<T>::My_vec():
	size(0), capacity(10), ptr(new T[capacity]) {}

template <typename T>	
My_vec<T>::My_vec(int sz): size(sz), capacity(2*sz), ptr(new T[capacity]) 
{
	for(int i = 0; i<size; ++i) {
		ptr[i] = 0;
	}
}

template <typename T>
My_vec<T>::~My_vec() 
{
	delete ptr;
}

template <typename T>
My_vec<T>::My_vec(const My_vec<T>& vec):
	size(vec.size), capacity(vec.capacity), ptr(new T[vec.capacity])
{
	for(int i = 0; i<vec.size; ++i) {
		ptr[i] = vec.ptr[i];
	}
}

template <typename T>
My_vec<T>& My_vec<T>::operator=(const My_vec<T>& vec)
{
	if(size > capacity) { //size can NEVER be larger than capacity
		throw bad_size{};
	}
	T* copy = new T[vec.capacity];
	for(int i = 0; i<vec.size; ++i) {
		copy[i] = vec.ptr[i];
	}
	
	delete[] ptr;
	
	ptr = copy;
	size = vec.size;
	capacity = vec.capacity;
	
	return *this;
}

template <typename T>
int My_vec<T>::get_size() const
{
	return size;
}

template <typename T>
int My_vec<T>::get_capacity() const
{
	return capacity;
}

template <typename T>
T& My_vec<T>::operator[](int i) const
{
	return ptr[i];
}

template <typename T>
T& My_vec<T>::operator[](int i) 
{
	return ptr[i];
}

template <typename T>
bool My_vec<T>::is_empty() const
{
	return size==0;
}

template <typename T>
T& My_vec<T>::elem_at_rank(int r) const
{
	return ptr[r];
}

template <typename T>
void My_vec<T>::insert_at_rank(int r, const T& elem)
{
	if(r >= capacity) { //create larger vector if r is larger than capacity
		
		int newalloc = r*2;
		
		T* copy = new T[newalloc];
		
		for(int i = 0; i<size; ++i) {
			copy[i] = ptr[i];
		}
		
		delete[] ptr;
		ptr = copy;
		capacity = newalloc;
	}
	
	if(size >= capacity) {
		T* copy = new T[capacity*2];
		
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
			ptr[i] = {'\0'};
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

template <typename T>
void My_vec<T>::replace_at_rank(int r, const T& elem)
{
	if(size > capacity) { //size can NEVER be larger than capacity
		throw bad_size{};
	}
	
	int newalloc = 0;
	
	if(r >= capacity) { //create larger vector if r is larger than capacity

		newalloc = r*2;
		
		T* copy = new T[newalloc];
		
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
			ptr[i] = {'\0'};
		}
		
		size = r + 1;  //something's wrong here ---- FIXED
	}
	 
	ptr[r] = elem;
}

template <typename T>
void My_vec<T>::remove_at_rank(int r)
{
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
template <typename T>
ostream& operator<<(ostream& out, const My_vec<T>& vec)
{
	for(int i = 0; i<vec.get_size(); ++i ) {
		out << "[" << vec[i] << "]" << endl;
	}
	return out;
}

template <typename T>
int find_max_index(const My_vec<T>& v,int size)
{
	// check for invalid input for size
	int big_num = 0;
	for(int i = 1; i<v.get_size(); ++i)
	{
		if(v[big_num] < v[i]) {
			big_num = i;
		}
	}
	return big_num;
}

template <typename T>
void sort_max(My_vec<T>& vec)
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
	