#ifndef MTFSELFORDEREDLIST_H
#define	MTFSELFORDEREDLIST_H

#include "SelfOrderedListADT.h"

template <typename E>
class MTFSelfOrderedList : public SelfOrderedListADT<E> {
private:
	LList<E> aList;
	int compares;
public:
	//Default constructor/destructor
	MTFSelfOrderedList() {}
	virtual ~MTFSelfOrderedList() {}

	//Look for 'it'.  If found return true and execute the self-ordering
	//heuristic used for ordering the list: count, move-to-front, or transpose.
	//Increments the compare instance variable every time it compares 'it' to
	//other members of the list. Returns true if 'it' is found.
	virtual bool find(const E& it) override;

	//Called by find if 'it' is not in the list. Adds the new 'it' to the list
	//Can also be called independently when initially loading the list with
	//unique values and when you want to load the list in the order 'it' is 
	//read without your re-order method being called (or the number of compares
	//being incremented.
	virtual void add(const E& it) override;  //Add new 'it' to the list


	virtual int getCompares() const override;   //Returns the number of accumulated compares
	virtual int size() const override;       //Returns the size of the list

											 //Print the list
											 //In order print of the list.  printlist() prints the entire list
											 //whereas printlist(n) prints n nodes.
	virtual void printlist() const override;
	virtual void printlist(int n) const override;

};
template <typename E>
inline bool MTFSelfOrderedList<E>::find(const E& it)
{
	bool found = false;
	int countHold;
	E itHolder;
	aList.moveToStart();
	for (int i = 0; i < aList.length() && found == false; i++)
	{
		compares++;
		if (aList.getValue() == it)
		{
			aList.addOne();
			found = true;

			//Heuristic
			//Holders for removed variable
			countHold = aList.getCounter();
			itHolder = aList.remove();
			//Move to front and insert
			aList.moveToStart();
			aList.insert(itHolder, countHold);
			return found;
		}
		else { aList.next(); }
	}
	if (!found)
	{
		//If not found, them insert it at the beginning
		aList.moveToStart();
		aList.insert(it, 0);
	}
	return true;
}

template <typename E>
inline void MTFSelfOrderedList<E>::add(const E& it)
{
	aList.append(it, 0); // New objects are appended
}



template <typename E>
inline int MTFSelfOrderedList<E>::getCompares() const
{
	return compares; //return compares
}
template <typename E>
inline int MTFSelfOrderedList<E>::size() const
{
	return aList.length(); // Return the LinkedLists' size
}

template <typename E>
inline void MTFSelfOrderedList<E>::printlist() const
{
	// Prints the FULL list
	aList.print(aList.length()); 
}

template <typename E>
inline void MTFSelfOrderedList<E>::printlist(int n) const
{
	// Prints n number of objects in the list
	aList.print(n);
}
#endif	/* MTFSELFORDEREDLIST_HPP */


