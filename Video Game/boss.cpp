#include "boss.h"
#include"players.h"
#include<algorithm>

//Definitions of member functions for the boss enemy

boss::boss() {}
//Parameterized constructor to construct a boss enemy with a given health and effects
boss::boss(double HP, std::vector<std::pair<std::string, int>> effects) {
    health = HP;
    effects_list = effects;
}
boss::~boss() {}

//Member function to complete monsters move during combat
void boss::fight(const std::vector<std::shared_ptr<players>>* player)
{
    //Input is a pointer to a polymorphic vector storing all the players characters the monster is currently fighting against
    if (not_stunned) {
        //Conditional to check the monster is not stunned so can take its turn in combat

        int option = rand() % 5;//Randomly generate which move the monster makes in combat

        int which_player = rand() % player->size();//Randomly generate which of the users characters the monster attacks

        //Conditionals to check which move the monster randomly took and then the code underneath to complete that move on the randomly selected character it is attacking
        if (option == 1) {
            std::cout << "Does basic attack: ";
            (*player)[which_player]->damage(attack);
        }else if (option == 2) {
            std::cout << "Does power attack and stuns oppponent: ";
            (*player)[which_player]->damage(attack / 2);
            (*player)[which_player]->set_stun(false);
        }else if (option == 3) {
            std::cout << "Does venom attack and poisons oppponent: ";
            (*player)[which_player]->damage((3 * attack) / 4);
            (*player)[which_player]->add_effects({ "poison", 2 });
        }else if (option == 4) {
            std::cout << "Does fire attack and inflicts fire damage: ";
            (*player)[which_player]->damage(attack);
            (*player)[which_player]->add_effects({ "fire",5 });
        }else {
            std::cout << "Does shock attack and inflicts shock damage: ";
            (*player)[which_player]->damage(attack);
            (*player)[which_player]->add_effects({ "shock",2 });
        }
    }else {
        //If the user was stunned this turn, set them back to not being stunned so that they can do their go next turn
        not_stunned = true;
        std::cout << "Stunned amd misses a turn" << std::endl << std::endl;
    }
}

//Member function for lower users health and outputing how much it has been lowered
void boss::damage(double attac)
{
    health = health - (attac * resist);
    std::cout << "Does " << (attac * resist) << " damage to " << name << std::endl << std::endl;
}

//Member function changes the status of the character as to whether they are stunned or not
void boss::set_stun(bool input) { not_stunned = input; }

//Member function to add effects to the effect list
void boss::add_effects(std::pair<std::string, int> effect) { effects_list.push_back(effect); }

//Member function to handle all the current active effects on the user and complete what they do
void  boss::effects()
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
                attack = 70;
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
double boss::get_health() { return health; }
std::string boss::get_name() { return name; }
std::vector<std::pair<std::string, int>> boss::show_effects() { return effects_list; }
