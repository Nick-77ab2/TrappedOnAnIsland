/**
 * @mainpage CS361 - Island Escape
 * @section Description
 * 
 * <Include some description here>
 * 
 * Make commands:
 * 
 *  make
 * 
 * will build the binary.
 * 
 *  make run
 * 
 * will run the boat with 7 adults and 9 children
 * 
 *  make clean
 * 
 * will clear out compiled code.
 * 
 *  make doc
 * 
 * will build the doxygen files.
 */

/**
 * @file
 * @author Nick Pelletier, nwp28
 * @date 2023 5/27
 * @section Description
 * 
 * A boat does 4 second laps across the water, there are adults and children, 2 people can be on the boat at a time. it must be rowed back and there cannot be 2 adults on the same boat. Anyways that's one speedy boat.
 * Uses threads and classes (boat, human, semaphore) to run.
*/
#include <string>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>
#include <ctime>
#include <thread>
//Include Random for sleep time.
#include <random>
#include <typeinfo>

#include "human.h"
#include "boat.h"
#include "mySemaphore.h"
/**
 human thread. Acts as a greedy human and tries to get onto the boat and off of it. Can be a child or an adult.
 @param b the boat
 @param h the vector of humans
 @param number the humans number in that list
 @param numPeopleLeft the number of people left on the island (+ the boat)
 @param numadults the number of adults left
 @param numchild the number of children left
 @param sema the base semaphore used for references objects and variables
 @param cSema the semaphore used for I/O
 @return no return
*/
void humanThread(Boat &b, std::vector<Human> &h, int number, int &numPeopleLeft, int &numadults, int &numchild, mySemaphore &sema, mySemaphore &cSema);
/**
 human thread. Acts as a greedy human and tries to get onto the boat and off of it. Can be a child or an adult.
 @param b the boat
 @param n the number of people left on the island (+ the boat)
 @param sema the base semaphore used for references objects and variables
 @param cSema the semaphore used for I/O
 @return no return
*/
void gameMaster(Boat &b, int &n, mySemaphore &sema, mySemaphore &cSema);
/**
 checkNumber function
 Check an input to see if it's a number
 @param a is the arguments given in the argument list
 @param final is the length of the argument list (or the length given in general as an int)
 @return wasDigit is returned, though in general a boolean is returned.
*/
bool checkNumber(char** a, int final);

//Random Time to Wait between 1-4 seconds
std::chrono::seconds waitTime();
/*
Once thread reaches mainland it may exit

Boat:
2 seats
    Driver
    Passenger
Weight Limit
    1 child or adult alone
    2 children
    1 child 1 adult
1-4 seconds at random to row to the mainland.

Thread cannot row boat more than 4 times without a break (passenger seat for one direction or on island counts)
Always return the boat to the island
    Only one person may exit the boat on the mainland

If can't have 2 adults in the boat -> can't have 2 adults left at the end, must have at least 1 child.


Print Statistics:
    Number of times the boat traveled to the mainland
    Number of times the boat returned to the island
    Number of boats with 2 children
    Number of boats with 1 child and 1 adult
    Number of boats with only 1 person (child or adult)
    Number of times adults were the driver
    Number of times children were the driver
*/
/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char *argv[])
{
    //Initiate a random number generator
    std::srand(std::time(NULL));
    //create lock for gameMaster and children
    //std::mutex tLock;
    //unsigned int counter;
    //std::condition_variable tCond;
   // std::unique_lock<std::mutex> lk(tLock);
    //std::lock_guard<std::mutex> lock(tLock);

    //check for more than two inputs. Let user know.
    if(argc>3){
        std::cout << "Only enter two commandline argument, thanks." << std::endl;
    }
    //Let user know that they need to give an input if they didn't give one.
    else if(argc<3){
        std::cout << "Usage: island 3 5" << std::endl;
    }
    else if(!checkNumber(argv, argc)){
        std::cout << "Please only enter positive numbers" << std::endl;
    }
    else if(argv[1]==0 || argv[2]==0){
        std::cout << "Please only enter positive numbers greater than 0" << std::endl;
    }
    else{
        std::string origAdults;
        int adults;
        std::string origChildren;
        int children;
        int numPeopleLeft;
        int numChildrenLeft;
        int numAdultsLeft;
        //my own semaphore class i made using mutexes, locks, conditionals and an atomic bool. We're splitting atoms baby.
        mySemaphore sema;
        mySemaphore cSema;
        origAdults=argv[1];
        origChildren=argv[2];
        adults = stoi(origAdults);
        children = stoi(origChildren);
        numPeopleLeft=adults+children;
        numChildrenLeft=children;
        numAdultsLeft=adults;
        std::string name1="adult";
        std::string name2="child";
        std::vector<Human> finalName1;
        //creat the humans that are adults.
        for(int m=0; m<adults; m++){
            std::string theID= name1 + " " + std::to_string(m+1);
            Human human =Human(name1, theID, 0, false, true);
            finalName1.push_back(human);
        }
        //create the humans that are children.
        for(int n=0; n<children; n++){
            std::string theID1= name2 + " " + std::to_string(n+1);
            Human human1 =Human(name2, theID1, 0, false, true);
            finalName1.push_back(human1);
        }
        //create boat. we love boats.
        Boat boat= Boat(false, true, false);
        std::cout << "made boat"<<std::endl;
        //Create the ALLTHREAD that holds all threads
        std::thread allThreads[(adults+children+1)];
        allThreads[0]=std::thread(gameMaster, std::ref(boat),std::ref(numPeopleLeft), std::ref(sema), std::ref(cSema));
        for(int i=1; i<adults+1; i++){
            allThreads[i]=std::thread(humanThread, std::ref(boat), std::ref(finalName1), (i-1), std::ref(numPeopleLeft), std::ref(numAdultsLeft), std::ref(numChildrenLeft),std::ref(sema), std::ref(cSema));
        }
        for(int j=adults+1; j<adults+children+1; j++){
            allThreads[j]=std::thread(humanThread, std::ref(boat), std::ref(finalName1) , (j-1), std::ref(numPeopleLeft), std::ref(numAdultsLeft), std::ref(numChildrenLeft),std::ref(sema), std::ref(cSema));
        }
        //join threads
        for(int k=0; k<adults+children+1; k++){
            allThreads[k].join();
        }


    }

    return 0;
}

