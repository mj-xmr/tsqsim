#ifndef TSINPUT_H
#define TSINPUT_H

class IPeriod;
class ConfigTS;

class TSInput
{
    public:
        TSInput(const IPeriod & per, const ConfigTS & cfgTS);
        virtual ~TSInput();
        
        const IPeriod & m_per;
        const ConfigTS & m_cfgTS;

    protected:

    private:
        
};

#endif // TSINPUT_H
