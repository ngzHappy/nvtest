/*NovelLayout hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_NOVELLAYOUT_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_NOVELLAYOUT_0__0x00() 1

#include <memory>
#include <vector>
#include "NovelFile.hpp"
#include <QtGui/qfont.h>
#include <QtGui/QFontMetricsF>
#include <QtGui/qtextlayout.h>

/*zone_namespace_begin*/

namespace zone_data{

class NovelLayoutData  {
public:
    NovelLayoutData();
    ~NovelLayoutData();

    double width;
    double height;

    std::shared_ptr<NovelFile> file;
    QFont font;
    QFontMetricsF fontMetrics;
    class Item {
    public:
        QString string;
        double lineHeight=0;
        std::int32_t lineCount=0;
        std::shared_ptr<QTextLayout>textLayout;
    };
    std::vector<Item> items;
    
};

}

/*zone_namespace_end*/

#endif

