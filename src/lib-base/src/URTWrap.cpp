#include "URTWrap.h"

#include <Template/CorradePointer.h>

#include <STD/VectorCpp.hpp>

using namespace std;

URTWrap::URTWrap(){}

#include <Eigen/Dense>
/// TODO: Upstream to EnjoLib 3rd
static Eigen::VectorXd ConvertVector1( const EnjoLib::VecD & vec )
{
    const int nrows = vec.size();
    Eigen::VectorXd veceig(nrows);
    for ( int i = 0; i < nrows; ++i )
            veceig(i) = vec.at(i);

    return veceig;
}

//#define USE_URT
#ifdef USE_URT
#include <URT.hpp>
//#include <URT/URT.hpp> // old
double URTWrap::GetStatistic(const EnjoLib::VecD & data, int lags) const
{
    try
    {
        // initializing ADF test with 10 lags and constant trend
        //urt::ADF<double> test(data, data.size() * 0.3, "ct");
        return Create(data, lags)->GetStatistic();
    }
    catch (std::exception & ex)
    {
        cout << ex.what() << endl;
        return 0;
    }
}

void URTWrap::Show(const EnjoLib::VecD & data, int lags) const
{
    try
    {
        Create(data, lags)->Show();
    }
    catch (std::exception & ex)
    {
        cout << ex.what() << endl;
    }
}

class URTAlgo : public IURTAlgo
{
    public:
        //using Algo = urt::ADF<double>;
        using Algo = urt::DFGLS<double>;
        //using Algo = urt::PP<double>;
        //using Algo = urt::KPSS<double>;
        URTAlgo(const EnjoLib::VecD & data, int lags = 0)
        {
            if (lags == 0)
            {
                m_algo = CorPtr<Algo>(new Algo(ConvertVector1(data.Data()), "AIC", "c"));
            }
            else
            {
                m_algo = CorPtr<Algo>(new Algo(ConvertVector1(data.Data()), lags, "c"));
            }
        }
        virtual ~URTAlgo(){}
        double GetStatistic() override
        {
            return m_algo->statistic();
        }
        void Show() override
        {
            m_algo->show();
        }

    CorPtr<Algo> m_algo;
};

CorPtr<IURTAlgo> URTWrap::Create(const EnjoLib::VecD & data, int lags) const
{
    return CorPtr<IURTAlgo>(new URTAlgo(data, lags));
}

#else
#include <Util/CoutBuf.hpp>

double URTWrap::GetStatistic(const EnjoLib::VecD & data, int lags) const
{
    std::cout << "URTWrap::GetStatistic() not compiled in" << std::endl;
    return 0;
}

void URTWrap::Show(const EnjoLib::VecD & data, int lags) const
{
    std::cout << "URTWrap::Show() not compiled in" << std::endl;
}
#endif
