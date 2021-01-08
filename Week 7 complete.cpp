//Jack McGinn
//Assignment 7
//20/03/2020

//Code doesn't check user inputs so may give errors if in the wrong form, velocities sare always input as fractions of the speed of light (less then one)
// Vectors should always be input like (for example length 3 vector) 1,1,1


#include<iostream>
#include<ostream>
#include<sstream>
#include<cmath>

class general_vector
{
    //Friend functions for inputs and outputs
    friend std::ostream& operator<<(std::ostream& output, general_vector&); //friend function for inserting vectors in to an ostream
    friend void operator>>(std::istream& input, general_vector& vec);
protected:
    size_t size{};
    double* array{ nullptr };
public:
    general_vector() {} //default 
    general_vector(size_t s); // parametrised
    general_vector(general_vector&); // copy
    general_vector(general_vector&&); //move
    ~general_vector() {} //destructor
    general_vector& operator=(general_vector&); //copy assignment
    general_vector& operator=(general_vector&&); //move assignment

    size_t length() const { return size; } //Mmeber function to return the size of the vector

    double& operator[](size_t i); //Prototype for to return parts of the vector

    //Member function to calculate the dot product of to general vectors of the same length
    double dot_product(general_vector& vec)const
    {
        double sum{};
        //Conditional to check the vectors are of the same length
        if (length() == vec.length()) {
            //For loop to run through the components of the vectors to multiply and sum them all together for the dot product
            for (size_t i{}; i < size; i++) {
                sum += array[i] * vec[i];
            }
        }
        else {
            std::cout << "Vectors of wrong dimensions to calculate dot product" << std::endl;
        }
        return sum;
    }
};

//Define four vector class which is a specialistaion class of the general vector class
class four_vector : public general_vector
{
public:
    //Derived constructors use base constructors to make these arrays and general vectors of length four first
    four_vector() :
        general_vector{ 4 } {} //default constructor

    four_vector(const double t, const double x, const double y, const double z); //parametrized constructor
    four_vector(const double t, general_vector vec); // paramterized constructor

    ~four_vector() {} //destructor

    //Member function to get the dot product of two 4 vectors in minkowski space, overidden version of the general vector function
    double dot_product(four_vector& vec)const
    {
        double sum{};
        //Checks they are both 4 vectors first
        if (size == vec.length()) {
            //Calculation for dot product stored in sum and returned at the end of the function
            sum = array[0] * vec[0];
            for (size_t i{ 1 }; i < size; i++) {
                sum = sum - array[i] * vec[i];
            }
        }
        else {
            std::cout << "Vectors of wrong dimensions to calculate dot product" << std::endl;
        }
        return sum;
    }

    //Member function to calculate lorentz boosted four vector for a given velocity, where the components for the input velocity is express as ratios to the speed of light
    four_vector lorentz_boost(general_vector velocity)const
    {
        four_vector boosted; // four vector to store the boosted version
        //Seperate out position data from the four vector as they are lorentz boosted in a different way to time
        general_vector position(3);
        for (size_t i{}; i < 3; i++) { position[i] = array[i + 1]; }
        //Check input velocity vector is actually a velocity
        if (velocity.length() == 3) {
            //Calculate boosted time component and add it to the boosted data, and the key factors to get the new position components
            double velocity_magnitude_squared = (velocity[0] * velocity[0]) + (velocity[1] * velocity[1]) + (velocity[2] * velocity[2]);
            double gamma_factor = 1.0 / sqrt(1.0 - velocity_magnitude_squared);
            double velocity_dot_position = velocity.dot_product(position);
            double position_calculation_factor = ((gamma_factor - 1.0) * velocity_dot_position * (1.0 / velocity_magnitude_squared) - gamma_factor * array[0]);
            boosted[0] = gamma_factor * (array[0] - velocity_dot_position);
            //For loop to run through position components to calculate the boosted version
            for (size_t i{}; i < 3; i++) {
                boosted[i + 1] = position[i] + position_calculation_factor * velocity[i];
            }
        }
        else {
            std::cout << "Velocity needs to be a 3 vector";
        }
        std::cout << boosted << std::endl;
        return boosted;
    }
};

class particle
{
private:
    general_vector velocity{ 3 }; //Each component of velocity is expressed as a fraction of the speed of light e.g 0.4,0.0.1, so when inputing make sure all components are less then one 
    four_vector particle_four_vector;
    double mass{ 0 };
public:
    particle() {} //default constructor
    particle(const double m, general_vector v, four_vector p) :
        mass{ m }, velocity{ v }, particle_four_vector{ p } {} //parameterized constructor
    ~particle() {} //destructor

    //Member function to calculate particle gamma factor
    const double speed_of_light = 3 * pow(10, 8);
    const double electron_volt = 1.6 * pow(10, -19);
    const double mega = pow(10, 6);
    double gamma() { return sqrt(1 / (1 - (velocity[0] * velocity[0]) + (velocity[1] * velocity[1]) + (velocity[2] * velocity[2]))); }