void gameMaster(Boat &boat, int &numPeopleLeft, mySemaphore &sema, mySemaphore &cSema){
    //yea mainland travels.
    int mainlandTravels=0;
    //island returns
    int islandReturns=0;
    //boats with 2 children
    int boat2c=0;
    //boats with 1 child and 1 adult
    int boat1c1a=0;
    //boats with 1 person (usually on the way back)
    int boat1p=0;
    //boats with adult drivers
    int numAdultDrivers=0;
    //boats with child drivers. we love child labor.
    int numChildDrivers=0;
    bool hasRun=false;
    int boatIdle=0;
    sema.sendWait();
    cSema.sendWait();
    std::cout<<"boat trying something"<<std::endl;
    int selfPeopleleft = numPeopleLeft;
    std::cout<<"boat succeeded trying something"<<std::endl;
    cSema.sendSignal();
    sema.sendSignal();
    //main loop starts.
    while(selfPeopleleft!=0){
        sema.sendWait();
        selfPeopleleft=numPeopleLeft;
        //If full on island start moving and add to ints for summary.
        if(boat.getOnIsland() && boat.getFull()){
            boatIdle=0;
            cSema.sendWait();
            std::cout<<"Boat is traveling from island to mainland."<<std::endl;
            cSema.sendSignal();
            mainlandTravels+=1;
            if(boat.getDriver()->getType()=="child" && boat.getPassenger()->getType()=="child"){
                numChildDrivers+=1;
                boat2c+=1;
            }
            else if(boat.getDriver()->getType()=="adult" && boat.getPassenger()->getType()=="child"){
                boat1c1a+=1;
                numAdultDrivers+=1;
            }
            else if(boat.getDriver()->getType()=="child" && boat.getPassenger()->getType()=="adult"){
                boat1c1a+=1;
                numChildDrivers+=1;
            }
            //Fall Asleep
            boat.setOnIsland(false);
		    std::this_thread::sleep_for(waitTime());
            boat.setOnMainland(true);
        }
        //if not full and on mainland and not empty, go back to island, of course add to ints for summary.
        else if(boat.getOnMainland()==true && !boat.getFull() && numPeopleLeft!=0){
            boatIdle=0;
            if(boat.getPassenger()!=NULL){
                boat.addHuman(0,boat.getPassenger());
                boat.removeHuman(1);
            }
            cSema.sendWait();
            std::cout<<"Boat is traveling from mainland to island."<<std::endl;
            cSema.sendSignal();
            boat1p+=1;
            if(boat.getDriver()->getType()=="adult"){
                numAdultDrivers+=1;
            }
            else if(boat.getDriver()->getType()=="child"){
                numChildDrivers+=1;
            }
            islandReturns+=1;
            boat.getDriver()->addRows(1);
            boat.setOnMainland(false);
            std::this_thread::sleep_for(waitTime());
            //reset boat to empty, no cheating, get in line.
            boat.getDriver()->setIsland(true);
            boat.removeHuman(0);
            boat.setOnIsland(true);
            cSema.sendWait();
            std::cout<<"There are: "<<numPeopleLeft<<" People left."<<std::endl;
            cSema.sendSignal();
        }
        hasRun=true;
        //yea just a cool thing telling you that the boat is waiting.
        if(boatIdle==0){
            cSema.sendWait();
            std::cout<<"Boat is Idling"<<std::endl;
            cSema.sendSignal();
            boatIdle=1;
        }
        sema.sendSignal();
    }
    //wait so that the threads finish their statements etc first.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cSema.sendWait();
    std::cout<<"\nSummary of Events:\n\tBoat traveled to the mainland: "<<mainlandTravels<<"\n\tBoat returned to the island: "<< islandReturns<<"\n\tBoats with 2 children: "<< boat2c<<"\n\tBoats with 1 child and 1 adult: "<<boat1c1a<<"\n\tBoats with only 1 person (child or adult): "<<boat1p<<"\n\tTimes adults were the driver: "<<numAdultDrivers<<"\n\tTimes children were the drivers: "<<numChildDrivers<<std::endl;
    cSema.sendSignal();

}

