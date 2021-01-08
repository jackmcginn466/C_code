#pragma once
#ifndef boss_fight_room_HEADER
#define boss_fight_room_HEADER

//include dependencies
#include "fight_room.h"

//Derived class of fight room - special case of this room when the enemy is of boss type, overwrites the enemy turn function and complete room
class boss_fight_room : public fight_room
{
protected:
    double summon_at_health{ 50 };
    double double_at_health{ 200 };
public:
    boss_fight_room();
    boss_fight_room(std::vector<std::shared_ptr<players>>*);
    ~boss_fight_room();

    //Member function to change the status of the rooms to be game over when the user characters die
    bool return_game_not_over();
    //Member function to complete the enemies turn in combat
    void enemies_turn();

    //Member function to complete all the actions required in this room for the user to progress
    void complete_room();
};

#endif

