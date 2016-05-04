/*CentralWidget cpp*/
#include "CentralWidget.hpp"
#include "private/CentralWidgetData.hpp"
#include "private/CentralWidgetPrivateFunction.hpp"
#include <NovelFile.hpp>
#include <NovelWidget.hpp>
#include <NovelLayout.hpp>
/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::CentralWidgetData *,0>(const CentralWidget * arg) ->zone_data::CentralWidgetData *{
    return const_cast<CentralWidget *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::CentralWidgetData *,1>(const CentralWidget * arg) ->const zone_data::CentralWidgetData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::CentralWidgetData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::CentralWidgetData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
CentralWidgetData::CentralWidgetData() {
}


CentralWidgetData::~CentralWidgetData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

CentralWidget::CentralWidget():thisData_(ThisDataType(
                         new zone_data::CentralWidgetData,
                         [](zone_data::CentralWidgetData *arg){delete arg;})) {
    this->setOrientation(Qt::Horizontal);
    zone_this_data(this);
    var_this_data->listView=new ListView;
    this->addWidget(var_this_data->listView);
    var_this_data->novelWidget=new NovelWidget;
    this->addWidget(var_this_data->novelWidget);
}

CentralWidget::~CentralWidget() {
}

const std::shared_ptr<NovelLayout> & CentralWidget::getNovelLayout() const{
    zone_const_this_data(this);
    return var_this_data->novelLayout;
}

template<typename _t_NOVELLAYOUT_t__>
void CentralWidget::_p_setNovelLayout(_t_NOVELLAYOUT_t__ &&_novelLayout_){
    zone_this_data(this);
    var_this_data->novelLayout=
        std::forward<_t_NOVELLAYOUT_t__>(_novelLayout_);
    var_this_data->novelWidget->setNovelLayout(var_this_data->novelLayout);
}

void CentralWidget::setNovelLayout(const std::shared_ptr<NovelLayout>&_novelLayout_){
    _p_setNovelLayout(_novelLayout_);
}

void CentralWidget::setNovelLayout(std::shared_ptr<NovelLayout>&&_novelLayout_){
    _p_setNovelLayout(std::move(_novelLayout_));
}

/*zone_namespace_end*/


