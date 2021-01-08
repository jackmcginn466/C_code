#include "get_inventory_room.h"
#include<iostream>
#include"inventory.h"
#include"stamina_potions.h"
#include"clear_effects_potions.h"
#include"health_potion.h"
#include"integer_checker.h"

//Definition of member functions for the room where the user gets their inventory

get_inventory_room::get_inventory_room() {}
get_inventory_room::get_inventory_room(inventory* inv) {
    //Try assign memory
    try
    {
        current_inv = inv;
    }
    catch (std::bad_alloc memFail)
    {
        //If memory allocation failed set the game to be over and return to main so the program ends
        std::cerr << "Memory allocation failure" << std::endl;
        game_not_over = false;
        return;
    }
}
get_inventory_room::~get_inventory_room() {
    //Destructors delete all pointers in the vectors then clear the vector
    for (auto first_contents_it = first_contents.begin(); first_contents_it < first_contents.end(); ++first_contents_it) {
        delete* first_contents_it;
    }
    first_contents.clear();
    for (auto second_contents_it = second_contents.begin(); second_contents_it < second_contents.end(); ++second_contents_it) {
        delete* second_contents_it;
    }
    first_contents.clear();
}

//Member function to change the status of the rooms to be game over when the user characters die
bool get_inventory_room::return_game_not_over() { return game_not_over; }
//Member function to generate the contents of the inventorys the user meets and decides between in this room
void get_inventory_room::generate_contents() {
    //The numbers are the amount of this type of potion that are placed in the inventory
    first_contents.push_back(new health_potion{ 3 });
    first_contents.push_back(new stamina_potion{ 3 });
    second_contents.push_back(new health_potion{ 2 });
    second_contents.push_back(new stamina_potion{ 2 });
    second_contents.push_back(new clear_effects_potion{ 2 });

}

//Member function to complete all the actions required in this room for the user to progress
void get_inventory_room::complete_room()
{
    std::cout << std::endl << "The heroes move in to the next room of the tower and discover the corpses of two previous travellers also seeking the treasure this building holds." << std::endl
                           << "The mage notices that each corpse has a stash of potions with them that could be crucial in helping our heroes reach the final treasure. However," << std::endl
                           << "they only have the capacity to take and carry one set of these potions. Which should they take?" << std::endl << std::endl;
    std::cout << "Press Enter to enter to see what the sets of potions are:";
    std::cin.get();
    std::cout << std::endl;

    generate_contents();
    //Construct inventories user decides between in this room
    inventory first_inventory{ first_contents };
    inventory second_inventory{ second_contents };

    //Ouput inventories so user knows which they are choosing between
    std::cout << "The set of potions on the first corpse contains:";
    first_inventory.output_inventory();
    std::cout << std::endl;
    std::cout << "The set of potions on the second corpse contains:";
    second_inventory.output_inventory();
    //Take user input of which inventory they would like to use
    std::cout << std::endl << "Press 1 to take the first set of potions, or press 2 for them to take the second set" << std::endl << std::endl;
    int potion_choice = integer_checker(2);
    //Conditionals to check which inventory the user selected to take, then move assign it to be equal to the one the users have access to
    if (potion_choice == 1) {
        *current_inv = std::move(first_inventory);
    }else {
        *current_inv = std::move(second_inventory);
    }

    std::cout << std::endl << "With their new set of potions, the heroes head further up the tower ready for whatever dangers they may face." << std::endl << std::endl;
    std::cin.ignore();
    std::cout << "Press Enter to move up the stairs to the next room:";
    std::cin.get();
    std::cout << std::endl;
}