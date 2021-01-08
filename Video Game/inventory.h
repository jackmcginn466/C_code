#pragma once
#ifndef inventory_HEADER
#define inventory_HEADER

#include <vector>
//forward declare dependencies
class inventory_items;
class players;

//Class that stores a polymorphic vector holding the items in the users inventory and all the functions the user can do with their inventory 
class inventory
{
private:
    size_t size{};
    std::vector<inventory_items*> contents{};
public:
    inventory();
    inventory(std::vector<inventory_items*>);
    ~inventory();
    //Member function to remove items from the inventory when the number of items of its type become 0
    void sort_inventory();
    //Member function to output all the items in the inventory in a clear way to the user
    void output_inventory();
    //Member function dealing with how the users use an item from their inventory during combat. The player the inventory items are being used on is input as a pointer
    bool use_inventory(players*);
    size_t items_in_inventory();
    inventory(inventory&);
    //Move assignment operator so the code knows how to copy inventorys over, used in one of the rooms in the game
    inventory& operator=(inventory&&) noexcept;
};

#endif
