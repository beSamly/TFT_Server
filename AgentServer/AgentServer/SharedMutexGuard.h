#pragma once

#include <shared_mutex>

using std::shared_mutex;

class SMWriteLockGuard
{
public:
    SMWriteLockGuard(shared_mutex& lock);
    ~SMWriteLockGuard();

private:
    shared_mutex& _lock;
};

class SMReadLockGuard
{
public:
    SMReadLockGuard(shared_mutex& lock);
    ~SMReadLockGuard();

private:
    shared_mutex& _lock;
};