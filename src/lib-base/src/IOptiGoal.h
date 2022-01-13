#ifndef IOPTIGOAL_H
#define IOPTIGOAL_H

class ProfitsCalc;

class IOptiGoal
{
    public:
        IOptiGoal();
        virtual ~IOptiGoal();
        
        virtual float GetGoal(const ProfitsCalc & profits) const = 0;
        bool IsGoalReached(const ProfitsCalc & profits, float previous) const;

    protected:

    private:
};

#endif // IOPTIGOAL_H
