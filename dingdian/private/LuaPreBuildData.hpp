/*LuaPreBuild hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_LUAPREBUILD_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_LUAPREBUILD_0__0x00() 1

#include <memory>
#include <lua/lua.hpp>

/*zone_namespace_begin*/

namespace zone_data{

class LuaPreBuildData  {
public:
    LuaPreBuildData();
    ~LuaPreBuildData();

    lua_State*L;

};

}

/*zone_namespace_end*/

#endif

