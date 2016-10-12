HW2.2 SPARSE MATRIX ADDITION
by Viktor Dahbura
Created: 09/26/2016

-About:
	This program adds two sparse matrices by using both C++ arrays and doubly linked-lists to store matrix data.
	It then implements either recursive or non-recursive methods for addition depending on user input.
  
-To compile:
	Command line for compiling in terminal:
	g++ -std=c++11 sparse.cpp -o sparse
  
-To run:
	Command line to run in terminal given 2 input .txt files and addition implementation (uses an argument manager):
	./sparse "operation=<add|multiply>;storage=<array|linkedlist>;recursive=<Y/N>;A=<file>;B=<file>;result=<file>"
  
	Example:
	./sparse "operation=add;storage=array;recursive=N;A=a.txt;B=b.txt;result=c.txt".
	
	**Note:
	If method of storage is not given, storage = array by default.
	If method of addition is not given, recursive = N by default.
