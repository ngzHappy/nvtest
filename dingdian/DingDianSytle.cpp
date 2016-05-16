/*DingDianSytle cpp*/
#include "DingDianSytle.hpp"
#include "private/DingDianSytleData.hpp"
#include "private/DingDianSytlePrivateFunction.hpp"
#include <lua/lua.hpp>
#include "LuaPreBuild.hpp"

namespace {
namespace zone_data_ {
LuaPreBuild::Item lua_functions[]{
u8R"(return function() print("Hellow Word!") end    )"_lua_prebuild, };
}/*~zone_data_*/
}

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::DingDianSytleData *,0>(const DingDianSytle * arg) ->zone_data::DingDianSytleData *{
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
                         [](zone_data::DingDianSytleData *arg){delete arg;})) {
}

DingDianSytle::~DingDianSytle() {
}

auto DingDianSytle::instance()->std::shared_ptr<DingDianSytle>{
    static auto varAns=std::shared_ptr<DingDianSytle>(
        new DingDianSytle,
        [](DingDianSytle * arg) {delete arg; });
    return varAns;
}

/*zone_namespace_end*/


