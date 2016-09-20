//----------------------------------------------//
//												//
//	:: Sparse Matrix Addition :: Main ::		//
//	Created by: Viktor Dahbura					//
//	Date: 09/15/2016							//
//												//
//----------------------------------------------//

#include <iostream> 
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "array.h"
#include "linkedlist.h"
using namespace std;


int main()
{
	ifstream inStreamA;
	ifstream inStreamB;
	ofstream outStream;
	string line;
	int temp;
	int n1 = 0;
	int n2 = 0;
	int numRowsA = 0;
	int numRowsB = 0;
	int numRowsC = 0;
	float value;

	//GETTING THE NUMBER OF ROWS FOR THE MATRIX
	inStreamA.open("A.txt");
	while (getline(inStreamA, line)) {
		if (line[0] == '#' || line.length() == 0) continue;
		istringstream fn(line);
		fn >> temp;
		numRowsA++;
	}
	inStreamA.close();
	inStreamB.open("B.txt");
	while (getline(inStreamB, line)) {
		if (line[0] == '#' || line.length() == 0) continue;
		istringstream fn(line);
		fn >> temp;
		numRowsB++;
	}
	inStreamB.close();
	
	//NUMBER OF POSSIBLE ENTRIES FOR listC
	numRowsC = numRowsA + numRowsB;

	//CREATING THE MATRICES BASED ON NUMBER OF ROWS
	ArrayList listA(numRowsA);
	ArrayList listB(numRowsB);
	ArrayList listC(numRowsC);

	//FILLING MATRICES listA AND listB
	listA.readFile("A.txt");
	listB.readFile("B.txt");

	//SORTS THE ARRAYS USING BUBBLE SORT AND REMOVES ZEROS FROM INPUT
	listA.sort2();
	listB.sort2();
	listA.removeZeros();
	listB.removeZeros();

	//CHECK MATRIX FOR COMPATIBILITY FOR ADDITION
	listA.compareSizes(listB);

	//MOVE ELEMENTS TO listC FROM listA
	listA.moveToC(listA, listB, listC);

	//ADDITION RECURSIVE 
	listC.addRecursive(listB, 0, listB.listSize());

	//ADDITION NON RECURSIVE 
	/*for (int i = 0; i < listB.listSize(); i++) {
		listC.addNonRecursive(listB.getRow(i), listB.getCol(i), listB.getValue(i));
	}*/

	//SORT listC
	listC.sort2();

	//REMOVES ANY ZEROS, IF ANY, FROM ADDITION IN listC;
	listC.removeZeros();

	//SENDS listC TO THE OUTPUT FILE
	listC.sendToOutput("C.txt");





	//TESTING
	cout << endl;
	cout << numRowsA << " <- numRowsA " << endl;
	cout << numRowsB << " <- numRowsB " << endl;
	cout << numRowsC << " <- numRowsC " << endl;

	cout << listA.listSize() << " <- length of A" << endl;
	cout << listB.listSize() << " <- length of B" << endl;
	cout << listC.listSize() << " <- length of C" << endl << endl;

	listA.print();
	cout << endl;
	listB.print();
	cout << endl;
	listC.print();
	cout << endl;
	cout << listA.maxRow() << " " << listA.maxCol() << " <- list A's max Row and max Col" << endl;
	cout << listB.maxRow() << " " << listB.maxCol() << " <- list B's max Row and max Col" << endl;
	cout << listC.maxRow() << " " << listC.maxCol() << " <- list C's max Row and max Col" << endl;







	system("pause");
	return 0;
}

