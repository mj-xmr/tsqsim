#ifndef CPTLWRAP_H
#define CPTLWRAP_H

#include "CtplWrapStatic.h"

#include "ctpl_stl.h"

#include <STD/Vector.hpp>
#include <STD/Algorithm.hpp>
#include <future>

/* TODO:
Version, which doesn't need to return anything.
*/
template <class T>
class CtplWrap
{
    public:
        CtplWrap()
        : pool(m_stat.GetNumCores())
        {
        
        }
        virtual ~CtplWrap(){}
        
        CtplWrapStatic & GetCfgRW() {return m_stat;}
        template<typename Fun, typename... Args>
        void Add(Fun funct, Args... args)
        {
            if (m_stat.IsMT())
            {
                m_futures.push_back(pool.push(funct, args...));
                // Variant: C++11, not thread pool:
                //futures.push_back (std::async(std::launch::async, GetSymbolStatic, 0, this, sym, periodNames));
            }
            else
            {
                const int idd = 0; // CTPL limitation
                m_rets.push_back(funct(idd, args...));
                // m_futures.push_back (std::async(std::launch::deferred, funct, args...));
            }
        }

        std::vector<T> Get()
        {
            std::vector<T> ret;
            if (! m_futures.empty())
            {
                if (m_stat.IsReversed())
                {
                    for(int i = int(m_futures.size()) - 1; i >= 0; --i) {
                        m_rets.push_back(m_futures.at(i).get());
                    }
                    std::reverse(m_rets.begin(), m_rets.end());
                }
                else
                {
                    for(auto &e : m_futures) {
                        m_rets.push_back(e.get());
                    }
                }
                m_futures.clear();
            }
            std::swap(ret, m_rets);
            return ret;
        }

    protected:

    private:
        CtplWrapStatic m_stat;
        std::vector<std::future<T>> m_futures;
        std::vector<T> m_rets;
        ctpl::thread_pool pool;
};

#endif // CPTLWRAP_H
