#ifndef LOGIC_H
#define LOGIC_H

namespace EnjoLib
{
    class VecD;    
}

class State;

class Logic
{
    public:
        Logic();
        virtual ~Logic();
        static bool GT(double a, double b, const State & st); // Is Greater Than
        static bool LT(double a, double b, const State & st); // Is Less Than
        static bool GTE(double a, double b, const State & st); // Is Greater Than or Equal
        static bool LTE(double a, double b, const State & st); // Is Less Than or Equal
        static bool In(double a, double between, double c);
        static double Sub(double a, double b, const State & st);
        static double Add(double a, double b, const State & st);
        
        static bool VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2, double eps = 0);
        static bool DoublesEqual(const double data1, const double, double eps = 0);
    protected:
    private:
        static void Swp(double & a, double & b, const State & st);
};

#endif // UTIL_H
