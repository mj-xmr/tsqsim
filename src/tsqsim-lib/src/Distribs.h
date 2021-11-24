#ifndef DISTRIBS_H
#define DISTRIBS_H

namespace EnjoLib
{
    class StdDev;
}

class Distribs
{
    public:
        Distribs();
        virtual ~Distribs(){}

        double NormalPDF(double mean, const EnjoLib::StdDev & stdDev, double arg) const;

    protected:

    private:
};

#endif // DISTRIBS_H
