/*CentralWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_CENTRALWIDGET_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_CENTRALWIDGET_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <QtWidgets/qsplitter.h>

/*zone_namespace_begin*/

namespace zone_data{
class CentralWidgetData;
}
class CentralWidget;
class NovelLayout;
class NovelFile;
class NovelWidget;
 
template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const CentralWidget *)->_TYPE_TAG_ ;

class CentralWidget :public QSplitter{
    Q_OBJECT

protected:
    using ThisDataType=std::unique_ptr<zone_data::CentralWidgetData,void(*)(zone_data::CentralWidgetData *)>;
    ThisDataType thisData_{nullptr,nullptr};
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const CentralWidget *)->_TYPE_TAG_ ;
public:
    explicit CentralWidget(decltype(nullptr)) {}
    CentralWidget();
    ~CentralWidget();
public:
    void setNovelLayout(const std::shared_ptr<NovelLayout>& /*novelLayout*/);
    void setNovelLayout(std::shared_ptr<NovelLayout>&& /*novelLayout*/);
    const std::shared_ptr<NovelLayout> & getNovelLayout() const;
    const std::shared_ptr<NovelLayout> & novelLayout() const{ return getNovelLayout();}
private: 
    template<typename _t_NOVELLAYOUT_t__>
    void _p_setNovelLayout(_t_NOVELLAYOUT_t__ && /*novelLayout*/);
};

/*zone_namespace_end*/

#endif



