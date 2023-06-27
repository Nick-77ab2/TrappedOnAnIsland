#include <iostream>
#include "boat.h"
//Your standard boat constructor, needs bool full, bool island and bool mainland.
Boat::Boat(bool f, bool island, bool mainland){
    full=f;
    onIsland=island;
    onMainland=mainland;
    driver=nullptr;
    passenger=nullptr;
}
//you can get the driver from the boat.
Human* Boat::getDriver(){
    return driver;
}
//you can get the passenger from the boat
Human* Boat::getPassenger(){
    return passenger;
}
//you can add a reference to a human to the boat in either the driver or passenger position.
void Boat::addHuman(int pos,Human* h){
    if(pos==0){
        driver=h;
    }
    else{
        passenger=h;
    }
}
//you can remove the reference to the human in the driver or passenger position.
void Boat::removeHuman(int pos){
    if(pos==0){
        driver=nullptr;
    }
    else{
        passenger=nullptr;
    }
}
//yea set it to full
void  Boat::setFull(bool f){
    full = f;

}
//getter for full
bool  Boat::getFull(){
    return full;
}
//can set whether it's on island or not
void  Boat::setOnIsland(bool i){
    onIsland=i;
}
//getter for island
bool  Boat::getOnIsland(){
    return onIsland;
}
//can set whether it's on mainland or not.
void  Boat::setOnMainland(bool m){
    onMainland=m;
}
//yea getter for on island.
bool  Boat::getOnMainland(){
    return onMainland;
}