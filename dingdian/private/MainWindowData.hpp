/*MainWindow hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_MAINWINDOW_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_MAINWINDOW_0__0x00() 1

#include <memory>
#include "CentralWidget.hpp"
/*zone_namespace_begin*/

class NovelWidget;
namespace zone_data {

class MainWindowData {
public:
    MainWindowData();
    virtual ~MainWindowData();

    CentralWidget * novelWidget;
};

}

/*zone_namespace_end*/

#endif

