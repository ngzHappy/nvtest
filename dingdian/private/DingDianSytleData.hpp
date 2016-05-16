/*DingDianSytle hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_DINGDIANSYTLE_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_DINGDIANSYTLE_0__0x00() 1

#include <memory>
#include <lua/lua.hpp>

/*zone_namespace_begin*/

namespace zone_data{

class DingDianSytleData  {
public:
    DingDianSytleData();
    ~DingDianSytleData();

    lua_State * L;
};

}

/*zone_namespace_end*/

#endif

