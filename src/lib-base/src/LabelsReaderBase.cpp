#include "LabelsReaderBase.h"

#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/StackTrace.hpp>
#include <Util/FileUtils.hpp>
#include <STD/VectorCpp.hpp>


using namespace std;
using namespace EnjoLib;

#include <STD/Set.hpp>

struct LabelsReaderBaseImpl
{
    LabelsReaderBaseImpl(const EnjoLib::Str & filePath)
    : m_fileContents(Tokenizer().GetLines(filePath))
    {
        
    }
    VecStr m_fileContents;
};

LabelsReaderBase::~LabelsReaderBase(){}
LabelsReaderBase::LabelsReaderBase(const EnjoLib::Str & filePath)
: m_filePath(filePath)
, m_impl(new LabelsReaderBaseImpl(m_filePath))
{
}

VecStr LabelsReaderBase::GetFileContents() const
{
    return m_impl->m_fileContents;
}

VecStr LabelsReaderBase::GetUniquePeriods() const
{
    set<EnjoLib::Str> ret;
    Tokenizer tok;
    for (const Str & l : GetFileContents())
    {
        if (l.empty())
            continue;
        const VecStr & tokenized = tok.Tokenize(l, delim);
        const Str period = tokenized.at(GetPeriodIndex());
        ret.insert(period);
    }
    VecStr ret2;
    for (auto s : ret)
        ret2.push_back(s);
    return ret2;
}
VecStr LabelsReaderBase::GetUniqueSymbols() const
{
    set<EnjoLib::Str> ret;
    Tokenizer tok;
    for (const Str & l : GetFileContents())
    {
        if (l.empty())
            continue;
        const VecStr & tokenized = tok.Tokenize(l, delim);
        const Str symbol = tokenized.at(GetSymbolIndex());
        ret.insert(symbol);
    }
    VecStr ret2;
    for (auto s : ret)
        ret2.push_back(s);
    return ret2;
}

EnjoLib::Array<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> LabelsReaderBase::GetSymPer() const
{
    set<EnjoLib::Str> sett;
    Tokenizer tok;
    for (const Str & l : GetFileContents())
    {
        if (l.empty())
            continue;
        const VecStr & tokenized = tok.Tokenize(l, delim);
        const Str symbol = tokenized.at(GetSymbolIndex());
        const Str period = tokenized.at(GetPeriodIndex());
        sett.insert(symbol + delim + period);
    }
    vector<Pair<EnjoLib::Str, EnjoLib::Str>> ret;
    for (const EnjoLib::Str & entry : sett)
    {
        const VecStr & tokenized = tok.Tokenize(entry, delim);
        ret.push_back(EnjoLib::MakePair(tokenized.at(0), tokenized.at(1)));
    }
    return ret;
}
