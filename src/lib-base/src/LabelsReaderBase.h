#ifndef LABELSREADERBASE_H
#define LABELSREADERBASE_H

//#include <vector>
#include "typesStr.h"
#include <Template/SafePtr.hpp>
#include <Template/Array.hpp>
#include <Util/Pair.hpp>
#include <3rdParty/stdfwd.hh>

struct LabelsReaderBaseImpl;
class LabelsReaderBase
{
    public:
        LabelsReaderBase(const EnjoLib::Str & filePath);
        virtual ~LabelsReaderBase();

        EnjoLib::Array<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> GetSymPer() const;
        VecStr GetUniquePeriods() const;
        VecStr GetUniqueSymbols() const;

    protected:
        virtual int GetSymbolIndex() const = 0;
        virtual int GetPeriodIndex() const = 0;
        VecStr GetFileContents() const;

        EnjoLib::Str m_filePath;
        
        

        static const char delim = '|';
    private:
        EnjoLib::SafePtr<LabelsReaderBaseImpl> m_impl;
};

#endif // LABELSREADERBASE_H
