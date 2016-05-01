/*DingDianProcess cpp*/
#include "DingDianProcess.hpp"
#include "private/DingDianProcessData.hpp"
#include "private/DingDianProcessPrivateFunction.hpp"

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::DingDianProcessData *,0>(const DingDianProcess * arg) ->zone_data::DingDianProcessData *{
    return const_cast<DingDianProcess *>(arg)->thisData_.get(); 
}

template<>
inline auto getThisData<const zone_data::DingDianProcessData *,1>(const DingDianProcess * arg) ->const zone_data::DingDianProcessData *{ 
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::DingDianProcessData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::DingDianProcessData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
DingDianProcessData::DingDianProcessData() {
}


DingDianProcessData::~DingDianProcessData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

DingDianProcess::DingDianProcess():thisData_(ThisDataType(
                         new zone_data::DingDianProcessData,
                         [](zone_data::DingDianProcessData *arg){delete arg;})) {
}

DingDianProcess::~DingDianProcess() {
}

/*zone_namespace_end*/


