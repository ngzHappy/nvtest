/*DingDianModel cpp*/
#include "DingDianModel.hpp"
#include "private/DingDianModelData.hpp"
#include "private/DingDianModelPrivateFunction.hpp"

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::DingDianModelData *,0>(const DingDianModel * arg) ->zone_data::DingDianModelData *{
    return const_cast<DingDianModel *>(arg)->thisData_.get(); 
}

template<>
inline auto getThisData<const zone_data::DingDianModelData *,1>(const DingDianModel * arg) ->const zone_data::DingDianModelData *{ 
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::DingDianModelData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::DingDianModelData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
DingDianModelData::DingDianModelData() {
}


DingDianModelData::~DingDianModelData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

DingDianModel::DingDianModel():thisData_(ThisDataType(
                         new zone_data::DingDianModelData,
                         [](zone_data::DingDianModelData *arg){delete arg;})) {
}

DingDianModel::~DingDianModel() {
}

QVariant DingDianModel::data(
    const QModelIndex &index,
    int role) const {

    if (index.isValid()==false) { return{}; }

    switch (role) {
        case Qt::EditRole:
        case Qt::DisplayRole: {
            zone_const_this_data(this);
            if (var_this_data->mainPage.items.size()>index.row()) {
                return var_this_data->mainPage.items[index.row()].title;
            }
        }break;
        case Role::URL_ROLE:
        case Qt::ToolTipRole: {
            zone_const_this_data(this);
            if (var_this_data->mainPage.items.size()>index.row()) {
                return var_this_data->mainPage.items[index.row()].url;
            }
        }break;
        default:break;
    }

    return{};
}

const DingDianProcess::MainPage & DingDianModel::getMainPage() const{
    zone_const_this_data(this);
    return var_this_data->mainPage;
}

template<typename _t_MAINPAGE_t__>
void DingDianModel::_p_setMainPage(_t_MAINPAGE_t__ &&_mainPage_){
    zone_this_data(this);
    beginResetModel();
    var_this_data->mainPage=std::forward<_t_MAINPAGE_t__>(_mainPage_);
    endResetModel();
}

void DingDianModel::setMainPage(const DingDianProcess::MainPage&_mainPage_){
    _p_setMainPage(_mainPage_);
}

void DingDianModel::setMainPage(DingDianProcess::MainPage&&_mainPage_){
    _p_setMainPage(std::move(_mainPage_));
}



/*zone_namespace_end*/


