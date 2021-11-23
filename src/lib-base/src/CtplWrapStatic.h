#ifndef CPTLWRAPSTATIC_H
#define CPTLWRAPSTATIC_H


class CtplWrapStatic
{
    public:
        CtplWrapStatic();
        virtual ~CtplWrapStatic();
        
        void SetSingle();
        void SetMT(bool mtt);
        void SetReversed();
        void SetNumCores(short numCores);
        
        bool IsMT() const;
        bool IsReversed() const;
        short GetNumCores() const;

    protected:

    private:
        bool m_single = false;
        bool m_reversed = false;
        short m_numCores = 1;
};

#endif // CPTLWRAPSTATIC_H
