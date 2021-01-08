 #pragma once
#ifndef fight_room_HEADER
#define fight_room_HEADER
#include<vector>
#include<memory>
//include dependencies
#include"rooms.h"
//forward declare dependencies
class players;
class monsters;

//Derived class for one of the rooms the users go through - fight room 
class fight_room :public rooms
{
protected:
    std::vector<std::shared_ptr<players>> players_list{}; //Polymorphic array of users characters
    std::vector<std::shared_ptr<monsters>> enemy_list{}; //Polymorphic array of enemies the user faces
public:
    fight_room();
    fight_room(std::vector<std::shared_ptr<players>>* player);
    ~fight_room();
    //Member function to change the status of the rooms to be game over when the user characters die
    bool return_game_not_over();
    //Member function to complete the users turn in combat
    void users_turn();
    //Member function to complete the enemies turn in combat
    void enemies_turn();
    //Member function to display output message of what the current status and situaiotn of the combat encounter looks like
    void output_message();
    //Member function to complete all the actions required in this room for the user to progress
    void complete_room();
};

#endif
