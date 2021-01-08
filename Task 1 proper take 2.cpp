// Assignment 1 
// Jack McGinn 29/01/2019
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>

//Function to calculate energy for given atomic orbital level (n) and given atomic number (Z). 
double energy_of_atomic_orbit(double n, int Z){
    //Even though n is an integer its input is taken to be a double so its reciporical does not give infinity
    double atomic_energy;
    const double Rydberg_energy{-13.6};
    atomic_energy = Rydberg_energy * Z * Z * (1 / n) * (1 / n);
    return atomic_energy;
}
// Function that repeatedly asks the user for an input until that input is definetly an integer and nothing else, then returns that input
int int_checker(std:: string quantity) {
    //Function keeps taking the input as a string until it satisfies the condition that it contains nothing but digits so is an integer
    int number;
    std::string number_as_string;
    std::cout << "Input " << quantity << " :  ";
    std:: cin >> number_as_string;
    //If the input fails the condition the input is cleared and the loop continues, otherwise the loop breaks.
    while (std::cin.fail() or std::cin.eof() or number_as_string.find_first_not_of("0123456789") != std::string::npos or number_as_string.length()>4) {
        std::cout << "\nInput invalid. Input "<< quantity << " number: " ;
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cin >> number_as_string;
    }
    // Convert input to an int so it can be used in calculations and return its value as the int
    number = std::stoi(number_as_string);
    return number;
}

int main(){
    // Key variables defined
    const double unit_charge{1.6 * pow(10,-19)};
    double energy_of_transition;
    std:: string repeat{"y"};
    std:: string eV_or_joules;
    int atomic_number, initial_quantum_number, final_quantum_number;
    //Loops whole code until user no longer wants to do anymore calculations
    while (repeat.compare("y") == 0) {
        // This variable takes value true or false depending if user input is valid in a loop, once valid this variable can be changed and the loop can be broken
        bool valid_input_check{ false };
        // Loop takes user input of atomic number till the input is of the right format and physically valid
        while (valid_input_check == false) {
            atomic_number = int_checker( "atomic number");
            if (atomic_number <= 0) {
                std::cout << "Atomic number must be greater than 0. Try again \n";
            }
            else {
                valid_input_check = true;
            }
        }
        // Loop takes user input of initial quantum number till the input is of the right format and physically valid
        while (valid_input_check == true) {
            initial_quantum_number = int_checker("initial quantum number");
            if (initial_quantum_number <= 0) {
                std::cout << "Initial quantum number must be greater then 1. Please input valid  number\n";
            }
            else {
                valid_input_check = false;
            }
        }
        // Loop takes user input of final quantum number till the input is of the right format and physically valid
        while (valid_input_check == false) {
            final_quantum_number = int_checker("final quantum number");
            // For photon emission, final quantum number must also be less then initial so this condition of the user input is also checked
            if (final_quantum_number <= 0 ) {
                    std::cout << "Final quantum number can not be 0 or less. Please input valid number\n";
            }
            else {
                    valid_input_check = true;
            }
        }
        // Calls function to calculate energy of each orbital user provided, and there difference will be the photon emission energy
        energy_of_transition = energy_of_atomic_orbit(initial_quantum_number, atomic_number) - energy_of_atomic_orbit(final_quantum_number, atomic_number);
        
        // Loop takes user input for whether they want the energy in joules or MeV until they give a valid answer 
        while (valid_input_check == true) {
            std::cout << "Would you like your photon energy in joules or eV? j for joules and e for eV\n";
            std::cin >> eV_or_joules;
            //If they want output as eV outputs photon energy in this form to user
            if (eV_or_joules.compare("e") == 0) {
                valid_input_check = false;
                if (energy_of_transition >= 0) {
                    std::cout << "Energy of transition is and photon emission is " << std::setprecision(3) << (energy_of_transition) << " eV\n";
                }
                else {
                // If energy of transition is negative, a photon needs to be absorbed and the user is informed of this
                    std::cout << "Photon of energy " << std::setprecision(3) << (-1 * energy_of_transition) << " eV needs to be absorbed for this transmission\n";
                }
            }
            // If they want output as joueles outputs photon energy in this form to user
            if (eV_or_joules.compare("j") == 0) {
                valid_input_check = false;
                if (energy_of_transition >= 0) {
                    std::cout << "Energy of transition and photon emission is " << std::setprecision(3) << (unit_charge * energy_of_transition) << " Joules\n";
                }
                else {
                    std::cout << "Photon of energy " << std:: setprecision(3)<<((unit_charge * energy_of_transition) * -1)<< " eV needs to be absorbed for this transmission\n";
                }
            }
            //Clears input to question to get a new input if the input was of the wrong form
            if(eV_or_joules.compare("j") != 0 && eV_or_joules.compare("e") != 0) {
                std::cout << "\nInput must be j for joules and m for MeV\n";
                std::cin.clear();
                std::cin.ignore(123, '\n');
            }
        }
        //Loop to ask the user whether they want to do another calculation until they give a valid answer to the question
        while (valid_input_check == false) {
            std::cout << "Would you like to do another calculation, type y for yes and n for no ";
            std::cin >> repeat;
            if (repeat.compare("y")==0 or repeat.compare("n") == 0) {
                valid_input_check = true;
            }
            //If they gave an invalid answer, the user is informed and the input is cleared so that they can give a new input 
            else {
                std::cout << "Invalid input\n";
                std::cin.clear();
                std::cin.ignore(123,'\n');
            }
        }
    }
    return 0;
}
