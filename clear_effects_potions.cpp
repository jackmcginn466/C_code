#include "clear_effects_potions.h"
#include<iostream>
#include "players.h"

//Definition of member functions fo clear effects potion

clear_effects_potion::clear_effects_potion() {}
clear_effects_potion::clear_effects_potion(int quantity) :number_in_inventory{ quantity } {}
clear_effects_potion::~clear_effects_potion() {}
//Completes the desired effects of the potion on the chosen player which is input by a pointer in to this member function
void clear_effects_potion::complete_effect(players* owners) {
    //Output to the user what this potion is doing, remove the one used from the inventory and complete the effect on the user
    std::cout << "Clear effect potion used to clear all active effects and heal " << heal_amount << " HP" << std::endl << std::endl;
    number_in_inventory = number_in_inventory - 1;
    owners->heal_stamina(heal_amount);
}
int clear_effects_potion::get_number_in_inventory() { return number_in_inventory; }
std::string clear_effects_potion::get_name() { return name; }