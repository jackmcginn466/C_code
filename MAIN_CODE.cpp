//Jack McGinn
//Main program code to run the tower quest game
//C++ Programmin Project
//30/04/2020

//Include classes required for the program defined in other files
#include "health_potion.h"
#include "inventory.h"
#include "knight.h"
#include "mage.h"
#include "demon.h"
#include"spider.h"
#include"gargoyle.h"
#include"boss.h"
#include "fight_room.h"
#include "boss_fight_room.h"
#include"get_inventory_room.h"
#include "puzzle_room.h"

int main()
{
    // Set precision of outputs
    std::cout.precision(3);
    
    //Introductory output message to user
    std::cout << "             ______________                                                                   ______________                                                            .-.           " << std::endl
        << "             \\____    ____/                                      ________   ______            |   _______   |               _________    _______    _________         __|=|__      " << std::endl
        << "                 |    |     _________   ____             _____  |  ______| |  __  |           |  |       |  |               |   _____|  /  _____|  |___   ___|       (_/`-`\\_)   " << std::endl
        << "                 |    |    |    __   |  \\    \\    /\\    /    /  |  |_____  | |__| |           |  |   __  |  |  ___    ___   |  |_____   |  \\____       |  |          //\\___/\\\\    " << std::endl
        << "                 |    |    |   |  |  |   \\    \\  /  \\  /    /   |   _____| |    __/           |  |___\\ \\_|  |  |  |   |  |  |   _____|   \\____  \\      |  |          <>/   \\<>   " << std::endl
        << "                 |    |    |   |__|  |    \\    \\/ __ \\/    /    |  |_____  | |\\ \\             |_______   ___|  |  |___|  |  |  |_____    ____/  |      |  |           \\|_._|/ " << std::endl
        << "                 |____|    |_________|     \\_____/  \\_____/     |________| |_| \\_\\                    \\__\\     |_________|  |________|  |_______/      |__|            <_I_>  " << std::endl
        << "                                                                                                                                                                        |||" << std::endl
        << "             _______________________________________________________________________Full screen output window ____________________________________________________     /_|_\\" << std::endl << std::endl
        << "Legend tells of an ancient treasure of great power locked away at the top of a dark tower in some distant kingdom. A young king eager to prove himself is desperate for this power." << std::endl
        << "He sends his 2 greatest heroes, a nameless knight and mage, to retrieve this legendary treasure. After weeks of traveling through dangerous and perilous  lands, the Knight and the " << std::endl
        << "Mage finally arrive at the foot of the tower." << std::endl << std::endl;
    std::cout << "Press Enter to enter the tower:";
    std::cin.get();
    std::cout << std::endl;
    
    //Define class to hold users inventory
    inventory bag;
    
    //Define a polymorphic vector that stores the characters the user controls, and initialise them with access to their shared inventory called bag
    std::vector<std::shared_ptr<players>> users;
    users.push_back(std::make_shared<knight>(knight{ &bag }));
    users.push_back(std::make_shared<mage>(mage{ &bag }));
    
    //Define a polymorphic vector that stores the rooms the users go through, where each is intialised with access to the data they need to complete the room
    std::vector<std::unique_ptr<rooms>> tower;
    tower.push_back(std::make_unique<fight_room>(fight_room{ &users }));
    tower.push_back(std::make_unique<get_inventory_room>(get_inventory_room{ &bag }));
    tower.push_back(std::make_unique<puzzle_room>(puzzle_room{ (rand() % 5) + 3 }));
    tower.push_back(std::make_unique<boss_fight_room>(boss_fight_room{ &users }));
    
    //For loop iterates through all the rooms in the tower then completes the actions the user needs to to progress on to the next room
    for (auto room_iterator = tower.begin(); room_iterator < tower.end(); ++room_iterator) {
        //Conditional checks whether the game is continuing and whether to complete the next room (if the users characters are alive)
        if ((*room_iterator)->return_game_not_over()) {
            (*room_iterator)->complete_room();
            //Reset status of next room depending on whether the users characters died in the current room
        }
    }
    
    //Clear data
    users.clear();
    tower.clear();
    
    return 0;
}


