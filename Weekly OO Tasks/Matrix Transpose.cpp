// MatrixTranspose
// Reads in a comma separated .txt file of arbitrary numbers of rows, columns
// and computes the transpose of the data.
// Jack McGinn
// 30/11/2018

// Neccesary packages are included
#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//Namespace shortcut
using namespace std;

int main() {
	// Key variables are declare 
	vector<vector<string>> data; 
	string line;
	
	// Open an input file to read in its data 
	ifstream theFile("test_data.txt");

	//Conditional to check if the file opened successfully so it can be used.
	if (theFile.is_open()){
		
		// While you can still get a line from the file the code in the loop keeps running, when you can't the loop stops as all data has been read.
		while (getline(theFile, line)){
				vector <string> row; // create a temporary vector which will store each row of the matrix
				stringstream  lineStream(line); //Used to manipulate strings easier
				string  value;
				
				//While there are still lines to get from linestream where a comma represents the begining of a new line
				while (getline(lineStream, value, ',')) {
					row.push_back(value);
				}
				// Push temporary vector onto data vector. So basically adding all the rows on to the overall matrix
				data.push_back(row);
		}
		theFile.close();
	}
	else {
		cout << "Error, file could not found\n";
		exit(1); //File couldn't be found so the rest of the program can't be done.The program should then be exited.
	}
	
	// Declare vector to store transposed matrix. Its size and what type of data it stores has been set.
	vector<vector<string>> transpose(data[0].size(), vector<string>());
	
	// Loop runs through all the vectors in the data vector, effectively running through all the rows in the matrix.
	for (unsigned int i = 0; i < data.size(); i++) {
		
		// Loop runs all components in vector. Like running through each component in each row of the matrix
		for (unsigned int j = 0; j < data[i].size(); j++) {
			transpose[j].push_back(data[i][j]); // Code to transpose matrix
		}
	}
	
	// Open an output file to write all the data in to 
	ofstream myfile("Transposed_Matrix.txt");
	
	// Conditional to check if the file opened successfully so it can be wrote in to.
	if (myfile.is_open()) {
	
		// Loop runs through vector to isolate each individual vector inside, where each individual vector represents a row of the matrix.
		for (unsigned int i = 0; i < transpose.size(); i++) {
			int unsigned count = 1; // Variable to check how far through the row the loop is

			// Next Loop runs through each individual vector to isolate individual components inside. Each component corresponds to a component in the matrix.
			for (unsigned int j = 0; j < transpose[i].size(); j++) {
				myfile << (transpose[i])[j]; // Each component is outputted in to file 
				
				//Conditional checks code is not at the end of the row and executes code below if not
				if (count < transpose[i].size()){
					myfile << ","; // Outputs commas to seperate components but doesn't put one at the end of the rpw
				}
				count++;
			}
			myfile << "\n"; // New line to seperate rows
		}
		myfile.close();
		cout << "Matrix has been transposed and can be accessed in the Matrix Transposed file";
	}
	// Else, conditional above was not met. User is informed of this via a message on the output screen
	else cout << "Unable to open file";

	return 0;
}


