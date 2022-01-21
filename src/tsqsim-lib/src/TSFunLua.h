#ifndef TSFUNLUA_H
#define TSFUNLUA_H

#include "TSFunBase.h"

struct lua_State;

class TSFunLua : public TSFunBase
{
    public:
        TSFunLua(const TSInput & tsin);
        virtual ~TSFunLua();

        const char * GetName() const override { return "TSFunLua"; }

    protected:
        TSRes OnDataPointProt(int idx) const override;
        //TSRes Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const override;
        EnjoLib::VecD ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const override;

    private:
        // create new Lua state
        lua_State *lua_state;
};

#endif // TSFUNLUA_H
