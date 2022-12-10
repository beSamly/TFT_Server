#pragma once

#include <thread>
#include <functional>

/*------------------
        ThreadSystem
-------------------*/

using std::atomic;
using std::lock_guard;
using std::thread;

class ThreadSystem
{
public:
    ThreadSystem();
    ~ThreadSystem();

    void Launch(function<void(void)> callback);
    void Join();

    static void InitTLS();
    static void DestroyTLS();

    static void DoGlobalQueueWork();
    static void DistributeReservedJobs();

private:
    mutex _lock;
    vector<thread> _threads;
};
