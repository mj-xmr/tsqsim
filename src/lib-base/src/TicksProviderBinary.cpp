#include "TicksProviderBinary.h"
#include "TicksProviderFake.h"
#include "SerializationSpec.h"
#include "TicksFilesExt.h"
#include "Ticks.h"
////#include "ConfigGlob.h"
#include "ConfigSym.h"

#include <EnjoLibBoost/Zipping.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/FileUtils.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Except.hpp>
#include <Util/CoutBuf.hpp>
#include <Visual/AsciiAnimation.hpp>
#include <Util/ProgressMonitHigh.hpp>
#include <Ios/Osstream.hpp>
#include <Ios/Sstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Ios/Cout.hpp>

using namespace std;
using namespace EnjoLib;

TicksProviderBinary::TicksProviderBinary(){}
TicksProviderBinary::~TicksProviderBinary(){}

CorPtr<ITicks> TicksProviderBinary::GetTicks(const EnjoLib::Str & symbol, const ConfigSym * confSym) const
{
    if (confSym == NULL)
    {
        //return TicksProviderFake().GetTicks(symbol);
        return StoreOrRestore(symbol, symbol);
    }
    else
    {
        Ticks ret;
        for (int y = confSym->dates.yearStart; y <= confSym->dates.yearEnd; ++y)
        {
            int mStart = 1;
            int mEnd = 12;
            if (y == confSym->dates.yearStart)
            {
                mStart = confSym->dates.monthStart;
            }
            if (y == confSym->dates.yearEnd)
            {
                mEnd = confSym->dates.monthEnd;
            }

            for (int m = mStart; m <= mEnd; ++m)
            {
                Osstream ossFileName;
                ossFileName << symbol << "-" << y << "-" << m;
                ret.Add(*StoreOrRestore(symbol, ossFileName.str()));
            }
        }
        return CorPtr<ITicks>(new Ticks(ret));
    }
}

CorPtr<ITicks> TicksProviderBinary::GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const
{
    return StoreOrRestore(symbolName, symbolName + '-' + periodName);
}

void TicksProviderBinary::Archive(const EnjoLib::Str & symbol, const Ticks & t) const
{
    /// TODO: tu moze byc synchronized queue i serializacja w drugim watku, ktory zbiera z kolejki
    ELO
    LOG << symbol << ": Archiving" << Endl;
    { // save data to archive
        // gzipped:
        //SerializationSpec().ArchiveZipped(serializedFileName, t);
        Ticks toStore;
        for (const Tick & tick : t)
        {
            const auto & currentTicks = toStore.GetTicks3();
            if (!currentTicks.empty())
            {
                const Tick & lastTick = currentTicks.back();
                if (lastTick.month != tick.month)
                {
                    ArchiveTickMonth(symbol, toStore, false);
                    toStore = Ticks();
                }
            }
            toStore.Add(tick);
        }
        ArchiveTickMonth(symbol, toStore, true);
    }
}

void TicksProviderBinary::ArchiveTickMonth(const EnjoLib::Str & symbol, const Ticks & ticks, bool isEndl) const
{
    Cout out;
    Osstream ossFileName;
    const Tick & tick = ticks.GetTicks3().at(ticks.GetTicks3().size() - 1);
    ossFileName << symbol << "-" << int(tick.year) << "-" << int(tick.month);
    const TicksFilesExt tfx(symbol, ossFileName.str());
    Osstream oss;
    static int m_prevStringSize = 0;
    oss << "Archiving " << tfx.binZipFile;
    //if (! isEndl) // was wrong!
    {
        /// TODO: Similar in EnjoLib::ProgressMonitHigh

        for (int i = 0; i < m_prevStringSize; ++i)
            out << '\b'; // Move back
        for (int i = 0; i < m_prevStringSize; ++i)
            out << ' ';  // Erase by filling with spaces
        for (int i = 0; i < m_prevStringSize; ++i)
            out << '\b'; // Move back again for the next printout
    }
    out << oss.str();
    if (isEndl)
    {
        out << Endl;
    }
    else
    {
       out.Flush();
    }
    m_prevStringSize = oss.str().size();

    SerializationSpec().ArchiveZipped(tfx.binZipFile, ticks);
}

CorPtr<ITicks> TicksProviderBinary::RestoreZipped(const EnjoLib::Str & serializedFileName) const
{
    //cout << "Restoring '" << serializedFileName << "'" << endl;
    // ... some time later restore the class instance to its orginal state
    const Ticks & t2 = SerializationSpec().RestoreZipped(serializedFileName);
    //return t2.FromYear(2010).TillYear(2010);
    //return t2.FromYear(2015).TillYear(2015).FromMonth(5, 2015);
    //return t2.FromYear(2015).TillYear(2015).TillMonth(5, 2015);
    //return t2.FromYear(2015).TillYear(2015).FromMonth(1, 2015).TillMonth(6, 2015);
    return CorPtr<ITicks>(new Ticks(t2));

}

