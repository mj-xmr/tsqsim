#ifndef ISERVER_RECEIVER_H
#define ISERVER_RECEIVER_H

#include <Util/Str.hpp>

class IServerReceiver
{
    public:
	virtual ~IServerReceiver(){}
	virtual EnjoLib::Str NotifyGetResult(const EnjoLib::Str & message) = 0;
	
	static const unsigned SZ_BUF;

    protected:
    private:
};

#endif
