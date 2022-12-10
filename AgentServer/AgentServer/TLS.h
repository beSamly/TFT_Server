#pragma once
#include <stack>

using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using int32 = __int32;

extern thread_local uint32				LThreadId;
extern thread_local uint64				LEndTickCount;
extern thread_local std::stack<int32>	LLockStack;
extern thread_local class JobQueue* LCurrentJobQueue;