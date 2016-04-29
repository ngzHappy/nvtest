/*NovelLayout hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_NOVELLAYOUT_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_NOVELLAYOUT_0__0x00() 1

#include <memory>
#include <vector>
#include <map>
#include <list>
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
        std::int32_t lineCount=0;
        std::int32_t startLine=0;
        std::int32_t endLine=0;
        class ItemLineLess {
        public:
            template<typename T>
            bool operator()(const Item & l,T &&r) { return l.endLine<r; }
            template<typename T>
            bool operator()(T&& l,const Item &r) { return l<r.endLine; }
            bool operator()(const Item & l,const Item &r) { return l.endLine<r.endLine; }
        };
    };
    std::vector<Item> items;
    double lineHeight;
    double topSpaceOfPage;
    double linesOfPage;
    std::int32_t pagesCount;
    std::int32_t linesCount;
    bool needLayout=false;
    class Page {
    public:
        std::int32_t index=0;
        std::list<std::shared_ptr<QTextLayout>> layouts;
        std::map<std::int32_t,QTextLine> lines;
        std::int32_t lineBegin;
        std::int32_t lineEnd;
    };
    std::shared_ptr<Page> currentPage;
};

}

/*zone_namespace_end*/

#endif

