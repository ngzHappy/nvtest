/*DingDianProcess hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DINGDIANPROCESS_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_DINGDIANPROCESS_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QList>
/*zone_namespace_begin*/

namespace zone_data {
class DingDianProcessData;
}
class DingDianProcess;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const DingDianProcess *)->_TYPE_TAG_;

class DingDianProcess {

protected:
    using ThisDataType=std::unique_ptr<zone_data::DingDianProcessData,void(*)(zone_data::DingDianProcessData *)>;
    ThisDataType thisData_{ nullptr,nullptr };
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const DingDianProcess *)->_TYPE_TAG_;
public:
    explicit DingDianProcess(decltype(nullptr)) {}
    DingDianProcess();
    ~DingDianProcess();

    class MainPage {
    public:
        class Item {
        public:
            QString title;
            QString url;
        };
        QList<Item> items;
        QString title;
    };

    MainPage processMainPage()const;

public:
    void setMainPage(const QByteArray& /*mainPage*/);
    void setMainPage(QByteArray&& /*mainPage*/);
    const QByteArray & getMainPage() const;
    const QByteArray & mainPage() const { return getMainPage(); }
private:
    template<typename _t_MAINPAGE_t__>
    void _p_setMainPage(_t_MAINPAGE_t__ && /*mainPage*/);

};

/*zone_namespace_end*/

#endif



