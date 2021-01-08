#pragma once
#ifndef inventory_room_HEADER
#define inventory_room_HEADER

#include<vector>

//forward declare dependencies
class inventory;
class inventory_items;
//include dependencies
#include"rooms.h"

//Derived class for one of the rooms the users go through - room where users get their inventory
class get_inventory_room : public rooms {
protected:
    inventory* current_inv{ nullptr };
    std::vector<inventory_items*> first_contents{};
    std::vector<inventory_items*>second_contents{};
public:
    get_inventory_room();
    get_inventory_room(inventory*);
    ~get_inventory_room();
    //Member function to change the status of the rooms to be game over when the user characters die
    bool return_game_not_over();
    //Member function to generate the contents of the inventorys the user meets and decides between in this room
    void generate_contents(); 
    //Member function to complete all the actions required in this room for the user to progress
    void complete_room();
};

#endif

