#include "demon.h"
#include"players.h"
#include<algorithm>

//Definition of member functions for the demon enemy type

demon::demon() {}
demon::~demon() {}

//Member function to complete monsters move during combat
void demon::fight(const std::vector<std::shared_ptr<players>>* player)
{
    //Input is a pointer to a polymorphic vector storing all the players characters the monster is currently fighting against

    int option = rand() % 10;//Randomly generate which move the monster makes in combat

    int which_player = rand() % player->size();//Randomly generate which of the users characters the monster attacks

    //Conditional to check the monster is not stunned so can take its turn in combat
    if (not_stunned) {
        //Conditionals to check which move the monster randomly took and then the code underneath to complete that move on the randomly selected character it is attacking
        if (option <= 7) {
            std::cout << "Does basic attack: ";
            (*player)[which_player]->damage(attack);
        }else {
            std::cout << "Does fire attack and inflicts fire damage: ";
            (*player)[which_player]->damage(attack);
            (*player)[which_player]->add_effects({ "fire",5 });
        }
    }else {
        //If the user was stunned this turn, set them back to not being stunned so that they can do their go next turn
        not_stunned = true;
        std::cout << "Stunned amd misses a turn" << std::endl;
    }
}
////Member function for lower users health and outputing how much it has been lowered
void demon::damage(double attac)
{
    health = health - (attac * resist);
    std::cout << "Does " << (attac * resist) << " damage to " << name << std::endl << std::endl;
}
//Member function changes the status of the character as to whether they are stunned or not
void demon::set_stun(bool input) { not_stunned = input; }

//Member function to add effects to the effect list
void demon::add_effects(std::pair<std::string, int> effect) { effects_list.push_back(effect); }
//Member function to handle all the current active effects on the user and complete what they do
void  demon::effects()
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
                attack = 40;
                (*effect_iterator).second = (*effect_iterator).second - 1;
            }
            if ((*effect_iterator).second > 1) {
                std::cout << "Shock effects makes " << name << " weak so does less damage on next attack" << std::endl << std::endl;
                attack = attack * 0.5;
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
double demon::get_health() { return health; }
std::string demon::get_name() { return name; }
std::vector<std::pair<std::string, int>> demon::show_effects() { return effects_list; }
