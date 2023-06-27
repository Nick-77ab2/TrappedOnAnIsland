#include "human.h"
#include <string>
//Beautiful human takes a type (child or adult), name (adult 1, child 1 etc.), rows, onMainland and onIsland.
 Human::Human(std::string t, std::string n, int r, bool m, bool i){
    type=t;
    name=n;
    rows=r;
    onMainland=m;
    onIsland=i;
 }
 //getter for name
 std::string Human::getName(){
    return name;
}
//getter for type
std::string Human::getType(){
    return type;
}
//add number of rows to human
void Human::addRows(int r){
    rows+=r;
}
//get the rows from the human
int Human::getRows(){
    return rows;
}
//reset them rows to 0
void Human::resetRows(){
    rows=0;
}
//set the mainland for the human
void Human::setMainland(bool m){
    onMainland=m;
}
//get whether human is on mainland.
bool Human::getMainland(){
    return onMainland;
}
//set whether human is on island
void Human::setIsland(bool i){
    onIsland=i;
}
//get whether human is on island.
bool Human::getIsland(){
    return onIsland;
}