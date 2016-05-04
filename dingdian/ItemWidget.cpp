/*ItemWidget cpp*/
#include "ItemWidget.hpp"
#include "private/ItemWidgetData.hpp"
#include "private/ItemWidgetPrivateFunction.hpp"

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::ItemWidgetData *,0>(const ItemWidget * arg) ->zone_data::ItemWidgetData *{
    return const_cast<ItemWidget *>(arg)->thisData_.get(); 
}

template<>
inline auto getThisData<const zone_data::ItemWidgetData *,1>(const ItemWidget * arg) ->const zone_data::ItemWidgetData *{ 
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::ItemWidgetData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::ItemWidgetData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
ItemWidgetData::ItemWidgetData() {
}


ItemWidgetData::~ItemWidgetData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

ItemWidget::ItemWidget():thisData_(ThisDataType(
                         new zone_data::ItemWidgetData,
                         [](zone_data::ItemWidgetData *arg){delete arg;})) {
}

ItemWidget::~ItemWidget() {
}

/*zone_namespace_end*/


