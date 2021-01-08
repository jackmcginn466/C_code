#include "health_potion.h"
#include<iostream>
#include "players.h"

//Definition of member functions for a health potion

health_potion::health_potion() {}
health_potion::health_potion(int quantity) :number_in_inventory{ quantity } {}
health_potion::~health_potion() {}
//Completes the desired effects of the potion on the chosen player which is input by a pointer in to this member function
void health_potion::complete_effect(players* owners) {
    //Output to the user what this potion is doing, remove the one used from the inventory and complete the effect on the user
    std::cout << "Health potion used to heal " << " " << heal_amount << " HP" << std::endl << std::endl;
    number_in_inventory = number_in_inventory - 1;
    owners->heal(heal_amount);
}
int health_potion::get_number_in_inventory() { return number_in_inventory; }
std::string health_potion::get_name() { return name; }
