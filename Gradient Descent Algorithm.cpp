//Code finds the optimal place to put a delivery hub in GB by minimising the average distance needed to travel to reach a person. This distance is the straight line distance like a drone may take.
//Data on locations and populations is read in from a csv file. A random location within the range of the locations in the csv file is then chosen and the mean distance for this point is found. 
//It is then minimised by the hill climbing (or descending in this case as looking for a minima) method shown in the examples where it takes steps around a point and sees how optimal each one is. 
//This method has been improved by:
//-Varying the step size. Starting it at a high value means it takes less time to get nearer the minima increasing efficiency and also means step size can take smaller values so the minima is more accuratelty found.
//-Creating a bias in the code to travel in the same direction as the previous step. This makes the code travel in more straight lines from the random starting point to the minima, rather then zig-zagging there, increasing effiency.
//-The nearest city from the minima and its distance is found and outputted so the user can have a greater understanding of where the most optimal location is. The mean distance to a person at the optimal location is also outputted
//-The random starting point is done in the range of values from the csv file rather then inputting directly what range the random numbers should take.
//Jack McGinn
//16/12/2018

// Neccesary packages are included
#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>

//Namespace shortcut
using namespace std;

// Key global variables defined, global so that they can be used in all functions
vector<int> population;
vector<double> latitude;
vector<double> longitude;
int f_evals = 0; // Keeps count of function evaluations
int pop_total = 0;
#define PI  3.14159
double R = 3958.75; //Radius of Earth in miles

//functions
double haversine_formula(double lat, double lon, int t) {
	double lat_dif, lon_dif;
	double a, c;
	// Calculates and returns great circle distance of points within the lattitude,longitude vector to the point lat, lon which is inputted in to the function
	lat_dif = lat - latitude[t];
	lon_dif = lon - longitude[t];
	a = (sin(lat_dif / 2)*sin(lat_dif / 2)) + cos(lat)*cos(latitude[t])*(sin(lon_dif / 2)*sin(lon_dif / 2));
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return c;
}

double fitness(double lat, double lon) {
	// Function calculates and returns mean distance to a person from a point that is inputted.  
	double c;
	double mean_distance = 0;
	//Loop runs through all latitudes and longitudes to calculate their distance from the point times by the population there and iteratively adds them to eachother
	for (unsigned int t = 0; t < longitude.size(); t++) {
		c = haversine_formula(lat, lon, t);
		mean_distance += R * c * population[t]; //
	}
	mean_distance = mean_distance / pop_total; //Dividing this by total population will give mean distance to a person
	f_evals++; //Increased each time this function is called
	return mean_distance;
}

double random_number(double lower, double upper) {
	// function to return a random number between two limits, lower and upper
	double random;
	srand((unsigned(time(NULL)))); // Seeds random number generator
	random = (rand() % (100 + 1)); // Produces a random number between 0 and 100
	random = lower + ((upper - lower)*(random/100)); 
	return random;
}

