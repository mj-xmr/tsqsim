#include "LabelML.h"
#include <Util/ProtocolCreator.h>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulationsTpl.hpp>



using namespace std;
using namespace EnjoLib;

LabelML::~LabelML(){}
LabelML::LabelML(DateInt date)
: date(date)
{
    static int nextId = 0;
    m_id = nextId++;
}

VecD LabelML::GetFlatObserv4Mask(const Mask & mask) const
{
    return observs.FilterByMaskD(mask).Flatten(); // Somehow faster

    /*
    const auto it = m_cache4Mask.find(mask);
    if (it != m_cache4Mask.end())
    {
        return it->second;
    }
    else
    {
        const VecD & obsFlat = observs.FilterByMask(mask).Flatten();
        m_cache4Mask[mask] = obsFlat;
        return obsFlat;
    }
    */
}

int LabelML::GetId() const
{
    return m_id;
}

DateInt LabelML::GetDate() const
{
    return date;
}

void LabelML::SetDate(DateInt pistate)
{
    date = pistate;
}

EnjoLib::Str LabelML::ToStr() const
{
     //EnjoLib::Matrix observs;
       // EnjoLib::VecD targets;
    ProtocolCreator pcc(SEP);
    pcc.AddInt64(date);
    //cout << "Storing LabelML = " << pcc.Get() << endl;
    pcc.AddStr(observs.ToStr());
    pcc.AddStr(targets.ToStr());
    
    return pcc.Get();
}

void LabelML::FromStr(const EnjoLib::Str & data)
{
    const Tokenizer tok;
    const auto & tokens = tok.Tokenize(data, SEP);
    int i = 0;
    
    date = CharManipulationsTpl().ToNumber<DateInt>(tokens.at(i++));
    observs.FromStr(tokens.at(i++));
    targets = VecD(tokens.at(i++));
}
