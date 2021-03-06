#include "TSFunLua.h"

#include "Candle.h"
//#include "IBufferCandles.h"
#include "ConfigTS.h"

#include <Util/FileUtils.hpp>
#include <Util/CoutBuf.hpp>
#include <Math/GeneralMath.hpp>
#include <Statistical/Assertions.hpp>

#ifdef USE_LUA
    #include <lua.hpp>
#endif // USE_LUA

using namespace EnjoLib;

TSFunLua::TSFunLua(const TSInput & tsin)
: TSFunBase(tsin)
//, lua_state(luaL_newstate())
{
#ifdef USE_LUA
    lua_state(luaL_newstate())
    // load Lua libraries
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(lua_state);
        lua_settop(lua_state, 0);
    }

    // run the Lua script
    const char * striptName = "helloworld.lua";
    if (not FileUtils().FileExists(striptName))
    {
        const Str mesage = Str(striptName) + " - not found ";
        Assertions::Throw(mesage.c_str(), "TSFunLua::TSFunLua()");
    }
    if (luaL_dofile(lua_state, striptName))
    {
        LOGL << "Couldn't load " << striptName << Nl;
    }
    else
    {
        LOGL << "Loaded " << striptName << Nl;
    }
#endif // USE_LUA
}

TSFunLua::~TSFunLua()
{
#ifdef USE_LUA
    // close the Lua state
    lua_close(lua_state);
#endif // USE_LUA
}

TSRes TSFunLua::OnDataPointProt(int idx) const
{
    const GMat gmat;

    const Candle & canCurr = GetCandle0Based(idx);
    const Candle & canPrev = GetCandle0Based(idx - 1);

    
    const double ret = gmat.Fabs(canCurr.GetPriceByType(GetTSIn().m_cfgTS.GetPriceType()) - canPrev.GetPriceByType(GetTSIn().m_cfgTS.GetPriceType()));

    TSRes res(true);
    res.val = ret;

    return res;
}

EnjoLib::VecD TSFunLua::ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const
{
    return EnjoLib::VecD();
}

/*
TSRes TSFunLua::Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const
{
    TSRes res(true);
    return res;
}
*/