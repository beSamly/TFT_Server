#include "pch.h"
#include "SharedMutexGuard.h"

/*	write lock guard  */
SMWriteLockGuard::SMWriteLockGuard(shared_mutex& lock) : _lock(lock) { _lock.lock(); }

SMWriteLockGuard::~SMWriteLockGuard() { _lock.unlock(); }

/*	read lock guard   */
SMReadLockGuard::SMReadLockGuard(shared_mutex& lock) : _lock(lock) { _lock.lock_shared(); }

SMReadLockGuard::~SMReadLockGuard() { _lock.unlock_shared(); }
