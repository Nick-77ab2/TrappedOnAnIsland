#ifndef _BOAT_H_
#define _BOAT_H_
#include <string>
#include <vector>

//Humans are coming, run like the wind.
#include "human.h"
class Human;

class Boat{
    private:
        bool full;
        bool onIsland;
        bool onMainland;
        Human* driver;
        Human* passenger;
    public:
        Boat(bool f, bool island, bool mainland);
        Human* getDriver();
        Human* getPassenger();
        void addHuman(int pos,Human* h);
        void removeHuman(int pos);
        void setFull(bool f);
        bool getFull();
        void setOnIsland(bool i);
        bool getOnIsland();
        void setOnMainland(bool m);
        bool getOnMainland();
};

#endif