// BrysonEdwardsSOList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "llist.h"
#include "SelfOrderedList.h"
#include "MTFSelfOrderedList.h"
#include "TransposeSelfOrderedList.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
template <typename E>
void charOutput(SelfOrderedListADT<E> &SOL, string nameOfHeuristic, char findStart[], int max);
template <typename E>
void stringOutput(SelfOrderedListADT<E> &SOL, string nameOfHeuristic);
int main()
{
	// Variables
	//Const Variables
	const int fSAS = 14;
	const int SAS = 8;

	//Non Const Variables
	char starter[SAS] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char findStarter[fSAS] = { 'F', 'D', 'F', 'G', 'E', 'G', 'F', 'A', 'D', 'F', 'G', 'E', 'H', 'I' };
	SelfOrderedList<char> so;
	MTFSelfOrderedList<char> mtfSO;
	TransposeSelfOrderedList<char> tSO;

	// Program Logic
	for (int i = 0; i < SAS; i++) { // Loop the chars into the LinkedLists
		so.add(starter[i]);
		mtfSO.add(starter[i]);
		tSO.add(starter[i]);
	}

	//Output Results
	charOutput(so, "Count", findStarter, fSAS);	
	cout << endl;

	charOutput(mtfSO, "MoveToFront", findStarter, fSAS);
	cout << endl;

	charOutput(tSO, "Transpose", findStarter, fSAS);
	cout << endl << endl << endl;


	//Non Const Variables
	SelfOrderedList<string> soString;
	MTFSelfOrderedList<string> mtfSOString;
	TransposeSelfOrderedList<string> tSOString;

	// Program Logic
	ifstream input;
	input.open("test.txt");
	if (!input)
	{
		cerr << "Unable to open file";
		exit(1);
	}
	string x;
	while (input >> x) { // Loop the chars into the LinkedLists
		soString.find(x);
		mtfSOString.find(x);
		tSOString.find(x);
	}
	input.close();

	//Output Results
	stringOutput(soString, "Count");
	cout << endl;

	stringOutput(mtfSOString, "MoveToFront");
	cout << endl;

	stringOutput(tSOString, "Transpose");
	system("pause");
    return 0;
}

template <typename E> // A function to format all char output 
void charOutput( SelfOrderedListADT<E> &SOL, string nameOfHeuristic, char findStart[], int max) 
{
	string desiredOutput;
	if (nameOfHeuristic == "Count")
		desiredOutput = "      F G D E A H B C I and compares should be 61";
	else if (nameOfHeuristic == "MoveToFront")
		desiredOutput = "      I H E G F D A B C and compares should be 70";
	else if (nameOfHeuristic == "Transpose")
		desiredOutput = "      A B F D G E H C I and compares should be 78";

	cout << "Testing " << nameOfHeuristic << ". . ." << endl;
	cout << "-My starting list structure for the " << nameOfHeuristic << " heuristic is:" << endl;
	cout << "      ";
	SOL.printlist();
	cout << endl;


	for (int i = 0; i < max; i++) { //Loop through looking for the chars in findStart
		SOL.find(findStart[i]);
	}
	cout << "-Testing my " << nameOfHeuristic << " heuristic.  If correct my list should be: " << endl;
	cout << desiredOutput << endl;

	cout << "-The number of compares for ";
	for (int i = 0; i < max; i++) {
		cout << findStart[i] << " ";
	}
	cout << " is " << SOL.getCompares() << endl;


	cout << "-My final list structure with frequencies is: " << endl;
	cout << "      ";
	SOL.printlist();
	cout << endl;
}
template <typename E> // A function to format all string output
void stringOutput(SelfOrderedListADT<E> &SOL, string nameOfHeuristic)
{
	cout << nameOfHeuristic << " Heuristic: Size of List - " << SOL.size();
	cout << endl;
	cout << "Number of Compares: " << SOL.getCompares();
	cout << endl;
	SOL.printlist(10);
	cout << endl << endl;
}
