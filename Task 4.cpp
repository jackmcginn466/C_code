// Jack McGinn
// Simple use of classes for manipulating data on galaxies
//19/02/2020

//Includes
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
//Key variables of class made private to minimise errors throughout the code
private:
    std::string hubble_type{ "E0" };
    double redshift{1};
    double total_mass{10e7};
    double stellar_mass_fraction{0.01};
    std::vector<galaxy> satellites;

public:
    // Constructors
    //Default Constructor
    galaxy() = default;
    //Parameterized constructor
    galaxy(std:: string type, double red_shift, double mass, double mass_fraction):
        hubble_type{type}, redshift{red_shift}, total_mass{mass}, stellar_mass_fraction{mass}{}
    
    // Destructor
    ~galaxy(std::cout<<hubble_type<<std::endl) {}
    
    // Return stellar mass (M_* = f_* x M_tot)
    double stellar_mass() {return stellar_mass_fraction * total_mass;};
    
    // Change galaxy's Hubble type
    void change_type(const std::string &new_type)
    {
        //Only change the type of a galaxy if it is of type Irr
        if (hubble_type.compare("Irr")==0) {
            hubble_type = new_type;
            std::cout << "Hubble type of Irr was changed to " << new_type << " for this galaxy" << std::endl;
        }
        return;
    }
    
    //Prototype for function to add a satellite galaxy
    void add_satellite();

    // Prototype for function to print out an object's data
    void print_data();
};

// Print out an object's data
void galaxy::print_data(){
    // Set output  precisision to  two significant figures
    std::cout.precision(3); 
    std::cout << "Galaxy: [type ,redshift,total mass,stellar mass frcation] = [" << hubble_type << "," << redshift
        << "," << total_mass << "," << stellar_mass_fraction << "]" << std::endl;
    std::cout << "This galaxy has " << satellites.size() << " satellites" << std:: endl;
    // Conditinal to check if this galaxy had satellites so that their data can be printed out too if it did
    if (satellites.size()!=0) {
        std::cout << "These satellites have the following properties: " << std::endl;
        //For loop to iterate through each satellite of the galaxy so each one can be accessed to output
        for (auto satellite_iterator = satellites.begin(); satellite_iterator < satellites.end(); ++satellite_iterator) {
            std::cout << "Satellite: [type ,redshift,total mass,stellar mass fraction] = [" << satellite_iterator->hubble_type << "," << satellite_iterator->redshift
                << "," << satellite_iterator->total_mass << "," << satellite_iterator->stellar_mass_fraction << "]" << std::endl;
        }
    }
    return;
}

//Memeber function for the user to add a specified number of satellites to a galaxy and input their details
void galaxy::add_satellite()
{
    int number_of_satellites;
    double satellite_mass, satellite_redshift, satellite_mass_fraction;
    std::string satellite_type;
    //Take input of how many satellites this galaxy has so code knows when to keep asking for more inputs of satellite data
    std::cout << "How many satelites does this galaxy have? " << std::endl;
    std::cin >> number_of_satellites;
    //For loop so code can take information for the amount of satellites that the user specified this galaxy had 
    for (int i{}; i < number_of_satellites; i++) {
        //Inputs for each satellite data taken
        std::cout << "Specify satellite data" << std::endl << "Input satellite type ";
        std::cin >> satellite_type;
        std::cout << "Input satellite mass ";
        std::cin >> satellite_mass;
        std::cout << "Input satellite redshift ";
        std::cin >> satellite_redshift;
        std::cout << "Input satellite mass fraction ";
        std::cin >> satellite_mass_fraction;
        //All the satelite data is the added to the vector for each galaxy that stores this 
        satellites.push_back(galaxy(satellite_type, satellite_mass, satellite_redshift, satellite_mass_fraction));
    }
    return;
}
// End of class and associated member functions

// Main program
int main()
{
    // Counter keeps track of which galaxy the program is on in the galaxy data list so that this useful information can be given to the user
    int counter{1};
    std::vector<galaxy> galaxy_data;
    // Example using default constructor
    galaxy galaxy_one;
    galaxy_data.push_back(galaxy_one);
    // Example using parameterised constructor
    galaxy_data.push_back(galaxy("Sa",5,10e10,0.03)); //galaxy 2 entry
    galaxy_data.push_back(galaxy("Irr", 4, 3e9,0.02)); //galaxy 3 entry

    //Output useful information to user about what is currently stored in the code
    std::cout << "For each galaxy in the list of galaxies specify how many satellites each has and their properties" << std::endl;
    std::cout << "There is currently  " << galaxy_data.size() << " galaxies in the galaxy data list" << std::endl;
    
    // For loop so that satellite galaxies can be added by the user to each galaxy in the galaxy data list
    for (auto galaxy_iterator = galaxy_data.begin(); galaxy_iterator < galaxy_data.end(); ++galaxy_iterator) {
        std::cout << "For galaxy " << counter << std::endl;
        galaxy_iterator->add_satellite();
        counter++;
    }
    counter = 1;
    // print out data,  get and print out stellar mass
    for (auto galaxy_iterator = galaxy_data.begin();galaxy_iterator < galaxy_data.end();++galaxy_iterator) {
        std::cout << "For galaxy " << counter << ":" << std::endl;
        std::cout << "Stellar mass is " << galaxy_iterator->stellar_mass() << std::endl;
        // Change Hubble type from Irr to S0, so only if the type was originally Irr
        galaxy_iterator->change_type( "S0" );
        galaxy_iterator->print_data();
        counter++;
    }
    return 0;
}
