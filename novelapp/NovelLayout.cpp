/*NovelLayout cpp*/
#include "NovelLayout.hpp"
#include "private/NovelLayoutData.hpp"
#include "private/NovelLayoutPrivateFunction.hpp"
#include <functional>
#include <QtConcurrent/QtConcurrent>
#include <QtGui/qtextlayout.h>
#include <QtCore/qdebug.h>
/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::NovelLayoutData *,0>(const NovelLayout * arg) ->zone_data::NovelLayoutData *{
    return const_cast<NovelLayout *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::NovelLayoutData *,1>(const NovelLayout * arg) ->const zone_data::NovelLayoutData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::NovelLayoutData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::NovelLayoutData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
NovelLayoutData::NovelLayoutData():fontMetrics(QFont{}) {
    width=64;
    height=36;
}


NovelLayoutData::~NovelLayoutData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

void doPreLayout(
    NovelLayout *argThis,
    zone_data::NovelLayoutData::Item &argItem
    ) {
    auto & width=argThis->width();
    QTextLayout layout(argItem.string,argThis->font());
    layout.setCacheEnabled(false);
    
    double height=0;
    const double leading=argThis->fontMetrics().leading();
    layout.beginLayout();
    argItem.lineCount=0;
    argItem.lineHeight=0;
    for (;;) {
        QTextLine line=layout.createLine();
        if (!line.isValid()) { break; }
        line.setLineWidth(width);
        height+=leading;
        line.setPosition({0.0,height});
        height+=line.height();
        argItem.lineHeight+=line.height();
        ++argItem.lineCount;
    }

    layout.endLayout();
    if (argItem.lineCount) {argItem.lineHeight/=argItem.lineCount;}
    else {argItem.lineHeight=0;}

}

void doRealLayout(
    NovelLayout *argThis,
    zone_data::NovelLayoutData::Item &argItem,
    double &argHeight){

    const auto & height=argThis->height();
    argItem.textLayout=std::make_shared<QTextLayout>();

    argItem.textLayout->beginLayout();

    argItem.textLayout->endLayout();

}

void doLayout(NovelLayout *argThis) {
    zone_this_data(argThis);
    auto &varFile=var_this_data->file;
    auto &paragraphs=varFile->paragraphs();
    var_this_data->items.clear();
    if (paragraphs.empty()) { return; }
    var_this_data->items.reserve(paragraphs.size());
    for (const auto &varI:paragraphs) {
        zone_data::NovelLayoutData::Item varItem;
        varItem.string=varI;
        var_this_data->items.push_back(std::move(varItem));
    }

    {
        class Pack {
        public:
            NovelLayout * layout;
        };
        auto pack=std::make_shared<Pack>();
        pack->layout=argThis;

        auto runFunction=[pack](
            zone_data::NovelLayoutData::Item &argItem) {
            doPreLayout(pack->layout,argItem);
        };

        QtConcurrent::blockingMap(
            var_this_data->items.begin(),
            var_this_data->items.end(),
            runFunction
        );
    }

    double varHeight=0;
    for (auto &i:var_this_data->items) {
        doRealLayout(argThis,i,varHeight);
    }

}
/********************************zone_function********************************/
}

NovelLayout::NovelLayout():thisData_(std::make_shared<zone_data::NovelLayoutData>()) {
}


NovelLayout::~NovelLayout() {
}

const std::shared_ptr<NovelFile> & NovelLayout::getNovelFile() const{
    zone_const_this_data(this);
    return var_this_data->file;
}

template<typename _t_NOVELFILE_t__>
void NovelLayout::_p_setNovelFile(_t_NOVELFILE_t__ &&_novelFile_){
    zone_this_data(this);
    var_this_data->file=std::forward<_t_NOVELFILE_t__>(_novelFile_);
    zone_private_function::doLayout(this);
}

void NovelLayout::setNovelFile(const std::shared_ptr<NovelFile>&_novelFile_){
    _p_setNovelFile(_novelFile_);
}

void NovelLayout::setNovelFile(std::shared_ptr<NovelFile>&&_novelFile_){
    _p_setNovelFile(std::move(_novelFile_));
}

const double & NovelLayout::getWidth() const{
    zone_const_this_data(this);
    return var_this_data->width;
}

template<typename _t_WIDTH_t__>
void NovelLayout::_p_setWidth(_t_WIDTH_t__ &&_width_){
    zone_this_data(this);
    var_this_data->width=_width_;
}

void NovelLayout::setWidth(const double&_width_){
    _p_setWidth(_width_);
}

void NovelLayout::setWidth(double&&_width_){
    _p_setWidth(std::move(_width_));
}

const double & NovelLayout::getHeight() const{
    zone_const_this_data(this);
    return var_this_data->height;
}

template<typename _t_HEIGHT_t__>
void NovelLayout::_p_setHeight(_t_HEIGHT_t__ &&_height_){
    zone_this_data(this);
    var_this_data->height=_height_;
}

void NovelLayout::setHeight(const double&_height_){
    _p_setHeight(_height_);
}

void NovelLayout::setHeight(double&&_height_){
    _p_setHeight(std::move(_height_));
}


const QFont & NovelLayout::getFont() const{
    zone_const_this_data(this);
    return var_this_data->font;
}

const QFontMetricsF & NovelLayout::fontMetrics() const {
    zone_const_this_data(this);
    return var_this_data->fontMetrics;
}

template<typename _t_FONT_t__>
void NovelLayout::_p_setFont(_t_FONT_t__ &&_font_){
    zone_this_data(this);
    var_this_data->font=std::forward<_t_FONT_t__>(_font_);
    var_this_data->fontMetrics=QFontMetricsF(var_this_data->font);
}

void NovelLayout::setFont(const QFont&_font_){
    _p_setFont(_font_);
}

void NovelLayout::setFont(QFont&&_font_){
    _p_setFont(std::move(_font_));
}

/*zone_namespace_end*/


