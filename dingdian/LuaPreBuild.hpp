/*LuaPreBuild hpp*/
#if !defined(____PRAGMA_ONCE_HPP_LUAPREBUILD_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_LUAPREBUILD_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <vector>
#include <stdexcept>

struct lua_State;
/*zone_namespace_begin*/

namespace zone_data {
class LuaPreBuildData;
}
class LuaPreBuild;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const LuaPreBuild *)->_TYPE_TAG_;

class LuaPreBuild {
    /*macro_no_copy(LuaPreBuild);*/
protected:
    using ThisDataType=std::unique_ptr<zone_data::LuaPreBuildData,void(*)(zone_data::LuaPreBuildData *)>;
    ThisDataType thisData_{ nullptr,nullptr };
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const LuaPreBuild *)->_TYPE_TAG_;
public:
    explicit LuaPreBuild(decltype(nullptr)) {}
    LuaPreBuild();

    class Item {
    public:
        const char * data=nullptr;
        std::size_t length=0;
        std::shared_ptr<std::vector<char>>bin;
        Item() {}
        Item(const char *arg_d,std::size_t arg_l):data(arg_d),length(arg_l) {}
    };

    class BuildException :public std::logic_error {
        using BP=std::logic_error;
    public:
        using BP::BP;
    };

    static void build(Item&)noexcept(false)/*BuildException*/;
    static int call(lua_State*,Item&,int argSize=0)noexcept(false)/*BuildException*/;
protected:
    ~LuaPreBuild();
    void preBuild(Item&);
};

/*return function() print("Hellow Word!") end */
inline LuaPreBuild::Item operator""_lua_prebuild_item(const char * arg0,std::size_t arg1) {
    return LuaPreBuild::Item{ arg0,arg1 };
}

inline LuaPreBuild::Item operator""_lua_prebuild(const char * arg0,std::size_t arg1) {
    LuaPreBuild::Item var{ arg0,arg1 };
    LuaPreBuild::build(var);
    return std::move(var);
}
/*zone_namespace_end*/

#endif