void humanThread(Boat &boat, std::vector<Human> &human, int number, int &numPeopleLeft, int &numAdultsLeft, int &numChildrenLeft, mySemaphore &sema, mySemaphore &cSema){
    //useless bool that just makes me feel better on my obviously worthless empty if statements.
    bool hasTried=false;
    //usefull bool that take the place of the reference to the human's position.
    bool onMainland=false;
    //create a start counter for my sake.
    int startCounter=0;
    sema.sendWait();
    std::string currentName = human[number].getName();
    sema.sendSignal();
    std::string pos;
    //start main loop
    while(!onMainland){
        if(startCounter==0){
            cSema.sendWait();
            std::cout<<currentName<<" Starting"<<std::endl;
            cSema.sendSignal();
            startCounter+=1;
        }
        sema.sendWait();
        //run this if on the island.
        if(boat.getOnIsland() && !boat.getFull() && human[number].getIsland()){
            if(boat.getDriver()==nullptr && human[number].getRows()<4 && human[number].getType()=="adult" && numAdultsLeft>=numChildrenLeft){
                boat.addHuman(0, &human[number]);
                pos="driver";
                human[number].addRows(1);
                human[number].setIsland(false);
                cSema.sendWait();
                std::cout<<currentName<<" got into the driver's seat of the boat"<<std::endl;
                cSema.sendSignal();
            }
            else if(boat.getDriver()==nullptr && human[number].getRows()<4 && numAdultsLeft<=numChildrenLeft){
                boat.addHuman(0, &human[number]);
                pos="driver";
                human[number].addRows(1);
                human[number].setIsland(false);
                cSema.sendWait();
                std::cout<<currentName<<" got into the driver's seat of the boat"<<std::endl;
                cSema.sendSignal();
            }
            else if(boat.getDriver()!=nullptr && human[number].getType()=="adult"){
                if(boat.getDriver()->getType()=="adult"){
                    hasTried=true;
                }
                else{
                    boat.addHuman(1, &human[number]);
                    pos="passenger";
                    human[number].setIsland(false);
                    human[number].resetRows();
                    boat.setFull(true);
                    cSema.sendWait();
                    std::cout<<currentName<<" got into the passenger seat of the boat"<<std::endl;
                    cSema.sendSignal();
                }
            }
            else{
                boat.addHuman(1, &human[number]);
                pos="passenger";
                human[number].resetRows();
                boat.setFull(true);
                cSema.sendWait();
                std::cout<<currentName<<" got into the passenger seat of the boat"<<std::endl;
                cSema.sendSignal();
            }
            //just in case.
            if(numPeopleLeft==1){
                cSema.sendWait();
                std::cout<<currentName<<" is trying to set the boat to full with 1 person left"<<std::endl;
                cSema.sendSignal();
                boat.setFull(true);
            }
        }
        //run this if when we reach the mainland and there's more than 2 people left.
        else if(boat.getOnMainland() && boat.getFull() && !human[number].getIsland() && !human[number].getMainland() && numPeopleLeft>2){
            if(pos=="passenger"){
                if(boat.getDriver()->getRows()==3){
                    hasTried=true;
                }
                else if(human[number].getType()=="adult" && numAdultsLeft>=numChildrenLeft){
                    boat.removeHuman(1);
                    numAdultsLeft-=1;
                    numPeopleLeft-=1;
                    human[number].setMainland(true);
                    boat.setFull(false);
                }
                else if(human[number].getType()=="child" && boat.getDriver()->getType()=="child" && numAdultsLeft>=numChildrenLeft){
                    boat.removeHuman(1);
                    numChildrenLeft-=1;
                    numPeopleLeft-=1;
                    human[number].setMainland(true);
                    boat.setFull(false);
                }
                else if(human[number].getType()=="child" && numAdultsLeft>=numChildrenLeft){
                    hasTried=true;
                }
                else if(human[number].getType()=="adult" && numAdultsLeft<numChildrenLeft){
                    boat.removeHuman(1);
                    numAdultsLeft-=1;
                    numPeopleLeft-=1;
                    human[number].setMainland(true);
                    boat.setFull(false);
                }
                else{
                    boat.removeHuman(1);
                    numChildrenLeft-=1;
                    numPeopleLeft-=1;
                    human[number].setMainland(true);
                    boat.setFull(false);
                }
            }
            else if(pos=="driver"){
                if(human[number].getType()=="adult" && numAdultsLeft>=numChildrenLeft){
                    boat.removeHuman(0);
                    human[number].setMainland(true);
                    numAdultsLeft-=1;
                    numPeopleLeft-=1;
                    boat.setFull(false);
                }
                else if(human[number].getType()=="child" && boat.getPassenger()->getType()=="child" && numAdultsLeft>=numChildrenLeft){
                    boat.removeHuman(0);
                    human[number].setMainland(true);
                    numPeopleLeft-=1;
                    numChildrenLeft-=1;
                    boat.setFull(false);
                }
                else if(human[number].getType()=="child" && numAdultsLeft>=numChildrenLeft){
                    hasTried=true;
                }
                else if(human[number].getType()=="adult" && numAdultsLeft<numChildrenLeft){
                    boat.removeHuman(0);
                    human[number].setMainland(true);
                    numAdultsLeft-=1;
                    numPeopleLeft-=1;
                    boat.setFull(false);
                }
                else{
                    boat.removeHuman(0);
                    human[number].setMainland(true);
                    numPeopleLeft-=1;
                    numChildrenLeft-=1;
                    boat.setFull(false);
                }
            }
        }
        //run this if when we're on the mainland and there's 2 people left. being in here insures that the last 2 get off.
        else if(boat.getOnMainland() && boat.getFull() && !human[number].getIsland() && !human[number].getMainland() && numPeopleLeft==2){
            boat.getPassenger()->setMainland(true);
            boat.removeHuman(1);
            boat.getDriver()->setMainland(true);
            boat.removeHuman(0);
            boat.setFull(false);
            numPeopleLeft-=2;
        }
        hasTried=true;
        //we did it.
        if(human[number].getMainland()){
            cSema.sendWait();
            std::cout<<currentName<<" On Mainland"<<std::endl;
            cSema.sendSignal();
            onMainland=true;
        }
        sema.sendSignal();
    }
}

//checking if the inputs are numbers.
bool checkNumber(char** a, int final){
    bool wasDigit=true;
    std::string first = a[1];
    std::string second = a[2];
        //check if that input is actually a number.
        for(size_t i=0; i< first.length(); i++ )
        {
            if(isdigit(first[i])){
                wasDigit=true;
                continue;
            }
            else{
                //leave loop if it's not a number
                wasDigit=false;
                break;
            }
        }
        for(size_t i=0; i< second.length(); i++ )
        {
            if(isdigit(second[i])){
                wasDigit=true;
                continue;
            }
            else{
                //leave loop if it's not a number
                wasDigit=false;
                break;
            }
        } 
    return wasDigit;
}

//Wait a random time to simulate hard work
std::chrono::seconds waitTime(){
	int time2Wait = 1+ (std::rand()%4);
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	return t;
}