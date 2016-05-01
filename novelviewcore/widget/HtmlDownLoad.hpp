/*HtmlDownLoad hpp*/
#if !defined(____PRAGMA_ONCE_HPP_HTMLDOWNLOAD_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_HTMLDOWNLOAD_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <QtCore/qstring.h>
#include <QtCore/qurl.h>
#include <QtCore/qobject.h>

#include "../novelviewcore_global.hpp"

/*zone_namespace_begin*/

namespace zone_data{
class HtmlDownLoadData;
class HtmlDownLoadPack;
}
class HtmlDownLoad;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const HtmlDownLoad *)->_TYPE_TAG_ ;

class NOVELVIEWCORESHARED_EXPORT HtmlDownLoad :public QObject{
    Q_OBJECT

protected:
    using ThisDataType=std::unique_ptr<zone_data::HtmlDownLoadData,void(*)(zone_data::HtmlDownLoadData *)>;
    ThisDataType thisData_{nullptr,nullptr};
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const HtmlDownLoad *)->_TYPE_TAG_ ;
public:
    explicit HtmlDownLoad(decltype(nullptr)) {}
    HtmlDownLoad();
    ~HtmlDownLoad();

signals:
    void download(const QUrl &);
    void downLoadFinished(QByteArray,std::shared_ptr<zone_data::HtmlDownLoadPack>);
};

/*zone_namespace_end*/

#endif



