﻿/*MainWindow cpp*/
#include "MainWindow.hpp"
#include "private/MainWindowData.hpp"
#include "private/MainWindowPrivateFunction.hpp"

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
}

MainWindow::~MainWindow() {
}

/*zone_namespace_end*/


