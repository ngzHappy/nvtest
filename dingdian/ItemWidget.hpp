/*ItemWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_ITEMWIDGET_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_ITEMWIDGET_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <QtWidgets/qwidget.h>
#include "AbstractItemWidget.hpp"

/*zone_namespace_begin*/

namespace zone_data{
class ItemWidgetData;
}
class ItemWidget;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const ItemWidget *)->_TYPE_TAG_ ;

class ItemWidget :public QWidget{
    Q_OBJECT

protected:
    using ThisDataType=std::unique_ptr<zone_data::ItemWidgetData,void(*)(zone_data::ItemWidgetData *)>;
    ThisDataType thisData_{nullptr,nullptr};
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const ItemWidget *)->_TYPE_TAG_ ;
public:
    explicit ItemWidget(decltype(nullptr)) {}
    ItemWidget();
    ~ItemWidget();

};

/*zone_namespace_end*/

#endif



