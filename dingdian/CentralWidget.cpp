﻿/*CentralWidget cpp*/
#include "CentralWidget.hpp"
#include "ItemWidget.hpp"
#include "DingDianModel.hpp"
#include "private/CentralWidgetData.hpp"
#include "private/CentralWidgetPrivateFunction.hpp"
#include <NovelFile.hpp>
#include <NovelWidget.hpp>
#include <NovelLayout.hpp>
/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::CentralWidgetData *,0>(const CentralWidget * arg) ->zone_data::CentralWidgetData * {
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
    [](zone_data::CentralWidgetData *arg) {delete arg; })) {
    this->setOrientation(Qt::Horizontal);
    zone_this_data(this);
    var_this_data->listView=new ListView;
    this->addWidget(var_this_data->listView);
    var_this_data->novelWidget=new NovelWidget;
    this->addWidget(var_this_data->novelWidget);

    {
        auto varSizePolicy=var_this_data->listView->sizePolicy();
        varSizePolicy.setHorizontalStretch(0);
        var_this_data->listView->setSizePolicy(varSizePolicy);
    }

    {
        auto varSizePolicy=var_this_data->novelWidget->sizePolicy();
        varSizePolicy.setHorizontalStretch(1);
        var_this_data->novelWidget->setSizePolicy(varSizePolicy);
    }
    /*设置listview 样式*/
    std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> createFunction=
        std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>>(
            new std::function<QWidget*(QWidget*,QModelIndex)>{
        [](QWidget* argParent,QModelIndex) ->QWidget * {
        ItemWidget * varAns=new ItemWidget(argParent);
        return varAns;
    }/*~lambda function*/
    });
    var_this_data->listView->setCreateFunction(createFunction);
    /*设置model*/
    if (var_this_data->listView->model()) {
        var_this_data->listView->model()->deleteLater();
    }
    var_this_data->listView->setModel(new DingDianModel);

    {
        auto varNovelLayout=std::make_shared<NovelLayout>();
        auto varFont=varNovelLayout->font();
        varFont.setPixelSize(26);
        varNovelLayout->setFont(varFont);
        var_this_data->novelWidget->setNovelLayout(varNovelLayout);
    }


    connect(
        var_this_data->listView,&ListView::onCurrentChanged,
        this,&CentralWidget::onCurrentChanged);
    connect(
        var_this_data->novelWidget,
        &NovelWidget::onKeyPressed,
        this,
        [var_this_data](Qt::Key argKey) {
        if (argKey==Qt::Key_Up) {
            auto varListView=var_this_data->listView;
            auto *varModel=varListView->model();
            auto varIndex=varModel->index(
                std::max(0,varListView->currentIndex().row()-1),
                0);
            varListView->setCurrentIndex(varIndex);
        }
        else if (argKey==Qt::Key_Down) {
            auto varListView=var_this_data->listView;
            auto *varModel=varListView->model();
            auto varIndex=varModel->index(
                std::min(
                std::max(0,varModel->rowCount()-1),
                1+varListView->currentIndex().row()),
                0);
            varListView->setCurrentIndex(varIndex);
        }
    });
}

CentralWidget::~CentralWidget() {
}

const std::shared_ptr<NovelLayout> & CentralWidget::getNovelLayout() const {
    zone_const_this_data(this);
    return var_this_data->novelLayout;
}

template<typename _t_NOVELLAYOUT_t__>
void CentralWidget::_p_setNovelLayout(_t_NOVELLAYOUT_t__ &&_novelLayout_) {
    zone_this_data(this);
    var_this_data->novelLayout=
        std::forward<_t_NOVELLAYOUT_t__>(_novelLayout_);
    var_this_data->novelWidget->setNovelLayout(var_this_data->novelLayout);
}

const DingDianProcess::MainPage & CentralWidget::getMainPage() const {
    zone_const_this_data(this);
    return var_this_data->mainPage;
}

template<typename _t_MAINPAGE_t__>
void CentralWidget::_p_setMainPage(_t_MAINPAGE_t__ &&_mainPage_) {
    zone_this_data(this);
    var_this_data->mainPage=std::forward<_t_MAINPAGE_t__>(_mainPage_);
    auto * varModel=
        qobject_cast<DingDianModel*>(var_this_data->listView->model());
    varModel->setMainPage(var_this_data->mainPage);
    auto varListView=var_this_data->listView;
    var_this_data->cacheHtmlDownLoad.reset();
    varListView->setCurrentIndex(varModel->index(0,0));
    var_this_data->currentPreDownloadID=0;
    var_this_data->cacheHtmlDownLoad
        =std::make_shared<HtmlDownLoad>();
    connect(var_this_data->cacheHtmlDownLoad.get(),
        &HtmlDownLoad::cacheDownLoadFinished,
        this,
        [var_this_data](auto) {
        if (var_this_data->cacheHtmlDownLoad) {
            if (var_this_data->mainPage.items.empty()==false) {
                ++(var_this_data->currentPreDownloadID);
                if (var_this_data->mainPage.items.size()>(var_this_data->currentPreDownloadID)) {
                    var_this_data->cacheHtmlDownLoad->cacheDownLoad(
                        var_this_data->mainPage.items[(var_this_data->currentPreDownloadID)]
                        .url
                    );
                }
            }
        }
    });
    if (var_this_data->mainPage.items.empty()) { return; }
    var_this_data->cacheHtmlDownLoad->cacheDownLoad(
        var_this_data->mainPage.items[0].url
    );
}

void CentralWidget::setMainPage(const DingDianProcess::MainPage&_mainPage_) {
    _p_setMainPage(_mainPage_);
}

void CentralWidget::setMainPage(DingDianProcess::MainPage&&_mainPage_) {
    _p_setMainPage(std::move(_mainPage_));
}

void CentralWidget::setNovelLayout(const std::shared_ptr<NovelLayout>&_novelLayout_) {
    _p_setNovelLayout(_novelLayout_);
}

void CentralWidget::setNovelLayout(std::shared_ptr<NovelLayout>&&_novelLayout_) {
    _p_setNovelLayout(std::move(_novelLayout_));
}

void CentralWidget::onCurrentChanged() {
    zone_this_data(this);
    QModelIndex varCurrentIndex=var_this_data->listView->currentIndex();
    if (varCurrentIndex.isValid()) {
        var_this_data->pageHtmlDownLoad.reset();
        QString varUrl=varCurrentIndex.data(Qt::ToolTipRole).value<QString>();
        if (varUrl.isEmpty()==false) {
            var_this_data->pageHtmlDownLoad=
                std::make_shared<HtmlDownLoad>();
            connect(
                var_this_data->pageHtmlDownLoad.get(),
                &HtmlDownLoad::downLoadFinished,
                this,
                [var_this_data](QByteArray argHtml,auto) {
                DingDianProcess varProcess;
                auto varPage=varProcess.processAPage(argHtml);
                auto novelFile=std::make_shared<NovelFile>();
                novelFile->setParagraphs(std::move(varPage));
                var_this_data->novelWidget->novelLayout()
                    ->setNovelFile(std::move(novelFile));
                var_this_data->novelWidget->firstPage();
                var_this_data->novelWidget->novelLayout()
                    ->setNeedLayout(true);
            });
            var_this_data->pageHtmlDownLoad->download(QUrl(varUrl));
        }
    }
}



/*zone_namespace_end*/


