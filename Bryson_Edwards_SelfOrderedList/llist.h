#ifndef LLIST_H
#define	LLIST_H

#include "book.h"
#include "link.h"
#include "list.h"

// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include in your code if you want access to the
// complete LList template class

// First, get the declaration for the base list class
#include "list.h"

// This is the declaration for LList. It is split into two parts
// because it is too big to fit on one book page
// Linked list implementation
template <typename E> class LList: public List<E> {
private:
  Link<E>* head;       // Pointer to list header
  Link<E>* tail;       // Pointer to last element
  Link<E>* curr;       // Access to current element
  int cnt;    	       // Size of list

  void init() {        // Intialization helper method
    curr = tail = head = new Link<E>;
    cnt = 0;
  }

  void removeall() {   // Return link nodes to free store
    while(head != NULL) {
      curr = head;
      head = head->next;
      delete curr;
    }
  }

public:
  LList(int size=defaultSize) { init(); }    // Constructor
  ~LList() { removeall(); }                   // Destructor
  void print(int n) const               // Print list contents
  {
	  //Link<E>* currHolder = curr;
	  Link<E>* it = head->next;
	  for (int i = 0; i < n; i++)
	  {
		  cout << it->element << "-" << it->counter;
		  if (i == (cnt - 1))
			  cout << ".";
		  else
			  cout << "   ";
		  it = it->next;
	  }
  }
  void clear() { removeall(); init(); }       // Clear list

  // Insert "it" at current position
  void insert(const E& it, int count) {
    curr->next = new Link<E>(it, count, curr->next);  
    if (tail == curr) tail = curr->next;  // New tail
    cnt++;
  }

  void append(const E& it, int count) { // Append "it" to list
    tail = tail->next = new Link<E>(it, count, NULL);
    cnt++;
  }

  void addOne() { curr->next->counter = curr->next->counter++; }
  int getCounter() const { return curr->next->counter; }


  //bool transpose() 
  //{
	 // /*Link<E>* holder = curr->next;
	 // E it = curr->element;
	 // remove();
	 // prev();
	 // if (curr == head)
		//  return true;
	 // Link<E>* holderTwo = curr->next;
	 // E itTwo = curr->element;
	 // insert(it, 0);
	 // next();
	 // insert(itTwo, 0);*/
	 // if (curr == head)
		//  return true;
	 // prev(); prev();
	 // Link<E>* nextHold = curr;
	 // cout << " Start " << endl;
	 // print();
	 // cout << endl;
	 // // For LL < | A B C D >
	 // nextHold->next = curr->next; // holder for current's next pointer
	 // // < | A [H] B C D > 
	 // E itHold = curr->element;
	 // curr->next = curr->next->next; // Linking A to C
	 // // < | A C [H]  D >
	 // //          B
	 // nextHold->next->next = curr->next->next->next; // Linking B to D
	 // // < | A C [H] B D >
	 // curr->next->next = nextHold->next; // Linking C to B
	 // //        [H]
	 // // < | A C B D >
	 //// nextHold->next = NULL;
	 // //delete nextHold;
	 // print();
	 // cout << endl << endl;
	 // return true;
  //}
  // Remove and return current element
  E remove() {
    Assert(curr->next != NULL, "No element");
    E it = curr->next->element;      // Remember value
    Link<E>* ltemp = curr->next;     // Remember link node
    if (tail == curr->next) tail = curr; // Reset tail
    curr->next = curr->next->next;   // Remove from list
    delete ltemp;                    // Reclaim space
    cnt--;			     // Decrement the count
    return it;
  }

  void moveToStart() // Place curr at list start
    { curr = head; }

  void moveToEnd()   // Place curr at list end
    { curr = tail; }

  // Move curr one step left; no change if already at front
  void prev() {
    if (curr == head) return;       // No previous element
    Link<E>* temp = head;
    // March down list until we find the previous element
    while (temp->next!=curr) temp=temp->next;
    curr = temp;
  }

  // Move curr one step right; no change if already at end
  void next()
    { if (curr != tail) curr = curr->next; }

  int length() const  { return cnt; } // Return length

  // Return the position of the current element
  int currPos() const {
    Link<E>* temp = head;
    int i;
    for (i=0; curr != temp; i++)
      temp = temp->next;
    return i;
  }

  // Move down list to "pos" position
  void moveToPos(int pos)   {
    Assert ((pos>=0)&&(pos<=cnt), "Position out of range");
    curr = head;
    for(int i=0; i<pos; i++) curr = curr->next;
  }

  const E& getValue() const { // Return current element
    Assert(curr->next != NULL, "No value");
    return curr->next->element;
  }
};

#endif