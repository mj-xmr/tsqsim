#ifndef REGOPTIBASE_H
#define REGOPTIBASE_H

class RegressionPars;

class RegOptiBase
{
    public:
        RegOptiBase();
        virtual ~RegOptiBase(){}

        int GetPast(const RegressionPars & reg) const;
        int GetPast(int future) const;
        bool IsValid() const;

    protected:
        virtual int GetDiffPastFuture() const = 0;

    private:
};

#endif // REGOPTIBASE_H
