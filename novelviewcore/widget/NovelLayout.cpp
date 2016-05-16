/*NovelLayout cpp*/
#include "NovelLayout.hpp"
#include "private/NovelLayoutData.hpp"
#include "private/NovelLayoutPrivateFunction.hpp"
#include <functional>
#include <QtConcurrent/QtConcurrent>
#include <QtGui/qtextlayout.h>
#include <QtCore/qdebug.h>
#include <QtGui/qpainter.h>
#include <cmath>
/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::NovelLayoutData *,0>(const NovelLayout * arg) ->zone_data::NovelLayoutData * {
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
    width=512;
    height=512;
}


NovelLayoutData::~NovelLayoutData() {
}

QTextOption textOption=[]() {
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignJustify);
    return std::move(textOption);
}();

/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

void doPreLayout(
    NovelLayout *argThis,
    zone_data::NovelLayoutData::Item &argItem
) {
    zone_this_data(argThis);
    auto & width=argThis->width();
    QTextLayout layout(argItem.string,argThis->font());
    layout.setTextOption(zone_data::textOption);
    layout.setCacheEnabled(false);

    constexpr const double height=123;
    layout.beginLayout();
    argItem.lineCount=0;

    bool isFirstLine=true;
    for (;;) {
        QTextLine line=layout.createLine();
        if (!line.isValid()) { break; }
        if (isFirstLine) {
            isFirstLine=false; 
            line.setLineWidth(std::max<double>(
                var_this_data->firstLineSpace,
                width-var_this_data->firstLineSpace));
            line.setPosition({ var_this_data->firstLineSpace,height });
        }
        else {
            line.setLineWidth(width);
            line.setPosition({ 0.0,height });
        }
        ++argItem.lineCount;
    }

    layout.endLayout();

}

void doLinesLayout(
    NovelLayout *,
    zone_data::NovelLayoutData::Item &argItem,
    std::int32_t &currentLine) {
    if (argItem.lineCount<=0) { return; }
    argItem.startLine=currentLine;
    currentLine+=argItem.lineCount;
    argItem.endLine=currentLine-1;
}

void doLayout(NovelLayout *argThis) {
    zone_this_data(argThis);

    if (var_this_data->needLayout==false) { return; }
    if (bool(var_this_data->file)==false) { return; }

    struct Lock {
        NovelLayout * thisp;
        Lock(NovelLayout *arg):thisp(arg) {}
        ~Lock() { thisp->layoutChanged({}); }
    };
    Lock varLock(argThis);

    auto &varFile=var_this_data->file;
    auto &paragraphs=varFile->paragraphs();

    var_this_data->items.clear();
    var_this_data->currentPage.reset();

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

    {
        std::int32_t currentLine=0;
        for (auto &i:var_this_data->items) {
            doLinesLayout(argThis,i,currentLine);
        }
    }

    if (var_this_data->items.empty()) {
        var_this_data->linesCount=0;
        var_this_data->pagesCount=0;
        return;
    }
    var_this_data->linesCount=var_this_data->items.rbegin()->endLine;

    {
        double pagesCount=
            var_this_data->linesCount/var_this_data->linesOfPage;
        auto pagesCountMore=std::modf(pagesCount,&pagesCount);
        pagesCountMore*=var_this_data->linesOfPage;
        pagesCount+=(pagesCountMore>=0.95);
        var_this_data->pagesCount=std::int32_t(pagesCount+0.5);
    }

}

void drawPage(
    NovelLayout * argThis,
    QImage & argAns
) {
    zone_this_data(argThis);
    if (var_this_data->currentPage) {
        QPainter varPainter(&argAns);
        varPainter.setFont(var_this_data->font);
        varPainter.setRenderHint(QPainter::HighQualityAntialiasing);
        varPainter.setRenderHint(QPainter::TextAntialiasing);
        varPainter.setPen(var_this_data->drawColor);
        varPainter.setBrush(var_this_data->drawColor);
        auto & currentPage=*(var_this_data->currentPage);
        for (auto & line:currentPage.lines) {
            if (line.first<currentPage.lineBegin) { continue; }
            if (line.first<currentPage.lineEnd) {
                line.second.draw(&varPainter,{ 0,0 });
            }
        }
    }
}

/********************************zone_function********************************/
}

NovelLayout::NovelLayout(QObject * parent):
    QObject(parent),
    thisData_(std::make_shared<zone_data::NovelLayoutData>()) {
    _p_setFont(QFont{});
}

NovelLayout::~NovelLayout() {
}

const std::shared_ptr<NovelFile> & NovelLayout::getNovelFile() const {
    zone_const_this_data(this);
    return var_this_data->file;
}

template<typename _t_NOVELFILE_t__>
void NovelLayout::_p_setNovelFile(_t_NOVELFILE_t__ &&_novelFile_) {
    zone_this_data(this);
    var_this_data->file=std::forward<_t_NOVELFILE_t__>(_novelFile_);
    doLayout();
}

