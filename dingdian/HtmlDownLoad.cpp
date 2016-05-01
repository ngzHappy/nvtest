/*HtmlDownLoad cpp*/
#include "HtmlDownLoad.hpp"
#include "private/HtmlDownLoadData.hpp"
#include "private/HtmlDownLoadPrivateFunction.hpp"

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::HtmlDownLoadData *,0>(const HtmlDownLoad * arg) ->zone_data::HtmlDownLoadData *{
    return const_cast<HtmlDownLoad *>(arg)->thisData_.get(); 
}

template<>
inline auto getThisData<const zone_data::HtmlDownLoadData *,1>(const HtmlDownLoad * arg) ->const zone_data::HtmlDownLoadData *{ 
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::HtmlDownLoadData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::HtmlDownLoadData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
HtmlDownLoadData::HtmlDownLoadData() {
}


HtmlDownLoadData::~HtmlDownLoadData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

HtmlDownLoad::HtmlDownLoad():thisData_(ThisDataType(
                         new zone_data::HtmlDownLoadData,
                         [](zone_data::HtmlDownLoadData *arg){delete arg;})) {
}

HtmlDownLoad::~HtmlDownLoad() {
}

/*zone_namespace_end*/


