#include "fight_room.h"
#include "players.h"
#include"demon.h"
#include"spider.h"
#include"gargoyle.h"
#include<algorithm>

//Definition of member functions for a combat room

fight_room::fight_room() {}
fight_room::fight_room(std::vector<std::shared_ptr<players>>* player) : players_list{ *player } { };
fight_room::~fight_room() {}

//Member function to change the status of the rooms to be game over when the user characters die
bool fight_room::return_game_not_over() { return game_not_over; }
//Member function to complete the users turn in combat
void fight_room::users_turn() {
    //Lambda function to run through all the users characters so they can each make their move
    std::for_each(players_list.begin(), players_list.end(), [this](std::shared_ptr<players> player)
    {
        //Conditional to check all the enemies have not already been defeated so that the user can take their turn
        if (enemy_list.size() > 0) {
            std::cout << player->get_name() << " TURN: ";
            player->effects();
            //Conditional to check the user character is not efeated so that they can take their turn
            if (player->get_health() <= 0) {
                std::cout << player->get_name() << " is defeated" << std::endl << std::endl;
            }else {
                output_message();
                player->fight_choice(&enemy_list, &players_list);
                //Lambda function to remove any enemies from the room if they have been defeated (less then 0 health)
                enemy_list.erase(std::remove_if(enemy_list.begin(), enemy_list.end(), [](auto const& it) {return it->get_health() <= 0; }), enemy_list.end());
                //Conditional to check if all the enemies in the room have been defeated so the heroes won
                if (enemy_list.size() == 0) {
                    std::cout << "Enemies defeated" << std::endl << std::endl;
                }
            }
        }
    });
    //Lambda function to remove any user controled characters from the room if they have been defeated (less then 0 health)
    players_list.erase(std::remove_if(players_list.begin(), players_list.end(), [](auto const& it) {return it->get_health() <= 0; }), players_list.end());
    //Conditional to check if all the user characters have been defeated, so the game is over and the status of all rooms can be changed to this so the game does not continue
    if (players_list.size() == 0) {
        std::cout << "GAME OVER!!";
        players_list.clear();
        game_not_over = false;
        return;
    }
}
//Member function to complete the enemies turn in combat
void fight_room::enemies_turn() {
    int count{ 1 };
    //Lambda function to run through all the enemy monsters so they can each make their move
    std::for_each(enemy_list.begin(), enemy_list.end(), [&count, this](std::shared_ptr<monsters> enemy)
    {
        //Conditional to check all the players have not already been defeated so that the user can take their turn
        if (players_list.size() > 0) {
            std::cout << enemy->get_name() << " " << count << ": " << std::endl;
            count++;
            enemy->effects();
            //Conditional to check the enemy is not defeated so that they can take their turn
            if (enemy->get_health() <= 0) {
                std::cout << enemy->get_name() << " is defeated" << std::endl << std::endl;
            }else {
                enemy->fight(&players_list);
                //Lambda function to remove any players from the room if they have been defeated (less then 0 health)
                players_list.erase(std::remove_if(players_list.begin(), players_list.end(), [](auto const& it) {return it->get_health() <= 0; }), players_list.end());
                //Conditional to check if all the user characters in the room have been defeated so the enemies won
                if (players_list.size() == 0) {
                    std::cout << "Game Over"<<std::endl<<std::endl;
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
    }
    else {
        std::cin.ignore();
        std::cout << "Press Enter to Continue";
        std::cin.get();
        std::cout << std::endl;
    }
}

//Member function to display output message of what the current status and situaiotn of the combat encounter looks like
void fight_room::output_message() {
    int count{ 1 }; //Numbers enemies so they are easier to identify
    std::cout << std::endl << std::endl;
    //For loop runs through all the enemies in the room so all their current status can be output
    for (auto enemies_vector_iterator = enemy_list.begin(); enemies_vector_iterator < enemy_list.end(); ++enemies_vector_iterator) {
        //Conditional to check that enemy has not been defeated so its status can be output
        if ((*enemies_vector_iterator)->get_health() > 0) {
            std::cout << count << ". " << *(*enemies_vector_iterator) << "       ";
            count++;
        }
    }
    count = 1;
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
    //For loop runs through all the players in the room so all their current status can be output
    for (auto players_vector_iterator = players_list.begin(); players_vector_iterator < players_list.end(); ++players_vector_iterator) {
        //Conditional to check that enemy has not been defeated so its status can be output
        if ((*players_vector_iterator)->get_health() > 0) {
            std::cout << count << ". " << *(*players_vector_iterator) << "        ";
            count++;
        }
    }
    std::cout << std::endl << std::endl;
}

//Member function to complete all the actions required in this room for the user to progress
void fight_room::complete_room()
{
    //Add enemies to the room
    enemy_list.push_back(std::make_shared<demon>(demon{}));
    enemy_list.push_back(std::make_shared<spider>(spider{}));
    enemy_list.push_back(std::make_shared<gargoyle>(gargoyle{}));

    std::cout << "As the mage and knight enter they notice three monsters knawing away at a rotting human corpse in the corner. The monsters look up from their meal, and look" << std::endl
              << "with hungry eyes at the heroes who just entred. A fight begins. " << std::endl << std::endl;
    std::cout << "Press Enter to start the combat:";
    std::cin.get();
    std::cout << std::endl;
    //While loop to keep making user and enemy turns in combat until one side has defeated the other (there is 0 of them left)
    while (players_list.size() >= 1 && enemy_list.size() >= 1) {
        users_turn();
        if (players_list.size() >= 1 && enemy_list.size() >= 1) {
            enemies_turn();
        }
    }
    //Conditional to check if the room ended with the heroes winning, so any effects on them can be cleared before they progress
    if (players_list.size() > 0) {
        //For loop to run through all the user characters to clear all the effects on them ready for the next room now that combat is over
        for (auto player_it = players_list.begin(); player_it < players_list.end(); ++player_it) {
            (*player_it)->clear_active_effects();
        }
        enemy_list.clear();
        std::cout << "With the monsters defeated, the heroes can now move onward up the tower." << std::endl << std::endl;
        std::cin.ignore();
        std::cout << "Press Enter to move up the stairs to the next room:";
        std::cin.get();
    }
}
