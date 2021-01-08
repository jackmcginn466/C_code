#include "knight.h"
#include"integer_checker.h"
#include"monsters.h"
#include"inventory.h"
#include<algorithm>

//Definition of member functions for the knight class

knight::knight() {}
knight::knight(inventory* inv) :bag{ inv } {}
knight::~knight() {}

//Member function outputs all the possible moves for this character and their required input during its turn in combat
void knight::choice_output()
{
    std::cout << std::endl << name << " turn, Press the following numbers to: " << std::endl << std::endl
        << "    (1.) Base Attack                         (2.) Slash " << std::endl
        << "         " << attack << " damage                     " << (attack * 2) / 3 << " damage to all enemies" << std::endl
        << "     Costs 30 stamina                       Costs 50 stamina  " << std::endl << std::endl
        << "    (3.) Defensive stance                    (4.) Pommel " << std::endl
        << " Block half of incoming damage        " << attack / 4 << " damage and stuns opponent" << std::endl
        << "       Gain 40 stamina                      costs 60 stamina " << std::endl << std::endl
        << "                          5. Open inventory      " << std::endl << std::endl;
}

//Member function changes the status of the character as to whether they are stunned or not
void knight::set_stun(bool input) { not_stunned = input; }

//Member function that completes the turn of this character based on user inputs, during its turn of combat
void knight::fight_choice(const std::vector<std::shared_ptr<monsters>>* enemies, const std::vector<std::shared_ptr<players>>* heroes)
{
    //Inputs are pointers to the vectors storing all the enemies and all the user controlled characters during combat

    bool stamina_check = true; //Define the user to have enough stamina for a move to begin with so the while loop can start

    int enemy_number{}; //Stores the value for which enemy the user intends to attack

    int option{}; //Stores the value for which move the user intends to do during its turn in combat

    //Conditional to check the user is not stunned so can take its turn in combat
    if (not_stunned) {
        choice_output();
        //While loop to keep taking user inputs till they give a valid move (e.g a move they have enough stamina for or using an inventory that isn't empty)
        while (stamina_check) {
            resist = 1;
            option = integer_checker(5);//User has 5 possible moves
            //Conditionals check what move the user chose and if they have enough stamina for this move, and if they do then complete it
            if (option == 1 && stamina >= 30) {
                stamina_check = false;
                std::cout << std::endl << "Choose which enemy to attack from their number, ";
                enemy_number = integer_checker(static_cast<int>(enemies->size()));
                stamina = stamina - 30;
                (*enemies)[enemy_number - 1]->damage(attack);
            }else if (option == 2 && stamina >= 50) {
                stamina_check = false;
                stamina = stamina - 50;
                //For loop runs through all the enemies in the combat so that this move can attack them all
                for (auto enemies_iterator = enemies->begin(); enemies_iterator < enemies->end(); ++enemies_iterator) {
                    (*enemies_iterator)->damage((attack * 2) / 3);
                }
            }else if (option == 3) {
                stamina_check = false;
                stamina = stamina + 40;
                resist = 0.5;
            }else if (option == 4 && stamina >= 60) {
                stamina_check = false;
                std::cout << std::endl << "Choose which enemy to attack from their number, ";
                enemy_number = integer_checker(static_cast<int>(enemies->size()));
                stamina = stamina - 50;
                (*enemies)[enemy_number - 1]->damage(attack / 4);
                (*enemies)[enemy_number - 1]->set_stun(false);
            }else if (option == 5) {
                //Conditional to check that there is items in the inventory for the user to use
                if (bag->items_in_inventory() > 0) {
                    //Use inventory class to use inventory
                    stamina_check = bag->use_inventory(this);
                }else {
                    //If inventory is empty inform user of invalid move and go back to the start of the while loop to get another user input
                    std::cout << "Inventory is currently empty, choose another move." << std::endl;
                }
            }else {
                //If none of the user selected moves could be completed, inform them the stamina is too low and go back to the start of the while loop for another input
                std::cout << "Stamina is too low for this move.";
            }
        }
    }else {
        //If the user could not go because they were stunned, set them back to being not stunned and inform the user they can't go this turn
        std::cout << name << " STUNNED and misses a turn" << std::endl;
        stamina_check = false;
        not_stunned = true;
    }
    std::cout << std::endl;
}

//Member function for lower users health and outputing how much it has been lowered
void knight::damage(double attac)
{
    health = health - (attac * resist);
    std::cout << "Does " << (attac * resist) << " damage to " << name << std::endl << std::endl;
}

//Member function to clear all the effects currently inflicting the user, needed for the potion and at the end of every combat to reset
void knight::clear_active_effects() { effects_list.clear(); }

//Member function to add effects to the effect list
void knight::add_effects(std::pair<std::string, int> effect) { effects_list.push_back(effect); }

//Member function to handle all the current active effects on the user and complete what they do
void  knight::effects()
{
    //For loop iterates through all the active effects on the user to complete them all
    for (auto effect_iterator = effects_list.begin(); effect_iterator < effects_list.end(); effect_iterator++) {
        //Conditionals to check what the effect currently is from the list so each one can be handled in its own way
        if ((*effect_iterator).first.compare("fire") == 0) {
            //Conditional to check that the effect is still active for another turn (number of turns affecting for>0)
            if ((*effect_iterator).second > 0) {
                //Output to user the consequnces of the effect, complete its functionality and make it active for one less turn
                std::cout << "Fire after effect does 10 damage" << std::endl << std::endl;
                health = health - 10;
                (*effect_iterator).second = (*effect_iterator).second - 1;
                (*effect_iterator).second;
            }
        }else if ((*effect_iterator).first.compare("shock") == 0) {
            if ((*effect_iterator).second == 1) {
                //Once the effect is down to 0 turns left so no longer effecting the user, reset the effecting variables back to its original value
                attack = 60;
                (*effect_iterator).second = (*effect_iterator).second - 1;
            }
            if ((*effect_iterator).second > 1) {
                std::cout << "Shock effects makes " << name << " weak so does less damage on next attack" << std::endl << std::endl;
                attack = attack/2;
                (*effect_iterator).second = (*effect_iterator).second - 1;
            }
        }else if ((*effect_iterator).first.compare("poison") == 0) {
            if ((*effect_iterator).second == 1) {
                resist = resist * 0.5;
                (*effect_iterator).first = "";
                (*effect_iterator).second = (*effect_iterator).second - 1;
            }
            if ((*effect_iterator).second > 1) {
                std::cout << "Poison effects makes " << name << " weak is more vunerable to be damaged" << std::endl << std::endl;
                resist = resist * 2;
                (*effect_iterator).second = (*effect_iterator).second - 1;
            }
        }
    }
    //Lambda function to run through the affect list vector and remove any effects that are active for 0 more turns (so inactive effects now)
    effects_list.erase(std::remove_if(effects_list.begin(), effects_list.end(), [](auto const& it) {return it.second == 0; }), effects_list.end());
}

//Public accessors to member data members of class 
double knight::get_health() { return health; }
double knight::get_stamina() { return stamina; }
std::vector<std::pair<std::string, int>> knight::show_effects() { return effects_list; }
std::string knight::get_name() { return name; }

//Member functions to increase the health or stamina of the user when they are healed under different potions in the inventory
void knight::heal(double amount) { health = health + amount; }
void knight::heal_stamina(double amount) { stamina = stamina + amount; }

