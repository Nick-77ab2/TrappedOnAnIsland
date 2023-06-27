//Note: You must use the C++ standard classes like mutex locks and conditional variables. 
//You may use these directly or implement them as part of one or more classes. 
//You need to build up your tools using just the features provided by the C++ standard library.
//So I make my own.
#include "mySemaphore.h"

//Implementation of basic semaphore using atomic bool and lock.
mySemaphore::mySemaphore(){
    std::lock_guard<std::mutex> lk(tLock);
    ready.store(true);
}
//signal sending using lock atomic bool and condition variable
void mySemaphore::sendSignal(){
    std::lock_guard<std::mutex> lk(tLock);
    ready.store(true);
    tCond.notify_all();
}
//wait sending using unique_lock condition variable and atomic bool.
void mySemaphore::sendWait(){
    std::unique_lock<std::mutex> lk(tLock);
    tCond.wait(lk, [this](){return ready.load();});
    ready.store(false);
    lk.unlock();
    return;
}