/*CentralWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_CENTRALWIDGET_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_CENTRALWIDGET_0__0x00() 1

#include <memory>
#include <QtWidgets/qwidget.h>
#include "../ListView.hpp"
#include <HtmlDownLoad.hpp>
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
    NovelWidget * novelWidget=nullptr;
    ListView * listView=nullptr;
    DingDianProcess::MainPage mainPage;
    std::shared_ptr<HtmlDownLoad> pageHtmlDownLoad;
};

}

/*zone_namespace_end*/

#endif

