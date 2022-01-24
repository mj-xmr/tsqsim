#ifndef MATPLOTLINE_H
#define MATPLOTLINE_H

#include <Util/Str.hpp>
#include <Util/VecD.hpp>
#include <STD/Vector.hpp>

class MatplotLine
{
    public:
        MatplotLine();
        virtual ~MatplotLine();

        void Plot(const EnjoLib::Str & title = "") const;
        void AddLine(const EnjoLib::VecD & line, const EnjoLib::Str & descr, const EnjoLib::Str & colour = "");

    protected:

    private:
        struct Data
        {
            EnjoLib::VecD data;
            EnjoLib::Str descr;
            EnjoLib::Str colour;
        };
        std::vector<Data> m_dat;
};

#endif // MATPLOTLINE_H
