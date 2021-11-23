#ifndef LABELML_H2
#define LABELML_H2

#include "typesVec.h"

#include <Util/VecD.hpp>
#include <Statistical/Matrix.hpp>



class LabelML
{
    public:
        LabelML(DateInt date = 0);
        virtual ~LabelML();

        EnjoLib::Matrix observs;
        EnjoLib::VecD targets;

        EnjoLib::VecD GetFlatObserv4Mask(const Mask & mask) const;

        int GetId() const;
        DateInt GetDate() const;
        void SetDate(DateInt date);
        
        EnjoLib::Str ToStr() const;
        void FromStr(const EnjoLib::Str & data);

    protected:

    private:
        static const char SEP = 'L';
        int m_id = 0;
        DateInt date = 0;
        //mutable std::map<VecB, EnjoLib::VecD> m_cache4Mask;
};

#endif // LABELML_H
