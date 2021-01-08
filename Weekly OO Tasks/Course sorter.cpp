// Code that takes user inputs for courses and sorts them either numerically or alphabeticly
// Jack McGinn
//14/02/2020

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

// Function that is used to sort the course names alphabeticly
bool sort_by_second_element_alphabetically(std::pair<int, std::string>& first_pair, std::pair<int, std::string>& second_pair) {
    return first_pair.second < second_pair.second;

}

//Function that makes sure any user input to a question is the right type of answer
std::string take_and_validate_input(std:: string output_message, std::string  first_correct_input, std::string second_correct_input, std:: string third_correct_input, std:: string fourth_correct_input) {
    std::string user_input;
    bool input_check = true;
    //While loop to keep taking the user input until it is a corrrect answer to the question in the output_message
    while (input_check) {
        std::cout << output_message;
        std::cin >> user_input;
        //Conditional to check that the user input was a valid answer to the question, where the valid answers are input in to the function when it is called
        if (user_input.compare(first_correct_input) == 0 or user_input.compare(second_correct_input) == 0 or user_input.compare(third_correct_input) == 0 or user_input.compare(fourth_correct_input) == 0) {
            input_check = false;
        }
        //If they gave an invalid answer, the user is informed and the input is cleared so that they can give a new input 
        else {
            std::cout << "Invalid input\n";
            std::cin.clear();
            std::cin.ignore(123, '\n');
        }
    }
    //Clear all inputs for later user inputs
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return user_input;
}

int main() {
    const std::string degreeCode("PHYS");
    //This vector stores all the courses the user inputs as a pair where each pair holds the course code and course title
    std::vector <std::pair <int, std::string>> courses;
    std::string course_code;
    std::string course_title;
    int course_code_integer;
    std::string not_finished("y");

    //While loop to keep taking user inputs for courses until they are done
    while (not_finished.compare("y") == 0) {
        std::cout << "Please enter a course code and title: ";
        std::cin >> course_code;
        std::getline(std::cin, course_title);
        // While loop to keep taking user inputs for course code and title until the course code is of valid form
        while (course_code.find_first_not_of("0123456789") != std::string::npos or course_code.length() != 5) {
            std::cout << "\nInput invalid for course code. Please enter a course code and title: ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> course_code;
            //Getline is used for course title as the title may be multiple words so have spaces
            std::getline(std::cin, course_title);
        }
        course_code_integer = stoi(course_code);
        
        //Combine the matching course code and title in a pair then append this on to the vector for all courses
        std::pair <int, std::string> course_information(course_code_integer, course_title);
        courses.push_back(course_information);

        not_finished = take_and_validate_input("Would you like to inupt more courses? y for yes and n for no ", "y", "n", "y", "n");
    }

    std::string sort_option = take_and_validate_input("Sort by code or name ( c for code and n for name): ", "c", "n", "c", "n");
    
    //Conditionals to check which way the user wanted their courses to be sorted so it can sort it differently for name or code
    if (sort_option == "c") {
        sort(courses.begin(), courses.end());
    }
    else {
        sort(courses.begin(), courses.end(), sort_by_second_element_alphabetically);
    }

    //Create the iterator to run through the vector courses so each entry can be outputed
    std::cout << "List of courses: " << std::endl;
    std::vector <std::pair<int, std::string> >::iterator vector_begin{courses.begin()};
    std::vector <std::pair<int, std::string>  >::iterator vector_end{courses.end()};
    std::vector <std::pair<int, std::string>  >::iterator vector_iterator;
    
    std::stringstream output_string;

    //For loop runs the iterator through each entry in the now sorted vector so each entry can be output back to the user in the sorted order
    for (vector_iterator = vector_begin; vector_iterator < vector_end; ++vector_iterator) {
        output_string << degreeCode << (*vector_iterator).first << "  " << (*vector_iterator).second << std::endl;
        std::cout << output_string.str();
        output_string.str("");
    }

    std::string year_choice = take_and_validate_input("Please enter year: (1,2,3 or 4) ", "1","2","3","4");

    // This for loop works in the same way as the previous one to run through the vector so each entry may be output
    for (vector_iterator = vector_begin; vector_iterator < vector_end; ++vector_iterator) {
        // Conditional checks whether each entry is from the year the user specified, so only these ones get output
        if (((*vector_iterator).first) / 10000 == stoi(year_choice)) {
            output_string << degreeCode << (*vector_iterator).first << "  " << (*vector_iterator).second << std::endl;
            std::cout << output_string.str();
            output_string.str("");
        }
    }

    return 0;
}
