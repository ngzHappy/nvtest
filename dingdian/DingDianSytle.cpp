/*DingDianSytle cpp*/
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include "DingDianSytle.hpp"
#include "private/DingDianSytleData.hpp"
#include "private/DingDianSytlePrivateFunction.hpp"
#include <lua/lua.hpp>
#include "LuaPreBuild.hpp"

namespace {
namespace zone_data_ {
enum {
    Test_=0,
    Style_Font_PixSize,
    Style_Font_Color_Red,
    Style_Font_Color_Green,
    Style_Font_Color_Blue,
    Style_Font_Color_Alpha,
    Style_StyleSheet,
};
LuaPreBuild::Item lua_functions[]{
u8R"(return function() print("Hellow Word!") end    )"_lua_prebuild,
u8R"(return function() return style.font.pixsize end    )"_lua_prebuild,
u8R"(return function() return style.font.color[1] end    )"_lua_prebuild,
u8R"(return function() return style.font.color[2] end    )"_lua_prebuild,
u8R"(return function() return style.font.color[3] end    )"_lua_prebuild,
u8R"(return function() return style.font.color[4] end    )"_lua_prebuild,
u8R"(return function() return style.styleSheet end    )"_lua_prebuild,
};
}/*~zone_data_*/
}

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::DingDianSytleData *,0>(const DingDianSytle * arg) ->zone_data::DingDianSytleData * {
    return const_cast<DingDianSytle *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::DingDianSytleData *,1>(const DingDianSytle * arg) ->const zone_data::DingDianSytleData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::DingDianSytleData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::DingDianSytleData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
DingDianSytleData::DingDianSytleData() {
    L=luaL_newstate();
    luaL_openlibs(L);
}


DingDianSytleData::~DingDianSytleData() {
    lua_close(L);
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

DingDianSytle::DingDianSytle():thisData_(ThisDataType(
    new zone_data::DingDianSytleData,
    [](zone_data::DingDianSytleData *arg) {delete arg; })) {
}

DingDianSytle::~DingDianSytle() {
}

auto DingDianSytle::instance()->std::shared_ptr<DingDianSytle> {
    static auto varAns=std::shared_ptr<DingDianSytle>(
        new DingDianSytle,
        [](DingDianSytle * arg) {delete arg; });
    return varAns;
}

void DingDianSytle::loadFile(const QString &arg) {
    QFile varFile{arg};
    if (varFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream stream_{&varFile};
        loadString(stream_.readAll());
    }
}

namespace {
class Lua_Lock {
    lua_State*L;
    int top_;
public:
    Lua_Lock(lua_State*s):L(s) {
        top_=lua_gettop(L);
    }
    ~Lua_Lock() { lua_settop(L,top_); }
};
}

void DingDianSytle::loadString(const QString &arg) {
    const auto varFile=arg.toUtf8()+"\r\n     ";
    zone_this_data(this);
    Lua_Lock argLock{var_this_data->L};
    luaL_dostring(var_this_data->L,varFile.data());
    styleChanged();
}

double DingDianSytle::fontPixSize()const {
    zone_const_this_data(this);
    Lua_Lock argLock{var_this_data->L};
    if (zone_data_::lua_functions[zone_data_::Style_Font_PixSize].call(
        var_this_data->L
        )==LUA_OK) {
        int varIsNum;
        double varAns=lua_tonumberx(var_this_data->L,-1,&varIsNum);
        if (varIsNum) { return varAns; }
    }
    return 30;
}

QColor DingDianSytle::fontColor()const{
    zone_const_this_data(this);
    double r,g,b,a;
    int varIsNum;
    Lua_Lock argLock{var_this_data->L};
    try {
        if (zone_data_::lua_functions[zone_data_::Style_Font_Color_Red].call(
            var_this_data->L
            )==LUA_OK) {
            r=lua_tonumberx(var_this_data->L,-1,&varIsNum);
            if (varIsNum<=0) { throw nullptr; }
        }
        else { throw nullptr; }
        if (zone_data_::lua_functions[zone_data_::Style_Font_Color_Green].call(
            var_this_data->L
            )==LUA_OK) {
            g=lua_tonumberx(var_this_data->L,-1,&varIsNum);
            if (varIsNum<=0) { throw nullptr; }
        }
        else { throw nullptr; }
        if (zone_data_::lua_functions[zone_data_::Style_Font_Color_Blue].call(
            var_this_data->L
            )==LUA_OK) {
            b=lua_tonumberx(var_this_data->L,-1,&varIsNum);
            if (varIsNum<=0) { throw nullptr; }
        }
        else { throw nullptr; }
        if (zone_data_::lua_functions[zone_data_::Style_Font_Color_Alpha].call(
            var_this_data->L
            )==LUA_OK) {
            a=lua_tonumberx(var_this_data->L,-1,&varIsNum);
            if (varIsNum<=0) { throw nullptr; }
        }
        else { throw nullptr; }

        return QColor{int(r),int(g),int(b),int(a)};
    }
    catch (...) {
        return QColor(0,0,0,255);
    }
}

QString DingDianSytle::styleSheet()const {
    zone_const_this_data(this);
    Lua_Lock argLock{var_this_data->L};
    if (zone_data_::lua_functions[zone_data_::Style_StyleSheet].call(
        var_this_data->L
        )==LUA_OK) {
        size_t varLen;
        const char *varTempAns=luaL_tolstring(var_this_data->L,-1,&varLen);
        if (varLen>0) { 
            return QString::fromUtf8(varTempAns,varLen);
        }
    }
    return QString::fromUtf8(u8R"(MainWindow{
background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
stop: 0 rgb(173,155,52), 
stop: 0.4 rgb(170,146,60),
stop: 0.8 rgb(168,150,55), 
stop: 1.0 rgb(171,146,53));
}

)");

}

/*zone_namespace_end*/


