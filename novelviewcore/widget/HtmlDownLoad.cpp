/*HtmlDownLoad cpp*/
#include "HtmlDownLoad.hpp"
#include "private/HtmlDownLoadData.hpp"
#include "private/HtmlDownLoadPrivateFunction.hpp"
#include <QtCore/qcoreapplication.h>

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

HtmlDownLoadThread::HtmlDownLoadThread(){
    this->moveToThread(this);

    isAboutToExit_=false;
    this->start();

    connect(this,&HtmlDownLoadThread::downLoad,
            this,&HtmlDownLoadThread::_p_downLoad,
            Qt::QueuedConnection);

    manager_=new QNetworkAccessManager;
    manager_->moveToThread(this);
}

void HtmlDownLoadThread::_p_downLoad(std::shared_ptr<HtmlDownLoadPack> argPack){
    if(argPack){
        if(argPack->isNeedDownLoad()){
            const QUrl & varUrl=argPack->url();

            if (manager_) {
                QNetworkRequest varReq(varUrl);
                auto * varRep=manager_->get(varReq);
                varRep->connect(varRep,&QNetworkReply::finished,
                    varRep,[argPack,varRep]() {
                    varRep->deleteLater();
                    QByteArray varData=varRep->readAll();
                    argPack->downLoadFinished(varData,argPack);
                });
            }

        }
    }
}

HtmlDownLoadPack::HtmlDownLoadPack(HtmlDownLoad * argTarget,const QUrl & argUrl){
    url_=argUrl;
    if(argTarget){
        isNeedDownLoad_=true;
        connect(this,&HtmlDownLoadPack::downLoadFinished,
                argTarget,&HtmlDownLoad::downLoadFinished,Qt::QueuedConnection);
        connect(argTarget,&HtmlDownLoad::destroyed,
                this,[this](QObject*){
            isNeedDownLoad_=false;},Qt::QueuedConnection);
    }
}

HtmlDownLoadThread::~HtmlDownLoadThread(){
    delete manager_;
    manager_=nullptr;
    this->quit();
    this->wait(1234);
}

void HtmlDownLoadThread::aboutToStopThread(){
    isAboutToExit_=true;
    delete manager_;
    manager_=nullptr;
    disconnect()/*关闭所有信号槽*/;
    this->quit();
}

void HtmlDownLoadThread::run(){
    if(isAboutToExit_==false){
        exec();
    }
}

std::shared_ptr<HtmlDownLoadThread> htmlDownLoadThread;
std::shared_ptr<HtmlDownLoadThread> HtmlDownLoadThread::instance(){
    if(htmlDownLoadThread){return htmlDownLoadThread;}
    htmlDownLoadThread=std::shared_ptr<HtmlDownLoadThread>(
                new HtmlDownLoadThread,
                [](HtmlDownLoadThread *arg){delete arg;});
    qAddPostRoutine([](){
        auto varHtmlDownLoadThread=htmlDownLoadThread;
        if(varHtmlDownLoadThread){
            varHtmlDownLoadThread->aboutToStopThread();
        }
        htmlDownLoadThread.reset();
    });
    return htmlDownLoadThread;
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
    connect(this,&HtmlDownLoad::download,
        this,[this](const QUrl & arg) {
        auto varDownLoadThread=zone_data::HtmlDownLoadThread::instance();
        auto varPack=std::make_shared<zone_data::HtmlDownLoadPack>(this,arg);
        varDownLoadThread->downLoad(varPack);
    });
}

HtmlDownLoad::~HtmlDownLoad() {
}


/*zone_namespace_end*/


