/*ItemWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_ITEMWIDGET_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_ITEMWIDGET_0__0x00() 1

#include <memory>
#include <QtCore/qstring.h>
#include <QtGui/qcolor.h>
/*zone_namespace_begin*/

namespace zone_data{

class ItemWidgetData  {
public:
    ItemWidgetData();
    virtual ~ItemWidgetData();

    QColor normal_color_;
    QString text_;
    QString url_;
};

}

/*zone_namespace_end*/

#endif

