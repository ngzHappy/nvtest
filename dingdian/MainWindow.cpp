/*MainWindow cpp*/
#include "MainWindow.hpp"
#include "private/MainWindowData.hpp"
#include "private/MainWindowPrivateFunction.hpp"
#include <NovelFile.hpp>
#include <NovelWidget.hpp>
#include <NovelLayout.hpp>

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::MainWindowData *,0>(const MainWindow * arg) ->zone_data::MainWindowData * {
    return const_cast<MainWindow *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::MainWindowData *,1>(const MainWindow * arg) ->const zone_data::MainWindowData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::MainWindowData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::MainWindowData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
MainWindowData::MainWindowData() {
}


MainWindowData::~MainWindowData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

MainWindow::MainWindow():
    thisData_(
        std::unique_ptr<
        zone_data::MainWindowData,
        void(*)(zone_data::MainWindowData*)>{new zone_data::MainWindowData,
        [](zone_data::MainWindowData * arg) {delete arg; } }) {
    zone_this_data(this);
    var_this_data->novelWidget=new NovelWidget;
    setCentralWidget(var_this_data->novelWidget);
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);
}

MainWindow::~MainWindow() {
}

const std::shared_ptr<NovelLayout> & MainWindow::getNovelLayout() const{
    zone_const_this_data(this);
    return var_this_data->novelWidget->novelLayout();
}

template<typename _t_NOVELLAYOUT_t__>
void MainWindow::_p_setNovelLayout(_t_NOVELLAYOUT_t__ &&_novelLayout_){
    zone_this_data(this);
    var_this_data->novelWidget->setNovelLayout(
        std::forward<_t_NOVELLAYOUT_t__>(_novelLayout_));
}

void MainWindow::setNovelLayout(const std::shared_ptr<NovelLayout>&_novelLayout_){
    _p_setNovelLayout(_novelLayout_);
}

void MainWindow::setNovelLayout(std::shared_ptr<NovelLayout>&&_novelLayout_){
    _p_setNovelLayout(std::move(_novelLayout_));
}



/*zone_namespace_end*/


