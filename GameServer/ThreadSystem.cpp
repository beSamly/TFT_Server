#include "pch.h"
#include "ThreadSystem.h"
#include "TLS.h"

/*------------------
        ThreadSystem
-------------------*/

ThreadSystem::ThreadSystem()
{
    // Main Thread
    InitTLS();
}

ThreadSystem::~ThreadSystem() { Join(); }

void ThreadSystem::Launch(function<void(void)> callback)
{
    lock_guard<mutex> guard(_lock);

    _threads.push_back(thread(
        [=]()
        {
            InitTLS();
            callback();
            DestroyTLS();
        }));
}

void ThreadSystem::Join()
{
    for (thread& t : _threads)
    {
        if (t.joinable())
            t.join();
    }
    _threads.clear();
}

void ThreadSystem::InitTLS()
{
    static atomic<int> SThreadId = 1;
    LThreadId = SThreadId.fetch_add(1);
}

void ThreadSystem::DestroyTLS() {}

void ThreadSystem::DoGlobalQueueWork()
{
    while (true)
    {
        uint64 now = ::GetTickCount64();
        if (now > LEndTickCount)
            break;

        // JobRef jobRef = GGlobalJobQueue->Pop();
        /*if (jobRef == nullptr)
                break;

        jobRef->Execute();*/
    }
}

void ThreadSystem::DistributeReservedJobs()
{
    const uint64 now = ::GetTickCount64();

    // GJobTimer->Execute(now);
}
