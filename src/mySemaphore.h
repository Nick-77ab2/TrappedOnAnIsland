#ifndef _MYSEMAPHORE_H_
#define _MYSEMAPHORE_H_

#include <mutex>
#include <atomic>
#include <condition_variable>

class mySemaphore{
    private:
        //oh yeah atomic bool
        std::atomic<bool> ready;
        //mutable lock
        mutable std::mutex tLock;
        //standard condition variable
        std::condition_variable tCond;

    public:

        mySemaphore();

        void sendSignal();

        void sendWait();
};

#endif