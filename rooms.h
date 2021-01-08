#pragma once
#ifndef rooms_HEADER
#define rooms_HEADER

//Abstract base class for the different rooms the players go through
class rooms {
protected:
    static bool game_not_over; //Static data member that all rooms can access so that they can all set when the game is over (user characters die)
public:
    virtual ~rooms() {}
    virtual void complete_room() = 0;
    virtual bool return_game_not_over() = 0;
};

#endif
