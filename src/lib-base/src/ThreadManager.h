#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <STD/Vector.hpp>
//#include <Template/ArrayFwd.hpp>
#include <thread>

class ThreadManager
{
    public:
        ThreadManager(bool multithreaded);
        virtual ~ThreadManager();
        void Join();

        std::vector<std::thread> * GetThreads();
        //EnjoLib::Array<std::thread> * GetThreads();


    protected:

    private:
        bool m_multithreaded;
        std::vector<std::thread> m_threads;
        //EnjoLib::Array<std::thread> m_threads;
};

#endif // THREADMANAGER_H
