#ifndef SCREENSHOTSSCALEUP_H
#define SCREENSHOTSSCALEUP_H

#include <Util/Str.hpp>
#include <3rdParty/stdfwd.hh>

class MyMainWindow;

class ScreenshotsScaleUp
{
    public:
        ScreenshotsScaleUp(){}
        virtual ~ScreenshotsScaleUp(){}

        void Handle(MyMainWindow * win, int mode, const EnjoLib::Str & screenShotSymbol,
                    const EnjoLib::Str & ssPeriod, const EnjoLib::Str & ssOutDir, const EnjoLib::Str & dataInputFileName) const;
    protected:

    private:
        void SavePNG(QCustomPlot * p, const EnjoLib::Str & path, int w, int h) const;
        STDFWD::vector<EnjoLib::Str> GetPeriods(const EnjoLib::Str & periodName) const;
};

#endif // SCREENSHOTSSCALEUP_H
