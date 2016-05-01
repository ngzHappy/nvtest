/*NovelWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_NOVELWIDGET_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_NOVELWIDGET_0__0x00() 1

#include <memory>
#include <QtCore/qobject.h>
#include <list>

/*zone_namespace_begin*/

class NovelLayout;
namespace zone_data{

class NovelWidgetData  {
public:
    NovelWidgetData();
    ~NovelWidgetData();

    std::shared_ptr<NovelLayout> layout;
    std::list<QMetaObject::Connection> connects;
    std::int32_t currentPage=0;
};

}

/*zone_namespace_end*/

#endif