void NovelLayout::setNovelFile(const std::shared_ptr<NovelFile>&_novelFile_) {
    _p_setNovelFile(_novelFile_);
}

void NovelLayout::setNovelFile(std::shared_ptr<NovelFile>&&_novelFile_) {
    _p_setNovelFile(std::move(_novelFile_));
}

const double & NovelLayout::getWidth() const {
    zone_const_this_data(this);
    return var_this_data->width;
}

template<typename _t_WIDTH_t__>
void NovelLayout::_p_setWidth(_t_WIDTH_t__ &&_width_) {
    zone_this_data(this);
    auto varWidth=std::max<std::int32_t>(_width_,32);
    if (var_this_data->width==varWidth) { return; }
    var_this_data->width=varWidth;
    doLayout();
    widthChanged({});
}

void NovelLayout::setWidth(const double&_width_) {
    _p_setWidth(_width_);
}

void NovelLayout::setWidth(double&&_width_) {
    _p_setWidth(std::move(_width_));
}

const double & NovelLayout::getHeight() const {
    zone_const_this_data(this);
    return var_this_data->height;
}

template<typename _t_HEIGHT_t__>
void NovelLayout::_p_setHeight(_t_HEIGHT_t__ &&_height_) {
    zone_this_data(this);
    auto varHeight=std::max<std::int32_t>(_height_,32);
    if (varHeight==var_this_data->height) { return; }
    var_this_data->height=varHeight;
    doLayout();
    heightChanged({});
}

void NovelLayout::setHeight(const double&_height_) {
    _p_setHeight(_height_);
}

void NovelLayout::setHeight(double&&_height_) {
    _p_setHeight(std::move(_height_));
}

const QFont & NovelLayout::getFont() const {
    zone_const_this_data(this);
    return var_this_data->font;
}

const QFontMetricsF & NovelLayout::fontMetrics() const {
    zone_const_this_data(this);
    return var_this_data->fontMetrics;
}

template<typename _t_FONT_t__>
void NovelLayout::_p_setFont(_t_FONT_t__ &&_font_) {
    zone_this_data(this);

    var_this_data->font=std::forward<_t_FONT_t__>(_font_);
    var_this_data->fontMetrics=QFontMetricsF(var_this_data->font);
    /*首行缩进*/
    var_this_data->firstLineSpace=
        var_this_data->fontMetrics.width(QStringLiteral("    "));
    /*获得行高*/
    var_this_data->lineHeight=var_this_data->fontMetrics.lineSpacing();
    /*计算每页可以保存的行数*/
    double varLineCountOfPage=
        var_this_data->height/(var_this_data->lineHeight);
    /*取出整数部分和余数部分*/
    var_this_data->topSpaceOfPage=
        std::modf(varLineCountOfPage,&(var_this_data->linesOfPage));
    /*计算余数部分对应的值*/
    var_this_data->topSpaceOfPage*=var_this_data->lineHeight;
    /*计算页眉*/
    var_this_data->topSpaceOfPage/=2;
    var_this_data->topSpaceOfPage=std::floor(var_this_data->topSpaceOfPage);

    zone_private_function::doLayout(this);
}

void NovelLayout::setFont(const QFont&_font_) {
    {
        zone_this_data(this);
        if (_font_==var_this_data->font) { return; }
    }
    _p_setFont(_font_);
    fontChanged({});
}

void NovelLayout::setFont(QFont&&_font_) {
    {
        zone_this_data(this);
        if (_font_==var_this_data->font) { return; }
    }
    _p_setFont(std::move(_font_));
    fontChanged({});
}

