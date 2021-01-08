#include "stamina_potions.h"
#include<iostream>
#include "players.h"

//Definition of member functions for a stamina potion class

stamina_potion::stamina_potion() {}
stamina_potion::stamina_potion(int quantity) :number_in_inventory{ quantity } {}
stamina_potion::~stamina_potion() {}

//Completes the desired effects of the potion on the chosen player which is input by a pointer in to this member function
void stamina_potion::complete_effect(players* owners) {
    //Output to the user what this potion is doing, remove the one used from the inventory and complete the effect on the user
    std::cout << "Stamina potion used to recover " << " " << heal_amount << " ST" << std::endl << std::endl;
    number_in_inventory = number_in_inventory - 1;
    owners->heal_stamina(heal_amount);
}

int stamina_potion::get_number_in_inventory() { return number_in_inventory; }
std::string stamina_potion::get_name() { return name; }