    //Member function to calculate particle energy
    double energy() { return (gamma() * mass * speed_of_light * speed_of_light) / (electron_volt * mega); }

    //Member function to calculate the magnitude of the momentum of the particle
    double momentum() { return (gamma() * mass * sqrt((velocity[0] * velocity[0]) + (velocity[1] * velocity[1]) + (velocity[2] * velocity[2]))) / (electron_volt * mega); }
};

// Copy constructor for deep copying
general_vector::general_vector(general_vector& arr)
{
    // Copy size and declare new array
    array = nullptr; size = arr.length();
    if (size > 0) {
        array = new double[size];
        // Copy values into new array
        for (size_t i{}; i < size; i++) array[i] = arr[i];
    }
}

// Move constructor
general_vector::general_vector(general_vector&& arr)
{ // steal the data
    size = arr.size;
    array = arr.array;
    arr.size = 0;
    arr.array = nullptr;
}

// Assignment operator for deep copying
general_vector& general_vector::operator=(general_vector& arr)
{
    if (&arr == this) return *this; // no self assignment
    // First delete this object's array
    delete[] array; array = nullptr; size = 0;
    // Now copy size and declare new array
    size = arr.length();
    if (size > 0) {
        array = new double[size];
        // Copy values into new array
        for (size_t i{}; i < size; i++) { array[i] = arr[i]; }
    }
    return *this;
}

// Move assignment operator
general_vector& general_vector::operator=(general_vector&& arr)
{
    std::swap(size, arr.size);
    std::swap(array, arr.array);
    return *this;
}

// Parameterized constructor implementation for vectors
general_vector::general_vector(size_t length)
{
    if (length < 1)
    {
        std::cout << "Error: trying to declare an array with size < 1" << std::endl;
        throw("size not positive");
    }
    size = length;
    array = new double[size];
    //For the parameterized constructor, each component for the given size of the vector is given the value 0
    for (size_t i{}; i < size; i++) { array[i] = 0; }
}

// Overloaded element [] operator implementation to index the array for a vector or four vector class storing the data. Appropriate accesor function to access parts of the vectors
//As four vector is a derived class from general vector, this specifier is appropriate and works for both of them
double& general_vector::operator[](size_t i)
{
    //Check element accessing is not outside the range of the vector
    if (i < 0 || i >= size)
    {
        std::cout << "Error: trying to access array element out of bounds" << std::endl;
        throw("Out of Bounds error");
    }
    return array[i];
}

//Overload << operator for the output of vectors so that it looks better
std::ostream& operator<<(std::ostream& output, general_vector& vec)
{
    //Outputs the vector in a bracket with commas between each component
    if (vec.length() > 0) {
        output << "(" << vec[0];
        for (size_t i{ 1 }; i < vec.length(); i++) {
            //std::cout << "dog";
            output << "," << vec[i];
        }
        output << ")";
    }
    else {
        output << "()";
    }
    return output;
}

//Parameterized constructor for four vector with each component input seperately (ct,x,y,z)
four_vector::four_vector(double t, double x, double y, double z)
{
    size = 4;
    array = new double[size];
    array[0] = t; array[1] = x; array[2] = y; array[3] = z;
}

//Paramterized constructor for four vector with time and vector position inputs (ct,r)
four_vector::four_vector(double t, general_vector vec)
{
    //Check the vector position is of length 3 which is what is needed for a four vector to be made
    if (vec.length() != 3)
    {
        std::cout << "Error: trying to declare a 4 vector with not 4 length" << std::endl;
        throw("4 vector length not 4");
    }
    size = 4;
    array = new double[size];
    array[0] = t;
    //For loop runs through components of four vector to match them with the correct components of the input vector
    for (size_t i{ 1 }; i < size; i++) array[i] = vec[i - 1];
}

void operator>>(std::istream& input, general_vector& vec)
{
    //Take input as comma seperated entries
    std::string input_row;
    int position_initial_comma{};
    int position_next_comma{};
    //Takes in the user input
    std::getline(std::cin, input_row);
    //For loop to run index through the vector
    for (size_t j{}; j < vec.length(); j++) {
        position_next_comma = input_row.find(",", position_initial_comma + 1);
        //Take each entry between the commas of the user input as the entry to the vector and run it through the vector moving the commas which the code is looking between along
        vec.array[j] = stod(input_row.substr(position_initial_comma, (position_next_comma - position_initial_comma)));
        position_initial_comma = position_next_comma + 1;
    }
    return;
}

