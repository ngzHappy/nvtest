/*NovelFile cpp*/
#include "NovelFile.hpp"
#include "private/NovelFileData.hpp"
#include "private/NovelFilePrivateFunction.hpp"

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::NovelFileData *,0>(const NovelFile * arg) ->zone_data::NovelFileData *{
    return const_cast<NovelFile *>(arg)->thisData_.get(); 
}

template<>
inline auto getThisData<const zone_data::NovelFileData *,1>(const NovelFile * arg) ->const zone_data::NovelFileData *{ 
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::NovelFileData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::NovelFileData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
NovelFileData::NovelFileData() {
}


NovelFileData::~NovelFileData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

NovelFile::NovelFile():thisData_(std::make_shared<zone_data::NovelFileData>()) {
}


NovelFile::~NovelFile() {
}

/*zone_namespace_end*/