void NovelLayout::drawPage(std::int32_t argPage,QImage & argImage) {
    zone_this_data(this);
    argImage=QImage(
        var_this_data->width,
        var_this_data->height,
        QImage::Format_RGBA8888);
    argImage.fill(QColor(0,0,0,0));
    if (argPage>=var_this_data->pagesCount) { return; }
    if (bool(var_this_data->file)==false) { return; }
    if (var_this_data->file->paragraphs().empty()) { return; }

    if (var_this_data->currentPage&&
        (var_this_data->currentPage->index==argPage)) {
        return zone_private_function::drawPage(this,argImage);
    }

    /*计算行号*/
    auto varLine=var_this_data->linesOfPage*argPage;
    /*找到段落*/
    auto varBlock=std::lower_bound(
        var_this_data->items.begin(),
        var_this_data->items.end(),
        varLine,
        zone_data::NovelLayoutData::Item::ItemLineLess{}
    );
    if (varBlock==var_this_data->items.end()) { return; }

    var_this_data->currentPage=std::make_shared<
        zone_data::NovelLayoutData::Page
    >();
    var_this_data->currentPage->index=argPage;

    auto dy=
        ((varBlock->startLine)-varLine)*var_this_data->lineHeight;
    dy+=var_this_data->topSpaceOfPage;

    std::int32_t varLineNum=varBlock->startLine;
    auto varEndLineNum=varLine+var_this_data->linesOfPage;
    auto varBlockEnd=var_this_data->items.end();

    /*设置起止行号*/
    var_this_data->currentPage->lineBegin=varLine;
    var_this_data->currentPage->lineEnd=varEndLineNum;

    /*布局*/
    for (; (varLineNum<varEndLineNum); ++varBlock) {
        if (varBlock==varBlockEnd) { break; }

        auto varTextLayout=std::make_shared<QTextLayout>(
            varBlock->string,
            var_this_data->font
            );
        var_this_data->currentPage->layouts.push_back(varTextLayout);
        varTextLayout->setTextOption(zone_data::textOption);

        {
            auto & layout=*varTextLayout;
            auto & width=var_this_data->width;
            auto leading=var_this_data->fontMetrics.leading();
            auto & height=dy;
            layout.beginLayout();
            bool isFirstLine=true;
            for (;;++varLineNum) {
                QTextLine line=layout.createLine();
                if (!line.isValid()) { break; }
                height+=leading;
                if(isFirstLine){
                    isFirstLine=false;
                    line.setLineWidth(std::max<double>(
                        var_this_data->firstLineSpace,
                        width-var_this_data->firstLineSpace));
                    line.setPosition({ var_this_data->firstLineSpace,height });
                }
                else {
                    line.setLineWidth(width);
                    line.setPosition({ 0.0,height });
                }
                height+=line.height();
                var_this_data->currentPage->lines.insert(
                { varLineNum,std::move(line) });
            }
            layout.endLayout();
        }

    }/*~布局*/

    return zone_private_function::drawPage(this,argImage);
}

std::int32_t NovelLayout::pagesCount()const {
    zone_const_this_data(this);
    return var_this_data->pagesCount;
}

std::int32_t NovelLayout::linesCuont()const {
    zone_const_this_data(this);
    return var_this_data->linesCount+0.5;
}

QSize NovelLayout::getSize() const {
    return QSize(width(),height());
}

template<typename _t_SIZE_t__>
void NovelLayout::_p_setSize(_t_SIZE_t__ &&_size_) {
    zone_this_data(this);
    bool varIsWidthChanged=true;
    bool varIsHeightChanged=true;

    auto varWidth=std::max<std::int32_t>(32,_size_.width());
    auto varHeight=std::max<std::int32_t>(32,_size_.height());

    if (var_this_data->width==varWidth) {
        varIsWidthChanged=false;
    }

    if (var_this_data->height==varHeight) {
        varIsHeightChanged=false;
    }

    if (varIsHeightChanged||varIsWidthChanged) {
        var_this_data->width=varWidth;
        var_this_data->height=varHeight;
        doLayout();
        if (varIsWidthChanged) { widthChanged({}); }
        if (varIsHeightChanged) { heightChanged({}); }
    }

}

void NovelLayout::setSize(const QSize&_size_) {
    _p_setSize(_size_);
}

void NovelLayout::setSize(QSize&&_size_) {
    _p_setSize(std::move(_size_));
}

void NovelLayout::doLayout() {
    _p_setFont(font());
}

const bool & NovelLayout::getNeedLayout() const {
    zone_const_this_data(this);
    return var_this_data->needLayout;
}

template<typename _t_NEEDLAYOUT_t__>
void NovelLayout::_p_setNeedLayout(_t_NEEDLAYOUT_t__ &&_needLayout_) {
    zone_this_data(this);
    if (var_this_data->needLayout==_needLayout_) { return; };
    if (var_this_data->needLayout) {
        var_this_data->needLayout=false;
    }
    else {
        var_this_data->needLayout=true;
        doLayout();
    }
    needLayoutChanged({});
}

void NovelLayout::setNeedLayout(const bool&_needLayout_) {
    _p_setNeedLayout(_needLayout_);
}

void NovelLayout::setNeedLayout(bool&&_needLayout_) {
    _p_setNeedLayout(std::move(_needLayout_));
}

const QColor & NovelLayout::getDrawColor() const{
    zone_const_this_data(this);
    return var_this_data->drawColor;
}

template<typename _t_DRAWCOLOR_t__>
void NovelLayout::_p_setDrawColor(_t_DRAWCOLOR_t__ &&_drawColor_){
    zone_this_data(this);
    if (var_this_data->drawColor==_drawColor_) { return; }
    var_this_data->drawColor=_drawColor_;
    layoutChanged({});
}

void NovelLayout::setDrawColor(const QColor&_drawColor_){
    _p_setDrawColor(_drawColor_);
}

void NovelLayout::setDrawColor(QColor&&_drawColor_){
    _p_setDrawColor(std::move(_drawColor_));
}


/*zone_namespace_end*/


