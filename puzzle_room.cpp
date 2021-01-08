//Include dependencies
#include "puzzle_room.h"
#include<iostream>
#include "integer_checker.h"

//Definition of member functions for a room where the user solves a puzzle

puzzle_room::puzzle_room() {}
puzzle_room::puzzle_room(int amount) {
    //Try allocate memory
    try
    {
        puzzle = new int[amount];
        size = amount;
    }
    catch (std::bad_alloc memFail)
    {
        //If memory allocation failed set the game to be over and return to main so the program ends
        std::cerr << "Memory allocation failure" << std::endl;
        game_not_over = false;
        return;
    }
}
puzzle_room::~puzzle_room() {}

//Member function to change the status of the rooms to be game over when the user characters die
bool puzzle_room::return_game_not_over() { return game_not_over; }

//Member function to generate the sequnce stored in the array that the user has to get the next of to solve the puzzle
void puzzle_room::generate_sequence() {
    //Conditionals to check randomly generated size of array to assign the fibonacci sequence to it for the user to figure out what number is next
    if (size >= 3) {
        puzzle[0] = 1;
        puzzle[1] = 1;
        for (size_t i{ 2 }; i < size; i++) {
            puzzle[i] = puzzle[i - 1] + puzzle[i - 2];
        }
    }else {
        for (size_t i{}; i < size; i++) {
            puzzle[i] = 1;
        }
    }
}

//Member function to complete all the actions required in this room for the user to progress
void puzzle_room::complete_room() {
    generate_sequence();
    std::cout << "Our heroes walk in to a room where a great door blocks their passage further up the tower. Carved in to this door is a large spiral structure. Writing on this door says: " << std::endl << std::endl
        << "                                   'Give the next for the door to open: ";

    //For loop to run through all the parts of the sequnce for the user to see it and guess the next
    for (size_t i{}; i < size; i++) { std::cout << puzzle[i] << ", "; }
    std::cout << "'";
    std::cout << std::endl << std::endl << "What number do the heroes say for the door to open?" << std::endl;
    int input = integer_checker(1000);
    //Conditioanl to check the users answer for the next in the sequnce was wrong
    if (input == (puzzle[size - 1] + puzzle[size - 2])) {
        //If the answer was correct, inform the user and progress on to the next room
        std::cout << std::endl << "The door swings open and our heroes may progress to the next room" << std::endl << std::endl;
        std::cin.ignore();
        std::cout << "Press Enter to move up the stairs to the next room:";
        std::cin.get();
        std::cout << std::endl;
    }else {
        //If the answer was incorrect, inform the user and set the status of the rooms to be game over so no more rooms will be completed in the main as a conditional checks their status before it does so
        std::cout << "The ground underneath the heroes feet begins to rumble as the door comes crashing down on top of them, crushing them beneath its immense weight. The heroes lay trapped with no way of escape." << std::endl
                  << "Door input was incorrect" << std::endl <<std::endl<< "GAME OVER!!"<<std::endl<<std::endl;
        game_not_over = false;
    }

}
