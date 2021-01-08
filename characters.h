#pragma once
#ifndef CHARACTER_HEADER 
#define CHARACTER_HEADER 
#include<string>
#include<vector>

//Abstract base class (use as interface only) for all the characters, contains virtual member functions that relate to both players and enemies and their base virtual destructor 
class characters
{
public:
    virtual ~characters() {}
    virtual void damage(double) = 0;
    virtual std::string get_name() = 0;
    virtual double get_health() = 0;
    virtual void set_stun(bool) = 0;
    void virtual effects() = 0;
    virtual void add_effects(std::pair<std::string, int>) = 0;
    virtual std::vector<std::pair<std::string, int>> show_effects() = 0;
};

#endif