int main() {
	// Key variables are declare 
	vector<string> name;
	string line;
	int dlat = 0;//Stores step direction and previous step direction to get to a more optimal point
	int dlon = 0;
	double lat, lon; // Holds the current best values of latitude and longitude
	double step = 0.5; // Step size to move in latitude and longitude, is varied in size depending on whether the maximum was reached or not, for efficiency and accuracy
	double value, oldValue, newValue, minValue;
	int iteration = 1;
	int not_first_line = 0;//Variable to make sure first row of csv file is not read in as this is just titles
	int index = 0;// Variable stores the vector position of the city that is the minimum distance from the final optimized location
    double min_dist = PI * R;//Variable to help figure out closest city from optimized point. Variable should initially be set to the maximum possible so you can find values less then it
	// Below variables will store the maximum/minimum positoins of towns and cities so random numbers can be generated in this range
	double lat_max = -PI;
	double lon_max = -PI / 2;
	double lat_min = PI;
	double lon_min = PI / 2;

	// Open an input file to read in its data 
	ifstream theFile("GBplaces.csv");

	//Conditional to check if the file opened successfully so it can be used.
	if (theFile.is_open()) {

		// While you can still get a line from the file the code in the loop keeps running, when you can't the loop stops as all data has been read.
		while (getline(theFile, line)) {
			// Conditional checks that the loop is not on the first line so it doesn't read this data in
			if (not_first_line > 0) {
				stringstream  lineStream(line); //Used to manipulate strings easier
				string  cell;
				int column_number = 0;// Stores which column the code is on and increases as you go through the column for each row

				//While there are still lines to get from linestream where a comma represents the begining of a new line
				while (getline(lineStream, cell, ',')) {
					//Conditional to check which column the row is on so code can add the data from that column to the appropriate vector representing it 
					if (column_number == 0) {
						name.push_back(cell);
					}
					if (column_number == 2) {
						population.push_back(int(atof(cell.c_str())));
					}
					if (column_number == 3) {
						//Lattitudes and longitudes are converted straight in to radians for calculation in the haversine formula
						latitude.push_back((atof(cell.c_str()) / 180)*PI);
					}
					if (column_number == 4) {
						longitude.push_back((atof(cell.c_str()) / 180)*PI);
					}
					column_number++;
				}
			}
			not_first_line++;//Increased so that code can register its past the first line and start reading data in
		}
		theFile.close();
	}
	else {
		cout << "Error, file could not be found\n";
		exit(1); //File couldn't be found so the rest of the program can't be done.The program should then be exited.
	}
	
	//Loop to run a number from 0 to the length of the vectors storing data from the csv, so they can be indexed with this number to find out various properties about them
	for (unsigned int i = 0; i < (population.size()); i++) {
		//Population and pop_total stored as ints to save memory
		pop_total += population[i];
		//Conditionals to check current index of vector against the maximum or minimum value currently found from the vector, to set this value to the current max/min if it is
		if (latitude[i] > lat_max) {
			lat_max = latitude[i];
		}
		if (latitude[i] < lat_min) {
			lat_min = latitude[i];
		}
		if (longitude[i] > lon_max) {
			lon_max = longitude[i];
		}
		if (longitude[i] < lon_min) {
			lon_min = longitude[i];
		}
	}
	//Random number for lattitude and longitude generated by the function in the correct range
	lat = random_number(lat_min, lat_max);
	lon = random_number(lon_min, lon_max);

	// Loop to repeat the process of finding the minimum with gradually decreasing step size after each loop. Looped six times as this will give an accuracy in position to 0.000005 radians which is good enough
	for (unsigned int p = 0; p < 6; p++) {
		// Work out mean distance to person at random starting point
		value = fitness(lat, lon);
		//Do is similar to a while loop, it completes the code then checks it matches a condition at the end rather thn begining
		do {
			// Save the current value
			oldValue = value;
			minValue = oldValue; // Set the minValue for the local search to be the current value

			//Find out the value for the location when stepping in the same direction as the previous one (previous direction stored in dLat,dLon) to try force the code to go in straight lines to the minima wherever possible
			newValue = fitness(lat + step * dlat, lon + step * dlon);
			//If this value is less then the minValue, then it means it was a more optimal direction to go in and the variables below should be changed accordingly
			if (newValue < minValue) {
				minValue = newValue;
				lat += step * dlat;
				lon += step * dlon;
				value = minValue;
			}
			//If stepping in the same direction was not optimal, check for other directions
			else {
				// Now look around the current point to see if there's a better one nearby. 2 for loops generate 9 points around and including current one
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) { 
						//Don't want to check the fit for this point for when i=0 and j=0, because this is no change, so a conditional to make sure its not
						if (!(i == 0 && j == 0)) {
                            // Don't want to double check the fit for this point when moving in the same direction as the last step as this has already been done, conditional to check its not
							if (i == dlat && j == dlon) {
								//Variables set back to 0
								dlat = 0;
								dlon = 0;
							}
							//If the step it creates is a change in position and isn't double checking the fit continuing in the same direction, this is what being inside the else represents
							else {
								//Check the fit of a value stepping in this direction
								newValue = fitness(lat + step * i, lon + step * j); // value at neighbouring point
								//If this new value is lower then the current minValue then it is a more optimized location, so minValue should be set by this and the step direcrtion to generate it should be saved in dLat and dLon
								if (newValue <= minValue) { 
								    dlat = i;
									dlon = j;
									minValue = newValue;
								}
							}
						}
					}
				}
				// update lat and lon to new point with lower more optimized value
				lat += step * dlat;
				lon += step * dlon;
				value = minValue;
			}

			// Write out something so user can see what each step generates
			cout << iteration << " : " << lat << "," << lon << " : " << value << "\n";

			iteration++; // Add one to the iteration counter so can see total number of steps

		} while (value < oldValue); // Repeat all this while we can find a value less than the previous one
		step = step / 10; //Reduce step size for when code loops to repeat method for finding minimum, starting from the location where the minimum was found with the previous step size
	}

	//Loop counts an interger up to length of population vector size, to use as an index to get each population location and check its distance from the optimal point to get the closest city.
	for (unsigned int z = 0; z < population.size(); z++) {
		double distance;
		//Call haversine_formula function to find the distance of this population to the optimal location
		distance = R * haversine_formula(lat, lon, z);
		//Conditional to check if this location is the closest yet, min_dist stores the distance for the current closest population
		if (distance < min_dist) {
			min_dist = distance;
			// Position of closest population in vector saved, so it can be later indexed to output to the user
			index = z;
		}
    }

	//Output the key information for the reader to see, outputted in clear and easy way to understand statements
	cout << "Function evaluations: " << f_evals << "\n\n"; // write out the total number of function evaluations
	cout << "Optimal location for delivery hub is at position, latitude: " << (lat / PI) * 180 << " degrees\n";
	cout << "                                                  longitude: " << (lon / PI) * 180 << " degrees\n";
	cout << "It is minimised with a mean distance to a person of " << value << " miles \n";
	cout << "The closest city/town to this location is " << name[index] << " which is " << min_dist << " miles away\n";

	return 0;
}





