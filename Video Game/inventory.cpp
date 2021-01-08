#include "inventory.h"
#include "integer_checker.h"
#include"inventory_items.h"
#include<algorithm>
#include<iostream>

//Definition of member functions for the inventory class

inventory::inventory() {}
inventory::inventory(std::vector<inventory_items*> items) {
    size = items.size();
    contents = items;
}
inventory::~inventory() {};

//Member function to remove items from the inventory when the number of items of its type become 0
void inventory::sort_inventory() {
    //Lambda function runs through all items in the vector and if they meet the condition that there is 0 items of this type, then they are removed from the vector
    contents.erase(std::remove_if(contents.begin(), contents.end(), [](auto const& it) {return it->get_number_in_inventory() == 0; }), contents.end());
    //Readjust inventory size to be the new size of the vector
    size = contents.size();
}

//Member function to output all the items in the inventory in a clear way to the user
void inventory::output_inventory() {
    //For loop runs through the inventory vector to output all the items in it
    for (size_t i{}; i < size; i++) {
        std::cout << "(" << i + 1 << ".) " << contents[i]->get_name() << " * " << contents[i]->get_number_in_inventory() << "  ";
    }
    std::cout << std::endl;
}

//Member function dealing with how the users use an item from their inventory during combat. The player the inventory items are being used on is input as a pointer
bool inventory::use_inventory(players* owners) {
    //Returns a boolean that true if the user didnt use an item from their inventory and instead decided to go back, so the code knows to take another input from the user until they have made a move in combat
    bool potion_not_used{ true };
    std::cout << "Choose which inventory item to use in the inventory from the number labeling them, or press " << size + 1 << " to go back" << std::endl;
    output_inventory();
    //Checks user input is valid
    int choice = integer_checker(static_cast<int>(size + 1));
    //Conditional checks the user didnt press to go back, then completes the effects of the potion they selected on their user
    if (choice != size + 1) {
        potion_not_used = false;
        contents[choice - 1]->complete_effect(owners);
    }
    //Removes any items from the vector if their quantity is 0
    sort_inventory();
    return potion_not_used;
}
size_t inventory::items_in_inventory() { return size; }

inventory::inventory(inventory& inv) {}
//Move assignment operator so the code knows how to copy inventorys over, used in one of the rooms in the game
inventory& inventory::operator=(inventory&& inv) noexcept
{
    std::swap(size, inv.size);
    std::swap(contents, inv.contents);
    return *this;
}

