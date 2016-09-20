//----------------------------------------------//
//												//
//	:: Sparse Matrix Addition :: Header ::		//
//	Created by: Viktor Dahbura					//
//	Date: 09/15/2016							//
//												//
//----------------------------------------------//

#pragma once
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;

struct Entry {
	int row;
	int col;
	float value;
};

class ArrayList {
public:
	ArrayList(int size);
	ArrayList();
	~ArrayList();

	int listSize() const;
	int maxListSize() const;
	void fill(int loc, int row, int col, float value);
	void print();
	int maxRow();
	int maxCol();
	int getRow(int loc);
	int getCol(int loc);
	float getValue(int loc);
	void readFile(string filename);
	void compareSizes(ArrayList& listB);
	void moveToC(ArrayList& listA, ArrayList& listB, ArrayList& listC);
	void addNonRecursive(int row, int col, float value);
	void addRecursive(ArrayList& listB, int i, int j);
	void sort2();
	void removeAt(int loc);
	void removeZeros();
	bool compareVal(int n, int m); 
	int getLineLoc(int n, int m);
	void sendToOutput(string filename);

	Entry *list;
	int length;
	int maxSize;
};

ArrayList::ArrayList(int size)
{
	maxSize = size;
	length = 0;
	list = new Entry[maxSize];
	assert(list != NULL);
}

ArrayList::~ArrayList() {
	delete[] list;
}

int ArrayList::listSize() const {
	return length;
}

int ArrayList::maxListSize() const {
	return maxSize;
}

void ArrayList::fill(int loc, int row, int col, float value) {
	list[loc].row = row;
	list[loc].col = col;
	list[loc].value = value;
	length++;
}

void ArrayList::print() {
	for (int i = 0; i < length; i++) {
		cout << list[i].row << " " << list[i].col << " " << setprecision(2) << fixed << list[i].value << endl;
	}
}

int ArrayList::maxRow() {
	return list[length - 1].row;
}

int ArrayList::maxCol() {
	return list[length - 1].col;
}

int ArrayList::getRow(int loc) {
	return list[loc].row;
}

int ArrayList::getCol(int loc) {
	return list[loc].col;
}

float ArrayList::getValue(int loc) {
	return list[loc].value;
}

void ArrayList::readFile(string filename) {
	int row, col;
	int n = 0;
	float value;
	string line;
	ifstream inStream;
	inStream.open(filename);
	while (getline(inStream, line)) {
		if (line[0] == '#' || line.length() == 0) continue;
		istringstream fn(line);
		fn >> row >> col >> value;
		fill(n, row, col, value);
		n++;
	}
	inStream.close();
}

void ArrayList::compareSizes(ArrayList& listB) {
	if (maxRow() != listB.maxRow() || maxCol() != listB.maxCol()) {
		cout << maxRow() << " " << maxCol() << " <- list A's max Row and max Col" << endl;
		cout << listB.maxRow() << " " << listB.maxCol() << " <- list B's max Row and max Col" << endl;
		cout << "Sparse matrices are not compatible for addition." << endl;
		cout << "Generating empty output File..." << endl;

		system("pause");
		exit(1);
	}
}

void ArrayList::moveToC(ArrayList& listA, ArrayList& listB, ArrayList& listC) {
	int i;
	int j = 0;
	for (i = 0; i < listC.maxListSize() && i < listA.listSize(); i++) {
		listC.fill(i, listA.getRow(i), listA.getCol(i), listA.getValue(i));
	}
}

void ArrayList::addNonRecursive(int row, int col, float value) {
	int addNew = length;
	for (int i = 0; i < maxListSize(); i++) {
		if (row == getRow(i) && col == getCol(i)) {
			list[i].value = list[i].value + value;
			return;
		}
	}
	fill(length, row, col, value);
}

void ArrayList::sort2() {
	bool swap;
	Entry temp;
	do {
		swap = false;
		for (int i = 0; i < listSize() - 1; i++) {
			if (list[i].row > list[i + 1].row) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				swap = true;
			}
			else if (list[i].row == list[i + 1].row && list[i].col > list[i + 1].col) {
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				swap = true;
			}
		} 
	} while (swap);
}

void ArrayList::removeZeros() {
	for (int i = 0; i < length - 1; i++) {
		if (list[i].value == 0) {
			removeAt(i);
			i--;
		}
		else
			continue;
	}
}

void ArrayList::removeAt(int loc) {
	for (int i = loc; i < length - 1; i++)
		list[i] = list[i + 1];
	length--;
}

void ArrayList::addRecursive(ArrayList& listB, int i, int listSizeOfB) {
	int loc = getLineLoc(listB.getRow(i), listB.getCol(i));

	if (i < listSizeOfB) {
		if (compareVal(listB.getRow(i), listB.getCol(i)) == true) {
			list[loc].value = list[loc].value + listB.list[i].value;
		}
		else {
			fill(length, listB.getRow(i), listB.getCol(i), listB.getValue(i));
		}
		addRecursive(listB, i + 1, listSizeOfB);
	}
}

bool ArrayList::compareVal(int n, int m) {
	 bool found = false;
	 for (int i = 0; i < listSize(); i++) {
		 if (n == getRow(i) && m == getCol(i)) {
			 found = true;
		 }
		 else
			 continue;
	 }
	 return found;
}

int ArrayList::getLineLoc(int n, int m) {
	 for (int i = 0; i < listSize(); i++) {
		 if (n == getRow(i) && m == getCol(i)) {
			 return i;
		 }
		 else
			 continue;
	 }
 }

void ArrayList::sendToOutput(string filename) {
	ofstream outStream;
	outStream.open(filename);
	outStream << "#Matrix C=A+B" << endl;
	for (int i = 0; i < listSize(); i++) {
		outStream << getRow(i) << " " << getCol(i) << " " << setprecision(2) << fixed << getValue(i) << endl;
	}
	outStream.close();
}

 






