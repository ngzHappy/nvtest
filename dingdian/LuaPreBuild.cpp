/*LuaPreBuild cpp*/
#include "LuaPreBuild.hpp"
#include "private/LuaPreBuildData.hpp"
#include "private/LuaPreBuildPrivateFunction.hpp"

#if defined(QT_CORE_LIB)
#include <QtCore/qdebug.h>
#else
#include <iostream>
#endif

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::LuaPreBuildData *,0>(const LuaPreBuild * arg) ->zone_data::LuaPreBuildData * {
    return const_cast<LuaPreBuild *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::LuaPreBuildData *,1>(const LuaPreBuild * arg) ->const zone_data::LuaPreBuildData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::LuaPreBuildData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::LuaPreBuildData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
LuaPreBuildData::LuaPreBuildData() {
    L=luaL_newstate();
    luaL_openlibs(L);
}


LuaPreBuildData::~LuaPreBuildData() {
    lua_close(L);
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

LuaPreBuild::LuaPreBuild():thisData_(ThisDataType(
    new zone_data::LuaPreBuildData,
    [](zone_data::LuaPreBuildData *arg) {delete arg; })) {
}

LuaPreBuild::~LuaPreBuild() {
}

void LuaPreBuild::build(Item&arg) {
    if (arg.bin) { return; }
    if (arg.data==nullptr) { return; }
    if (arg.length<=0) { return; }
    static auto varThis=std::shared_ptr<LuaPreBuild>(
                new LuaPreBuild,
                [](auto *arg) {delete arg; });

    try {
        varThis->preBuild(arg);
    }
    catch (const BuildException&e) {
#if defined(QT_CORE_LIB)
        qDebug()<<e.what();
#else
        std::cout<<e.what()<<std::endl;
        std::cout.flush();
#endif
    }
}

namespace {
class LuaPreBuildLock {
    lua_State*L;
    int top_;
public:
    LuaPreBuildLock(lua_State*s):L(s) {
        top_=lua_gettop(L);
    }
    ~LuaPreBuildLock() { lua_settop(L,top_); }
};
}

int LuaPreBuild::call(lua_State*L,const Item&arg,int argSize) {
    enum { Error_Code=-1999 };
    if (L==nullptr) { return Error_Code; }
    if (bool(arg.bin)==false) {
        return Error_Code;
    }
    auto varError=luaL_loadbuffer(L,arg.bin->data(),arg.bin->size(),"?!");
    if (LUA_OK==varError) {
        if (lua_isfunction(L,-1)) {
            return lua_pcall(L,argSize,LUA_MULTRET,0);
        }
        else { return 0/*just load something??*/; }
    }
    else { return varError; }
}

int LuaPreBuild::call(lua_State*L,Item&arg,int argSize) {
    enum { Error_Code=-1999 };
    if (L==nullptr) { return Error_Code; }
    if (bool(arg.bin)==false) {
        build(arg);
        if (bool(arg.bin)==false) {
            return Error_Code;
        }
    }
    auto varError=luaL_loadbuffer(L,arg.bin->data(),arg.bin->size(),"?!");
    if (LUA_OK==varError) {
        if (lua_isfunction(L,-1)) {
            return lua_pcall(L,argSize,LUA_MULTRET,0);
        }
        else { return 0/*just load something??*/; }
    }
    else { return varError; }
}

/*return function() print("abcd") end*/
void LuaPreBuild::preBuild(Item&arg) {
    zone_this_data(this);
    LuaPreBuildLock argLock{ var_this_data->L };
    if (LUA_OK==luaL_loadbuffer(var_this_data->L,arg.data,arg.length,"?!")) {
        if (LUA_OK==lua_pcall(var_this_data->L,0,LUA_MULTRET,0)) {
            if (lua_isfunction(var_this_data->L,-1)) {
                arg.bin=std::make_shared<std::vector<char>>();
                auto lua_writer_function=[](lua_State *L,
                    const void* p,
                    size_t sz,
                    void* ud)->int {
                    if (sz<=0) { return 0; }
                    auto varItem=reinterpret_cast<Item*>(ud);
                    auto varData=reinterpret_cast<const char *>(p);
                    for (size_t varI=0; varI<sz; ++varI) {
                        varItem->bin->push_back(*varData);
                        ++varData;
                    }
                    return 0; (void)L;
                };
                if (
                    lua_dump(var_this_data->L,
                    lua_writer_function,
                    &arg,true)==0) {
                    return;
                }
                else {
                    arg.bin.reset();
                    throw BuildException(std::string("unkow error:dump error?"));
                }
            }
            else {
                throw BuildException(std::string("unkow error:is not a function?"));
            }
        }
        else {
            std::size_t varLen;
            auto * varError=luaL_tolstring(var_this_data->L,-1,&varLen);
            throw BuildException(std::string(varError,varLen));
        }
    }
    else {
        std::size_t varLen;
        auto * varError=luaL_tolstring(var_this_data->L,-1,&varLen);
        throw BuildException(std::string(varError,varLen));
    }

}

/*zone_namespace_end*/


