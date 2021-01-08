// PHYS 30762 Programming in C++, Assignment 5
// Jack McGinn
// 28/02/2020

#include<iostream>
#include<cmath>
#include<ostream>
#include<string>
#include<iomanip>

// Class for complex numbers
class complex
{
private:
    double real{};
    double imaginary{};
public:
    // Default constructor
    complex() = default;
    // Paraneterised constructor
    complex(double real_part, double imaginary_part) : real{ real_part }, imaginary{ imaginary_part }{};
    // Destructor
    ~complex() {}
    // Member functions
    // Return real component
    double get_real() const { return real; }

    // Return imaginary component
    double get_imaginary() const { return imaginary; }

    // Return modulus
    double modulus() const { return(sqrt(real * real + imaginary * imaginary)); }

    // Return argument
    double argument() const { return(atan(imaginary / real)); }

    // Return complex conjugate
    complex complex_conjugate() const
    {
        complex conjugate{ real, imaginary * -1 };
        return conjugate;
    }

    // Set real and complex parts of complex number
    void set_real(const double real_input) { real = real_input; }
    void set_imaginary(const double imaginary_input) { imaginary = imaginary_input; }

    // Overload + operator for addition of complex numbers 
    complex operator+(const complex complex_number) const
    {
        complex addition{ real + complex_number.real ,imaginary + complex_number.imaginary };
        return addition;
    }

    // Overload - operator for subtraction of complex numbers
    complex operator-(const complex complex_number) const
    {
        complex subtraction{ real - complex_number.real ,imaginary - complex_number.imaginary };
        return subtraction;
    }

    // Overload * operator for multiplication of complex numbers, z1*z2
    complex operator*(const complex complex_number) const
    {
        complex multiplication{ (real * complex_number.real) - (imaginary * complex_number.imaginary) ,(real * complex_number.imaginary) + (imaginary * complex_number.real) };
        return multiplication;
    }

    // Overload / operator for division of complex numbers, z1/z2
    complex operator/(const complex complex_number) const
    {
        double denominator{ complex_number.real * complex_number.real + complex_number.imaginary * complex_number.imaginary };
        complex division{ ((real * complex_number.real) + (imaginary * complex_number.imaginary)) / denominator,((imaginary * complex_number.real) - (real * complex_number.imaginary)) / denominator };
        return division;
    }

    // Define non-member friend functions that deal with inputs and outputs of complex numbers
    friend std::ostream& operator<<(std::ostream& output, const complex& complex_number);
    friend void operator>>(std::istream& input, complex& complex_number);
};

// Function to overload << operator for complex numbers so that they can be output to the user
std::ostream& operator<<(std::ostream& output, const complex& complex_number)
{
    // Conditional to check sign of imaginary component to know whether to output a plus or a minus to the user
    if (complex_number.imaginary < 0) {
        output << complex_number.real << "-" << -1 * complex_number.imaginary << "i";
    }
    else {
        output << complex_number.real << "+" << complex_number.imaginary << "i";
    }
    return output;
}

// Function to overload the input operator so that the user can input a complex number and it can be saved in the complex class form
void operator>>(std::istream& input, complex& complex_number)
{
    // Take input as string
    std::string complex_string;
    input >> complex_string;
    // Find positions of operator and i so real and imaginary parts of input can be selected out and saved to the class
    int operator_position = complex_string.find("+", 0) or complex_string.find("-", 0);
    int imaginary_position = complex_string.find("i", operator_position);
    complex_number.set_real(std::stod(complex_string.substr(0, operator_position)));
    complex_number.set_imaginary(std::stod(complex_string.substr(operator_position, imaginary_position - operator_position)));
    return;
}

// Function to output all the useful information about a complex number to the user
void output_data(const complex complex_number)
{
    // Output message with each output to say what it is to the user
    std::cout << "Real: " << complex_number.get_real() << std::endl;
    std::cout << "Imaginary: " << complex_number.get_imaginary() << std::endl;
    std::cout << "Modulus: " << complex_number.modulus() << std::endl;
    std::cout << "Argument: " << complex_number.argument() << " radians" << std::endl;
    std::cout << "Conjugate: " << complex_number.complex_conjugate() << std::endl;
    return;
}

int main()
{
    // Define complex variables to save the user inputs
    complex first_complex_number;
    complex second_complex_number;

    // Set precision of outputs
    std::cout.precision(3);

    // Get the user to input two complex numbers and save them to the two variables just defined. Output messages to tell the user what they are doing
    std::cout << "Input complex number in form a+bi (no spaces) ." << std::endl;
    std::cout << "Input first complex number: ";
    std::cin >> first_complex_number;
    std::cout << "Input second complex number: ";
    std::cin >> second_complex_number;

    // Get real and imaginary components, modulus and argument of each complex number
    std::cout << std::endl << "For the first complex number: " << std::endl;
    output_data(first_complex_number);
    std::cout << "For the second complex number: " << std::endl;
    output_data(second_complex_number);

    // Get sum, difference, product and quotient of the two complex numbers
    std::cout << std::endl << "Sum of complex numbers: " << first_complex_number + second_complex_number << std::endl;
    std::cout << "Subtraction of complex numbers: " << first_complex_number - second_complex_number << std::endl;
    std::cout << "Multiplication of complex numbers: " << first_complex_number * second_complex_number << std::endl;
    std::cout << "Division of complex numbers: " << first_complex_number / second_complex_number << std::endl;

    return 0;
}

