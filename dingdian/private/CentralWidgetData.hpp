/*CentralWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_CENTRALWIDGET_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_CENTRALWIDGET_0__0x00() 1

#include <memory>
#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qwidget.h>
class NovelLayout;
class NovelFile;
class NovelWidget;
/*zone_namespace_begin*/

namespace zone_data{

class CentralWidgetData  {
public:
    CentralWidgetData();
    ~CentralWidgetData();

    std::shared_ptr<NovelLayout> novelLayout;
    QSplitter * splitter=nullptr;
    NovelWidget * novelWidget=nullptr;
};

}

/*zone_namespace_end*/

#endif

