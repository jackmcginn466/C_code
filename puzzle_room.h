#pragma once
#ifndef puzzle_room_HEADER
#define puzzle_room_HEADER

//include dependencies
#include"rooms.h"

//Derived class for one of the rooms the users go through - a room where the user solves a puzzle
class puzzle_room : public rooms {
protected:
    int* puzzle{ nullptr };
    size_t size{};
public:
    puzzle_room();
    puzzle_room(int);
    ~puzzle_room();


    //Member function to change the status of the rooms to be game over when the user characters die
    bool return_game_not_over();
    //Member function to generate the sequnce stored in the array that the user has to get the next of to solve the puzzle
    void generate_sequence();

    //Member function to complete all the actions required in this room for the user to progress
    void complete_room();
};

#endif

