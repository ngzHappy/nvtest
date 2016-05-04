/*ItemWidget cpp*/
#include "ItemWidget.hpp"
#include "private/ItemWidgetData.hpp"
#include "private/ItemWidgetPrivateFunction.hpp"
#include <QtGui/QPalette>
#include <QtGui/QPainter>
#include <iterator>

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::ItemWidgetData *,0>(const ItemWidget * arg) ->zone_data::ItemWidgetData * {
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
    normal_color_=QColor(
        30+(127&rand()),
        30+(127&rand()),
        30+(127&rand()),
        127);
}


ItemWidgetData::~ItemWidgetData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

ItemWidget::ItemWidget(QWidget* p):
    QWidget(p),
    thisData_(ThisDataType(
        new zone_data::ItemWidgetData,
        [](zone_data::ItemWidgetData *arg) {delete arg; })) {
}

ItemWidget::~ItemWidget() {
}

void ItemWidget::paint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) {
    if (isPaintOptionChanged(option,index)) {
        if (option.rect!=lastStyleOptionViewItem_.rect) {
            updateEditorGeometry(option,index);
        }
        else { this->update(); }
        index_=index;
        lastStyleOptionViewItem_=option;
    }
}
void ItemWidget::setEditorData(const QModelIndex &index) {
    zone_this_data(this);
    //auto & normal_color_=var_this_data->normal_color_;
    auto & text_=var_this_data->text_;
    auto & url_=var_this_data->url_;

    index_=index;
    if (index.isValid()) {
        text_=index.data(Qt::DisplayRole).value<QString>();
        url_=index.data(Qt::ToolTipRole).value<QString>();
        setToolTip(url_);
    }
    else {
        url_="";
        text_="";
    }
    update();

}

void ItemWidget::setModelData(
        QAbstractItemModel *model,
        const QModelIndex &index) {
    index_=index;
    (void)model;
}

QSize ItemWidget::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) {
    return QSize(64,16);
    (void)index; (void)option;
}

void ItemWidget::updateEditorGeometry(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) {
    lastStyleOptionViewItem_=option;
    index_=index;
    this->setGeometry(option.rect);
    update();
}

bool ItemWidget::isPaintOptionChanged(
        const QStyleOptionViewItem &option,
        const QModelIndex &index)const {
    //if (option.state&QStyle::State_MouseOver) { return true; }
    if (index_!=index) { return true; }
    if (option.state!=lastStyleOptionViewItem_.state) { return true; }
    if (option.rect!=lastStyleOptionViewItem_.rect) { return true; }
    return false;
}

void ItemWidget::aboutToDelete() {
    setVisible(false);
}

QRect ItemWidget::geometry()const {
    return QWidget::geometry();
}

void ItemWidget::paintEvent(QPaintEvent*) {
    this->setGeometry(lastStyleOptionViewItem_.rect);
    QImage about_to_draw_;
    renderToImage(about_to_draw_);

    QPainter painter(this);
    painter.setClipRect(0,0,width(),height());
    painter.drawImage(0,0,about_to_draw_);
}

void ItemWidget::renderToImage(QImage & argImage) {

    zone_this_data(this);
    auto & normal_color_=var_this_data->normal_color_;
    auto & text_=var_this_data->text_;
    //auto & url_=var_this_data->url_;

    auto var_size=lastStyleOptionViewItem_.rect.size();

    //qDebug()<<var_size;
    QImage varImage(var_size,QImage::Format_RGBA8888);
    QPainter painter(&varImage);
    varImage.fill(QColor(0,0,0,0));

    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QColor brushColor=QColor(210,212,210);
    if (lastStyleOptionViewItem_.state&QStyle::State_MouseOver) {
        painter.setBrush(brushColor);
    }
    else {
        brushColor=normal_color_;
        painter.setBrush(brushColor);
    }

    varImage.fill(brushColor);
    backGroundColor_=QColor(0,0,0,0);

    if (lastStyleOptionViewItem_.state&QStyle::State_Selected) {
        QPainterPath path;
        path.moveTo(1,1);
        path.lineTo(width()-1,1);
        path.lineTo(width()-1,height()-1);
        path.lineTo(1,height()-1);
        path.closeSubpath();
        painter.setBrush(QColor(10,70,205,100));
        painter.setPen(QPen(QColor(10,70,205,100),2));
        painter.drawPath(path);
    }

    painter.setPen(QPen(QColor(0,0,0),1));
    painter.setBrush(QColor(0,0,0));

    {
        QFont font=painter.font();
        font.setPixelSize(12);
        painter.setFont(font);
    }

    painter.drawText(2,
        painter.fontMetrics().ascent()+2,
        text_);

    argImage=std::move(varImage);
}

/*zone_namespace_end*/


