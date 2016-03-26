#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "Record.h"
using namespace std;
template <typename T>
class DoublyLinkedList; // class declaration

// list node
template <typename T>
class DListNode {
private: T obj;
  DListNode *prev, *next;
  friend class DoublyLinkedList<T>;
public:
  DListNode(T a = T(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(a), prev(p), next(n) {}
  T getElem() const { return obj; }
  DListNode * getNext() const { return next; }
  DListNode * getPrev() const { return prev; }
};

// doubly linked list
template <typename T>
class DoublyLinkedList {
protected: DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(), trailer() // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
 // DListNode<T>* insertBefore(DListNode<T>* n);
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  DListNode<T>* insertOrderly(const T& obj); 

  T removeLast(); // remove the last node
};
// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

//--------------------------------------------------------------------------------------------------

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
// copy constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  header.next = &trailer; trailer.prev = &header;

  // Copy from dll
  /* Complete this function */
  //DListNode *p = dll->header;
  DListNode<T> *current = dll.getFirst();
  //header.next = copynode;
  while(current != dll.getAfterLast()) {
	  T copy = current->getElem();
	  DListNode<T> *newNode = new DListNode<T>(copy, trailer.prev, &trailer); //copy of insertLast code
	  trailer.prev->next = newNode;
	  trailer.prev = newNode;
	  current = current->next;
	  //copy_list = copy_list->next;
  }
  
}
// assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  // Delete the whole list
  /* Complete this function */
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
  
  // Copy from dll
  /* Complete this function */
   DListNode<T> *current = dll.getFirst();

  while(current != dll.getAfterLast()) {
	  T copy = current->getElem();
	  DListNode<T> *newNode = new DListNode<T>(copy, trailer.prev, &trailer); //copy of insertLast code
	  trailer.prev->next = newNode;
	  trailer.prev = newNode;
	  current = current->next;
  }
}
// insert the object to the first of the linked list
template <typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
template <typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

//-----------------------------------------------------------------------------
//F()=3n+8
//Big-O of O(n)
template <typename T>
DListNode<T>* DoublyLinkedList<T>::insertOrderly(const T& obj) {
	DListNode<T> *current = header.next; //1
	while(current != &trailer) { //runs n times
		if(obj < current->getElem()) { //runs the comparison n times, not the code below
			//insert happens only once
			DListNode<T>* newnode = new DListNode<T>(obj, NULL, NULL); //1
			newnode->next = current; //1
			if(current->prev !=NULL) //1
				current->prev->next = newnode; //1
			newnode->prev = current->prev; //1
			current->prev = newnode; //1
			return newnode; //1
		}
		current = current->next; //1
	}
	this->insertLast(obj); //1
	return &trailer; //1
}
//---------------------------------------------------------------------------------


// remove the first object of the list
template <typename T>
T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}
// remove the last object of the list
template <typename T>
T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}
// destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
template <typename T>
T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
template <typename T>
T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
template <typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
  
  /* Complete this function */
  DListNode<T> *current = dll.getFirst();
  while(current != dll.getAfterLast()) {
	T val = current->getElem();
	out << val;
	current = current->getNext();
  }
  return out;
}
