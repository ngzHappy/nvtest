/*NovelWidget hpp*/
#if !defined(____PRAGMA_ONCE_HPP_NOVELWIDGET_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_NOVELWIDGET_0___HPP_0x00_() 1

#include <QtWidgets/qwidget.h>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

#include "../novelviewcore_global.hpp"

/*zone_namespace_begin*/

namespace zone_data{
class NovelWidgetData;
}
class NovelWidget;
class NovelLayout;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const NovelWidget *)->_TYPE_TAG_ ;

class NOVELVIEWCORESHARED_EXPORT NovelWidget :public QWidget {
    Q_OBJECT

protected:
    std::shared_ptr<zone_data::NovelWidgetData> thisData_;
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const NovelWidget *)->_TYPE_TAG_ ;
public:
    explicit NovelWidget(QWidget * /**/=nullptr);
    ~NovelWidget();
public slots:

    void nextPage();
    void firstPage();
    void lastPage();
    void previousPage();
protected:
    void paintEvent(QPaintEvent *event)override;
    void keyPressEvent(QKeyEvent *event)override;
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



