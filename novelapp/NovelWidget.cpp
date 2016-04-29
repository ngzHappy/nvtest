/*NovelWidget cpp*/
#include "NovelWidget.hpp"
#include "private/NovelWidgetData.hpp"
#include "private/NovelWidgetPrivateFunction.hpp"
#include "NovelFile.hpp"
#include "NovelLayout.hpp"
#include <QtGui/qpainter.h>

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::NovelWidgetData *,0>(const NovelWidget * arg) ->zone_data::NovelWidgetData *{
    return const_cast<NovelWidget *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::NovelWidgetData *,1>(const NovelWidget * arg) ->const zone_data::NovelWidgetData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::NovelWidgetData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::NovelWidgetData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
NovelWidgetData::NovelWidgetData() {
}


NovelWidgetData::~NovelWidgetData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

NovelWidget::NovelWidget(QWidget * p):
    QWidget(p),
    thisData_(std::make_shared<zone_data::NovelWidgetData>()) {
}


NovelWidget::~NovelWidget() {
}

const std::shared_ptr<NovelLayout> & NovelWidget::getNovelLayout() const{
    zone_const_this_data(this);
    return var_this_data->layout;
}

template<typename _t_NOVELLAYOUT_t__>
void NovelWidget::_p_setNovelLayout(_t_NOVELLAYOUT_t__ &&_novelLayout_){
    zone_this_data(this);
    if (var_this_data->layout==_novelLayout_) { return; }
    if (var_this_data->layout) {
        for (auto & i:var_this_data->connects) {disconnect(i);}
    }
    var_this_data->connects.clear();
    if (_novelLayout_) {
        connect(
            _novelLayout_.get(),
            &NovelLayout::layoutChanged,
            this,[this]() {update(); }
        );
        _novelLayout_->setSize({ width(),height() });
    }
    var_this_data->currentPage=0;
    var_this_data->layout=std::forward<_t_NOVELLAYOUT_t__>(_novelLayout_);
    update();
}

void NovelWidget::setNovelLayout(const std::shared_ptr<NovelLayout>&_novelLayout_){
    _p_setNovelLayout(_novelLayout_);
}

void NovelWidget::setNovelLayout(std::shared_ptr<NovelLayout>&&_novelLayout_){
    _p_setNovelLayout(std::move(_novelLayout_));
}

void NovelWidget::paintEvent(QPaintEvent *){
    zone_this_data(this);
    if(var_this_data->layout){
        var_this_data->layout->setSize({ width(),height() });
        QImage varImage;
        if (var_this_data->currentPage>=var_this_data->layout->pagesCount()) {
            var_this_data->currentPage=std::max<std::int32_t>(
                var_this_data->layout->pagesCount()-1,
                0);
        }
        var_this_data->layout->drawPage(
            var_this_data->currentPage,
            varImage);
        QPainter painter(this);
        painter.drawImage(0,0,varImage);
    }
}

/*zone_namespace_end*/


