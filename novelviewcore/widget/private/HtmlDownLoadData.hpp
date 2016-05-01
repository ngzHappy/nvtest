/*HtmlDownLoad hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_HTMLDOWNLOAD_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_HTMLDOWNLOAD_0__0x00() 1

#include <memory>
#include <QtCore/qobject.h>
#include <QtCore/qthread.h>
#include <QtCore/qurl.h>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkrequest.h>
#include <atomic>

/*zone_namespace_begin*/
class HtmlDownLoad;
namespace zone_data{

class HtmlDownLoadPack : public QObject{
    Q_OBJECT

private:
    QUrl url_;
    std::atomic<bool> isNeedDownLoad_;
public:
    HtmlDownLoadPack(HtmlDownLoad *,const QUrl &);

    bool isNeedDownLoad()const{return isNeedDownLoad_.load();}
    const QUrl & url()const{return url_;}

signals:
    void downLoadFinished(QByteArray,std::shared_ptr<HtmlDownLoadPack>);
};

class HtmlDownLoadThread :public QThread{
    Q_OBJECT

private:
    std::atomic<bool> isAboutToExit_;
    QNetworkAccessManager * manager_=nullptr;
public:
    HtmlDownLoadThread();

    static std::shared_ptr<HtmlDownLoadThread> instance();
    void aboutToStopThread();

signals:
    void downLoad(std::shared_ptr<HtmlDownLoadPack>);
protected:
    ~HtmlDownLoadThread();
    void run() override;
    void _p_downLoad(std::shared_ptr<HtmlDownLoadPack>);
};

class HtmlDownLoadData  {
public:
    HtmlDownLoadData();
    ~HtmlDownLoadData();

};

}

Q_DECLARE_METATYPE(std::shared_ptr<zone_data::HtmlDownLoadPack>)

/*zone_namespace_end*/

#endif

