#pragma once
#ifndef mage_HEADER
#define mage_HEADER

//include dependencies
#include"players.h"
//forward declare dependencies
class inventory;

//Derived class of players, type of player the user can control - a mage
class mage :public players
{
protected:
    //Key member data for the player
    double health{ 250 };
    double attack{ 40 };
    double stamina{ 300 };
    std::string name{ "MAGE" };
    double resist{ 1 }; //How much a character resits damage
    bool not_stunned{ true };
    std::vector<std::pair<std::string, int>> effects_list{};//The string is the name of the effect and the int is how many turns it effects the user in combat for
    //Bag is a pointer to the users currenty inventory. It's a pointer so that all the players the users control have access to the same inventory
    inventory* bag{ nullptr };
public:
    mage();
    mage(inventory*);
    ~mage();

    //Member function outputs all the possible moves for this character and their required input during its turn in combat
    void choice_output();
    //Member function changes the status of the character as to whether they are stunned or not
    void set_stun(bool);
    //Member function that completes the turn of this character based on user inputs, during its turn of combat
    void fight_choice(const std::vector<std::shared_ptr<monsters>>*, const std::vector<std::shared_ptr<players>>*);
    //Member function for lower users health and outputing how much it has been lowered
    void damage(double);
    //Member function to clear all the effects currently inflicting the user, needed for the potion and at the end of every combat to reset
    void clear_active_effects();
    //Member function to add effects to the effect list
    void add_effects(std::pair<std::string, int>);
    //Member function to handle all the current active effects on the user and complete what they do
    void  effects();
    //Public accessors to member data members of class 
    double get_health();
    double get_stamina();
    std::vector<std::pair<std::string, int>> show_effects();
    std::string get_name();

    //Member functions to increase the health or stamina of the user when they are healed under different potions in the inventory
    void heal(double);
    void heal_stamina(double);
};

#endif





