/*NovelFile hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_NOVELFILE_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_NOVELFILE_0__0x00() 1

#include <memory>
#include <list>
#include <QtCore/qstring.h>

/*zone_namespace_begin*/

namespace zone_data{

class NovelFileData  {
public:
    NovelFileData();
    ~NovelFileData();

    std::list<QString> paragraphs;

};

}

/*zone_namespace_end*/

#endif