int main()
{
    // First part of assignment: constructing and deep copying vectors
    std::cout << "The first half of the code demonstrates the use of the move and copy constructors on general vectors, taking user inputs for some. The second half of the code then demonstrates the uses of the four vector and particle classes." << std::endl << std::endl;

    // Demonstrate default constructor
    std::cout << "Default constructor used to set value of vector_one. " << std::endl;
    general_vector vector_one;
    std::cout << "Output vector_one:  " << vector_one << std::endl;

    //Demonstrate parameterised constructor
    size_t vector_length{ 3 };//SET LENGTH OF VECTORS FOR THE FIRST HALF OF THE CODE HERE
    std::cout << "Vector length for the general vectors is set to " << vector_length << ". This can be changed in the code." << std::endl;
    std::cout << std::endl << "Parameterised constructor used to set value of vector_two" << std::endl;
    general_vector vector_two{ vector_length };

    // User inputs values for vector_two here
    std::cout << "To input a vector, type a comma (,) after each element and press enter at the end of the vector" << std::endl;
    std::cout << "Input vector_two: ";
    std::cin >> vector_two;
    std::cout << "Output vector_two: " << vector_two << std::endl;

    // Demonstrate deep copying by assignment
    std::cout << "Parameterised constructor used to initialise vector_three" << std::endl;
    general_vector vector_three{ vector_length };
    std::cout << "Output vector_three: " << vector_three << std::endl;
    std::cout << "Vector_three deep copy assigned to be same as vector_two." << std::endl;
    vector_three = vector_two;
    std::cout << "Output vector_three again: " << vector_three << std::endl;

    // Demonstrate deep copy using copy constructor 
    std::cout << "Vector_four copy constructed to be same as vector_two." << std::endl;
    general_vector vector_four{ vector_two };
    std::cout << "Output vector_four: " << vector_four << std::endl;

    //Demonstrate move copy construction 
    std::cout << "A new vector vector_five is made from a move copy construction of vector_two " << std::endl;
    general_vector vector_five{ std::move(vector_two) };
    std::cout << "Output vector_five" << vector_five << std::endl;

    //Take an input for another vector so the dot product between the two input vectors can eventually be calculated
    general_vector vector_six(vector_length);
    std::cout << "Input another vector, the same length as vector_two." << std::endl << "Input vector: ";
    std::cin >> vector_six;

    //Demonstrate move assignment 
    std::cout << "Vector_five is now move assigned to equal this input vector " << std::endl;
    vector_five = std::move(vector_six);
    std::cout << "Output vector_five: " << vector_five << std::endl;

    //Demonstrate the dot product functionality for two general vectors
    std::cout << "The dot product of the two input vectors is: " << vector_three.dot_product(vector_six) << std::endl;

    //Demonstrate default constructor for 4 vectors
    std::cout << std::endl << "Now the code moves on to four vectors." << std::endl << "Default constructor used to make four_vector_one" << std::endl;
    four_vector four_vector_one;

    //Demonstrate parameterized constructor with 4 inputs for 4 vectors
    std::cout << "This four vector has value: " << four_vector_one << std::endl << "Parametrised constructor used to make four_vector_two (from each component of the 4 vector being input in the code) " << std::endl;
    four_vector four_vector_two{ 1,2,3,4 };
    std::cout << "This four vector has value: " << four_vector_two << std::endl;

    std::cout << "Now consider a proton at a given time of 5/c seconds in some stationary frame of reference (called S). A parameterised constructor is made to store the particles (length 3) vector caretesian position in frame S" << std::endl;
    general_vector position{ 3 };
    std::cout << "Input the cartesian position vector of the particle at this given time in S: ";
    std::cin >> position;

    //Demonstrate parametised constructor with a time input and a position vector input
    std::cout << "A parameterised constructor is then used to make the 4 position of this particle (from the time 5/c seconds and the user input position vector)." << std::endl;
    four_vector particle_four_vector(5, position);

    //Demonstrate the dot product functionality for four vectors in minkowski space
    std::cout << "The dot product in minkowski space between the particles four vector and the variable four_vector_two is: " << particle_four_vector.dot_product(four_vector_two) << std::endl;

    std::cout << "Parameterised constructor used to make velocity vector for frame S' relative to frame S." << std::endl;
    general_vector frame_velocity(3);
    std::cout << "Input the vector velocity of frame S' relative to S, where each component should be wrote as a fraction of the speed of light (so should all be less then one)" << std::endl << "Frame velocity: ";
    std::cin >> frame_velocity;

    //Demonstrate lorentz boost functionality for 4 vectors
    std::cout << std::endl << "The lorentz boosted 4 vector of the particle in the frame S' is then: ";
    particle_four_vector.lorentz_boost(frame_velocity);

    std::cout << "Parameterised constructor used to store particle velocity in frame S" << std::endl;
    general_vector particle_velocity{ 3 };
    std::cout << "Input particle velocity in frame S,where each component should be wrote as a fraction of the speed of light (so should all be less then one) " << std::endl << "Particle velocity: ";
    std::cin >> particle_velocity;

    const double proton_mass{ 1.67 * pow(10,-27) };

    //Parametrized constructor used to make particle class
    particle proton{ proton_mass, particle_velocity, particle_four_vector };

    //Demonstrate functionality of the energy and momentum magnitude calculation for the particle class
    std::cout << "The energy of the proton is " << proton.energy() << " MeV" << " and the momentum of the particle is " << proton.momentum() << "MeV/c" << std::endl;

    return 0;
}


