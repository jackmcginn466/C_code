#include "integer_checker.h"
#include<iostream>

//Definition of integer checker function

int integer_checker(int range)
{
    int number;
    std::cout << "Input: ";
    std::cin >> number;
    //If the input fails the condition the input is cleared and the loop continues, otherwise the loop breaks.
    while (std::cin.fail() or std::cin.eof() or number > range or number < 1) {
        std::cout << "\nInput invalid. Input a number in range 1 to " << range << " : ";
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cin >> number;
    }
    return number;
}
