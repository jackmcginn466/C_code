// Jack McGinn
// 07/02/2020
//Assignment 2

// Program to compute mean, standard deviation and standarderror of the mean electronic charge. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

// Functions to compute mean of a given data set
double mean_calculator(double* data, double number_in_data_set) {
	double mean;
	double sum{ 0 };
	// For loop runs through data set so all the numbers in it can be totaled to give the sum
	for (int i{}; i < number_in_data_set; i++) {
		sum = sum + *(data + i);
	}
	mean = sum / number_in_data_set;
	return mean;
}

// Function to calculate the standard deviation of a given data set
double standard_deviation_calculator(double* data, double number_in_data_set, double mean) {
	double standard_deviation;
	double sum_difference_squared{ 0 };
	// For loop runs through data set so the sum of the difference between a data point and the mean all squared can be totaled
	for (int i{}; i < number_in_data_set; i++) {
		sum_difference_squared = sum_difference_squared + ((*(data + i) - mean) * (*(data + i) - mean));
	}
	standard_deviation = sqrt(sum_difference_squared * (1 / (number_in_data_set - 1)));
	return standard_deviation;
}

// Main function
int main() {
	double* my_data; // Pointer to a double of each data point
	string data;      // String that will store all the good pieces of data in the file seperated by commas
	int number_of_data_points{ 0 }; //Stores the amount of good data pieces in the file to initialise the size of the dynamic array
	string file_name;
	string line;

	//
	cout << "Input file name: " << endl;
	cin >> file_name;

	// Open an input file to read in its data 
	ifstream theFile(file_name);

	//Conditional to check if the file opened successfully so it can be used.
	if (theFile.is_open()) {
		//Read in each line of the file individually. 
		while (getline(theFile, line)) {
			// Check that the data on that line is just a number so can be accepted to callculate the mean
			if (!(line.find_first_not_of("0123456789. ") != string::npos)) {
				// Keep total of number of accepted data points so can use this to define the dynamic array
				number_of_data_points++;
				// Save the accepted data points in a string seperated by commas so that they can be indexed for
				data = data + line + ",";
			}
			else {
				//Output to the user any rejected data pieces for the calculations from the file, and what they were
				cout << "Data piece that had value " << line << " was rejected as it has the wrong form for calculations" << endl;
			}

		}
		theFile.close();
	}
	// If the file name was not found output this to the user and close the program
	else {
		cout << "Error, file could not be found\n";
		exit(1); //File couldn't be found so the rest of the program can't be done.The program should then be exited.
	}

	//Variables to save the positions of the commas in the string data so their positions can be indexed to find the individual pieces of data between them
	int position_initial_comma{};
	int position_next_comma{};
	// Define dynamic array to store all the data
	my_data = new double[number_of_data_points];

	// For loop to run through the string containing all the data so the individual pieces between the commas can be stored in the dynamic array for further calculation
	for (int i{}; i < number_of_data_points; i++) {
		position_next_comma = data.find(",", position_initial_comma + 1);
		// Store the data pieces from the string of al the data to the dynamic array
		*(my_data + i) = stod(data.substr(position_initial_comma, (position_next_comma - position_initial_comma)));
		position_initial_comma = position_next_comma + 1;
	}

	//Using the functions defined at th start, from the read in data set from the file, calculate the mean, standard deviation and standard error on the mean
	double mean = mean_calculator(my_data, number_of_data_points);
	double standard_deviation = standard_deviation_calculator(my_data, number_of_data_points, mean);
	double standard_error_on_mean = standard_deviation / sqrt(number_of_data_points);

	// Free memory
	delete[] my_data;

	//Output to the user all the required values calculated from the given data set in the file
	cout << "Number of data pieces in the calcultions is " << number_of_data_points << endl;
	cout << "The data has mean " << mean << " with standard error in the mean of " << standard_error_on_mean << endl;
	cout << "The standard deviation is " << standard_deviation;

	return 0;
}
