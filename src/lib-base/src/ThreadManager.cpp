#include "ThreadManager.h"

using namespace std;

ThreadManager::ThreadManager(bool multithreaded)
: m_multithreaded(multithreaded)
{
}

ThreadManager::~ThreadManager()
{
    Join();
}

void ThreadManager::Join()
{
    for (thread & t : m_threads) t.join();
}

std::vector<std::thread> * ThreadManager::GetThreads()
{
    if (m_multithreaded)
    {
        return &m_threads;
    }
    else
    {
        return nullptr;
    }
}
