/*HtmlDownLoad cpp*/
#include "HtmlDownLoad.hpp"
#include "private/HtmlDownLoadData.hpp"
#include "private/HtmlDownLoadPrivateFunction.hpp"
#include <QtCore/qcoreapplication.h>
#include <QtCore/qdir.h>
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
    connect(this,&HtmlDownLoadThread::downLoad,
        this,&HtmlDownLoadThread::_p_downLoad,
        Qt::QueuedConnection);

    isAboutToExit_=false;
    this->start();
}

void HtmlDownLoadThread::_p_downLoad(std::shared_ptr<HtmlDownLoadPack> argPack){
     
    if(argPack){
        if(argPack->isNeedDownLoad()){
            const QUrl & varUrl=argPack->url();
            
            {/*尝试读取缓存*/
                const QString localCacheName=HtmlDownLoad::url2LocalCacheFileName(varUrl);
                QFile file{localCacheName};
                if (file.open(QIODevice::ReadOnly)) {
                    if (argPack->isCacheDownLoad()) { 
                        argPack->cacheDownLoadFinished(argPack);
                        return; 
                    }
                    QByteArray varAns=file.readAll();
                    argPack->downLoadFinished(varAns,argPack);
                    return;
                }
            }

            if (manager_==nullptr) {
                manager_=new QNetworkAccessManager(this);
            }

            if (manager_) {
                QNetworkRequest varReq(varUrl);
                auto * varRep=manager_->get(varReq);
                varRep->connect(varRep,&QNetworkReply::finished,
                    varRep,[argPack,varRep]() {
                    varRep->deleteLater();
                    QByteArray varData=varRep->readAll();
                    {/*写入缓存*/
                        const QUrl & varUrl=argPack->url();
                        const QString localCacheName=HtmlDownLoad::url2LocalCacheFileName(varUrl);
                        QFile file{ localCacheName };
                        if (file.open(QIODevice::WriteOnly)) {
                            file.write(varData);
                        }
                    }
                    if (argPack->isCacheDownLoad()) { 
                        argPack->cacheDownLoadFinished(argPack);
                        return; 
                    }
                    argPack->downLoadFinished(varData,argPack);
                });
            }

        }
    }
}

HtmlDownLoadPack::HtmlDownLoadPack(
    HtmlDownLoad * argTarget,
    const QUrl & argUrl,
    bool arg_isc):isCacheDownLoad_(arg_isc){
    url_=argUrl;
    if(argTarget){
        isNeedDownLoad_=true;
        connect(this,&HtmlDownLoadPack::downLoadFinished,
                argTarget,&HtmlDownLoad::downLoadFinished,Qt::QueuedConnection);
        connect(argTarget,&HtmlDownLoad::destroyed,
                this,[this](QObject*){
            isNeedDownLoad_=false;},Qt::QueuedConnection);
        connect(this,&HtmlDownLoadPack::cacheDownLoadFinished,
            argTarget,&HtmlDownLoad::cacheDownLoadFinished,
            Qt::QueuedConnection);
    }
}

HtmlDownLoadThread::~HtmlDownLoadThread(){
    this->quit();
}

void HtmlDownLoadThread::aboutToStopThread(){
    isAboutToExit_=true;
    this->quit();
    this->wait(11);
}

void HtmlDownLoadThread::run(){
    if(isAboutToExit_==false){exec();}
}

std::shared_ptr<HtmlDownLoadThread> htmlDownLoadThread;
std::shared_ptr<HtmlDownLoadThread> HtmlDownLoadThread::instance(){
    if(htmlDownLoadThread){return htmlDownLoadThread;}
    htmlDownLoadThread=std::shared_ptr<HtmlDownLoadThread>(
                new HtmlDownLoadThread,
                [](HtmlDownLoadThread *arg){
        arg->quit();
        /*arg->wait(123);*/
        /*arg->terminate();*/
        /*arg->deleteLater();*/
    });
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
    connect(this,&HtmlDownLoad::cacheDownLoad,
        this,[this](const QUrl & arg) {
        auto varDownLoadThread=zone_data::HtmlDownLoadThread::instance();
        auto varPack=std::make_shared<zone_data::HtmlDownLoadPack>(this,arg,true);
        varDownLoadThread->downLoad(varPack);
    });
}

HtmlDownLoad::~HtmlDownLoad() {
}

QString HtmlDownLoad::url2LocalCacheFileName(const QUrl &varUrl) {
    static const QString appDir=[]()->QString {
        QString ans=qApp->applicationDirPath();
        QDir dir{ ans };
        dir.mkpath(ans+"/appCache");
        return ans+"/appCache";
    }();
    const auto localFileName=varUrl.toString().toUtf8()
        .toBase64(QByteArray::Base64UrlEncoding);
    return appDir+"/"+localFileName+".html";
}

/*zone_namespace_end*/


