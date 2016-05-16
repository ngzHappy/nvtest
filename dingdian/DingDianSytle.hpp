/*DingDianSytle hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DINGDIANSYTLE_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_DINGDIANSYTLE_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <QObject>

/*zone_namespace_begin*/

namespace zone_data{
class DingDianSytleData;
}
class DingDianSytle;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const DingDianSytle *)->_TYPE_TAG_ ;

class DingDianSytle :public QObject{
    Q_OBJECT

protected:
    using ThisDataType=std::unique_ptr<zone_data::DingDianSytleData,void(*)(zone_data::DingDianSytleData *)>;
    ThisDataType thisData_{nullptr,nullptr};
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const DingDianSytle *)->_TYPE_TAG_ ;
public:
    explicit DingDianSytle(decltype(nullptr)) {}
    DingDianSytle();

    static std::shared_ptr<DingDianSytle> instance();

protected:
    ~DingDianSytle();

};

/*zone_namespace_end*/

#endif



