#pragma once
#ifndef spider_HEADER
#define spider_HEADER

//include dependencies
#include"monsters.h"

//Derived class of monsters, type of enemy the user meets - a giant spider
class spider :public monsters
{
protected:
    double health{ 125 };
    double attack{ 55 };
    std::string name{ "GIANT SPIDER" };
    double resist{ 1 };
    bool not_stunned{ true };
    std::vector<std::pair<std::string, int>> effects_list{}; //The string is the name of the effect and the int is how many turns it effects the user in combat for
public:
    spider();
    ~spider();

    //Member function to complete monsters move during combat
    void fight(const std::vector<std::shared_ptr<players>>*);
    ////Member function for lower users health and outputing how much it has been lowered
    void damage(double);
    //Member function changes the status of the character as to whether they are stunned or not
    void set_stun(bool);

    //Member function to add effects to the effect list
    void add_effects(std::pair<std::string, int>);
    //Member function to handle all the current active effects on the user and complete what they do
    void  effects();

    //Public accessors to member data members of class 
    double get_health();
    std::string get_name();
    std::vector<std::pair<std::string, int>> show_effects();
};

#endif


