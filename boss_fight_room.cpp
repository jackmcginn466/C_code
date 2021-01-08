#include "boss_fight_room.h"
#include "players.h"
#include"boss.h"
#include "demon.h"
#include<algorithm>

//Definition of member functions for the room where the user fights the boss

boss_fight_room::boss_fight_room() {}
boss_fight_room::boss_fight_room(std::vector<std::shared_ptr<players>>* player) { players_list = *player; };
boss_fight_room::~boss_fight_room() { players_list.clear(); enemy_list.clear();}

//Member function to change the status of the rooms to be game over when the user characters die
bool boss_fight_room::return_game_not_over() { return game_not_over; }
//Member function to complete the enemies turn in combat
void boss_fight_room::enemies_turn() {
    int count{ 1 };
    std::vector<std::shared_ptr<monsters>> temp_enemy_list;//Stores temporary enemies that the room will generate mid-combat until they are added on to the main enemy vector
    //Lambda function to run through all the enemy monsters so they can each make their move
    std::for_each(enemy_list.begin(), enemy_list.end(), [&count, this, &temp_enemy_list](std::shared_ptr<monsters> enemy)
    {
        //Conditional to check all the players have not already been defeated so that the user can take their turn
        if (players_list.size()) {
            std::cout << enemy->get_name() << " " << count << ": " << std::endl << std::endl;
            count++;
            enemy->effects();
            //Conditional to check the enemy is not defeated so that they can take their turn
            if (enemy->get_health() <= 0) {
                std::cout << enemy->get_name() << " is defeated" << std::endl << std::endl;
                //Conditionals to check the health of the boss enemy to see if it should complete any special actions (duplicating itself or adding a demon to the enemy_list to fight is well)
            }else if (enemy->get_health() <= summon_at_health && enemy_list.size() < 3 && enemy->get_name().compare("BOSS ENEMY") == 0) {
                //Add them to temp enemy list to after the enemies turn be added to the enemy_list and then clearing the temp_enemy_list for next turn
                temp_enemy_list.push_back(std::make_shared<demon>(demon{}));
                summon_at_health = 0.25 * summon_at_health;
                std::cout << "Summons a demon to assist" << std::endl << std::endl;

            }else if (enemy->get_health() <= double_at_health && enemy_list.size() < 3 && enemy->get_name().compare("BOSS ENEMY") == 0) {
                //Use parameterised constructor to create new boss so it has the same values as the current boss who's turn it is so that appears to be duplicating itself
                temp_enemy_list.push_back(std::make_shared<boss>(boss{ enemy->get_health(),enemy->show_effects() }));
                double_at_health = 0.5 * double_at_health;
                std::cout << "Duplicates itself" << std::endl << std::endl;
            }else {
                enemy->fight(&players_list);
                //Lambda function to remove any players from the room if they have been defeated (less then 0 health)
                players_list.erase(std::remove_if(players_list.begin(), players_list.end(), [](auto const& it) {return it->get_health() <= 0; }), players_list.end());
                //Conditional to check if all the user characters in the room have been defeated so the enemies won
                if (players_list.size() == 0) {
                    std::cout << "GAME OVER" << std::endl << std::endl;
                    players_list.clear();
                    game_not_over = false;
                    return;
                }
            }
        }
    });
    //Lambda function to remove any enemy monsters from the room if they have been defeated (less then 0 health)
    enemy_list.erase(std::remove_if(enemy_list.begin(), enemy_list.end(), [](auto const& it) {return it->get_health() <= 0; }), enemy_list.end());
    //Conditional to check whether all the enemies have been defeated so the room is complete or not
    if (enemy_list.size() == 0) {
        std::cout << "Enemies defeated" << std::endl << std::endl;
    }else {
        //If the enemies have not been defeated, run through the temp enemy list and add these ones on to the enemy list and then clear the temp enemy list for next turn
        for (auto temp_enemies_vector_iterator = temp_enemy_list.begin(); temp_enemies_vector_iterator < temp_enemy_list.end(); ++temp_enemies_vector_iterator) {
            enemy_list.push_back(*temp_enemies_vector_iterator);
        }
        temp_enemy_list.clear();
        std::cin.ignore();
        std::cout << "Press Enter to Continue";
        std::cin.get();
        std::cout << std::endl;
    }
}

//Member function to complete all the actions required in this room for the user to progress
void boss_fight_room::complete_room()
{
    //Add enemies to the room
    enemy_list.push_back(std::make_shared<boss>(boss{}));
    std::cout << "The mage and knight enter the final room of the tower noticing they have reached its summit. In the centre of the room stands a great fearsome monster, clearly" << std::endl
        << "standing guard over the huge treasure chest that lies behind it.The monster locks eyes with the heroes, ready to defend its treasure. A fight begins. " << std::endl << std::endl;
    std::cout << "Press Enter to start the combat:";
    std::cin.get();
    std::cout << std::endl;
    //While loop to keep making user and enemy turns in combat until one side has defeated the other (there is 0 of them left)
    while (players_list.size() >= 1 && enemy_list.size() >= 1) {
        users_turn();
        //Conditional to check the fight is still continuing (both sides still alive) so that the enemies should take their turn too
        if (players_list.size() >= 1 && enemy_list.size() >= 1) {
            enemies_turn();
        }
    }
    //Conditional to check if the room ended with the heroes winning, so any effects on them can be cleared before they progress
    if (players_list.size() > 0) {
        enemy_list.clear();
        std::cout << "With the monster vanquished the two heros head to the chest to retrieve the treasure they have traveled and fought so hard for." << std::endl << std::endl;
        std::cout << "Tower quest complete - YOU WON!!" << std::endl << std::endl;

    }
}