CorPtr<ITicks> TicksProviderBinary::Restore(const EnjoLib::Str & serializedFileName) const
{
    Cout out;
    out << "Restoring '" << serializedFileName << "'" << Endl;
    // ... some time later restore the class instance to its orginal state
    const Ticks & t2 = SerializationSpec().Restore(serializedFileName);
    return CorPtr<ITicks>(new Ticks(t2));;
}

CorPtr<ITicks> TicksProviderBinary::StoreOrRestore(const EnjoLib::Str & symbol, const EnjoLib::Str & fileName) const
{
    const TicksFilesExt tfx(symbol, fileName);
    const FileUtils fu;
    if (fu.FileExists(tfx.binaryFile))
    {
        return Restore(tfx.binaryFile);
    }
    else if (fu.FileExists(tfx.binZipFile))
    {
        return RestoreZipped(tfx.binZipFile);
    }
    else if (fu.FileExists(tfx.textFile))
    {
        Ifstream ifs(tfx.textFile);
        const auto & ticks = ReadFile(fileName, ifs); /// TODO: Join with UnzipTxt(). Used for Windows for now.
        Archive(fileName, ticks);
        return CorPtr<ITicks>(new Ticks(ticks));
    }
    else if (fu.FileExists(tfx.txtZipFile))
    {
        return UnzipTxt(symbol, fileName, tfx.txtZipFile);
    }
    else if (fu.FileExists(tfx.txtGZipFile))
    {
        return UnzipTxt(symbol, fileName, tfx.txtGZipFile);
    }
    else
    {
        throw ExceptInvalidArg("File " + tfx.txtGZipFile + " doesn't exist");
    }
}

CorPtr<ITicks> TicksProviderBinary::UnzipTxt(const EnjoLib::Str & symbol, const EnjoLib::Str & fileName, const EnjoLib::Str & txtFileName) const
{
    Cout out;
    out << symbol << ": Unzipping file '" << txtFileName << "'" << Endl;
    Sstream sstream;
    EnjoLibBoost::Zipping().UnzipFile(txtFileName, sstream);
    const auto & ticks = ReadFile(fileName, sstream);
    Archive(fileName, ticks);
    return CorPtr<ITicks>(new Ticks(ticks));
}

Ticks TicksProviderBinary::ReadFile(const EnjoLib::Str & symbolName, EnjoLib::Istream & is) const
{
    Cout out;
    out << symbolName << ": Reading file ... " << Endl;
    //const size_t szz = FileUtils().GetNumLinesFile(is);
    class Worker : public EnjoLib::IWorksOnLine
    {
    public: 
        Worker(const TicksProviderBinary & parent)
        : m_parent(parent)
        , m_anim(11111)
        {
            
        }
        void Work(const EnjoLib::Str & line) override
        {
            static int idx = 0;
            if (idx++ == 0)
            {
                return; // Skip the 1st line
            }
            const EnjoLib::Str & lineConv = m_parent.ConvertSingle(line);
            
            //m_anim.AnimationPropeller(&idx);
            //m_pmon.PrintProgressBarTime(idx++, m_szz);
            if (idx % 50000 == 0)
            {
                LOGL << lineConv << Nl;
            }
            Tick tick(lineConv);
            m_ticks.Add(tick);
        }
        const TicksProviderBinary & m_parent;
        
        Ticks m_ticks;
        Str m_lastDate;
        EnjoLib::AsciiAnimation m_anim;
        EnjoLib::ProgressMonitHigh m_pmon;
    };
    //const VecStr & lines = Tokenizer().GetLines(is, true);
    Worker worker(*this);
    Tokenizer().WorkOnLines(is, worker, true);
    
    out << symbolName << ": " << worker.m_ticks.size() << " lines.\n";
    //out << symbolName << ": Tokenizing..." << Endl;
    //Ticks t(is, sz);
    //const VecStr & linesConv = Convert(lines);
    //Ticks t(symbolName, linesConv);
    out << symbolName << ": Filtering" << Endl;

    //t = t.FromYear(2010);
    //t = t.FromMonth(8);
    return worker.m_ticks;
}

VecStr TicksProviderBinary::Convert(const VecStr & lines) const
{
    return lines;
}

EnjoLib::Str TicksProviderBinary::ConvertSingle(const EnjoLib::Str & line) const
{
    return line;
}

