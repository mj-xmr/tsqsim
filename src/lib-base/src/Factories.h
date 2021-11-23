#ifndef FACTORIESABSTRACT_HPP
#define FACTORIESABSTRACT_HPP

namespace EnjoLib
{
    class EigenFactoryAbstract;
}

class StrategyFactoryAbstract;

class Factories
{
    public:
        Factories();
        virtual ~Factories();
        
        virtual const StrategyFactoryAbstract & GetStrat() const = 0;
        virtual const EnjoLib::EigenFactoryAbstract & GetEigen() const = 0;
    protected:

    private:
        
};

#endif // FACTORIESABSTRACT_HPP
