#ifndef THREADRUNNER_H
#define THREADRUNNER_H

//#include "pch_base.h"
#include "ThreadManager.h"

#include <thread>

class ThreadRunner
{
    public:
        ThreadRunner(){};
        virtual ~ThreadRunner(){};

        //void RunMe(T & t, std::vector<std::thread> * threads, ctpl::thread_pool * pool);
        template <class T>
        void RunMe(T & t, ThreadManager & tman);

        //static void Run(int id, T & t);


    protected:

    private:
};

template<class T>
void ThreadRunner::RunMe(T & t, ThreadManager & tman)
{
    if (tman.GetThreads() != nullptr)
    {
        //pool->push(Run, t);
        tman.GetThreads()->push_back(std::thread(t));
    }
    else
    {
        t();
    }
}

/*
template<class T>
void ThreadRunner<T>::Run(int id, T & t)
{
    t();
}
*/
#endif // ThreadRunner_H
