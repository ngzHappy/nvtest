/*MainWindow hpp*/
#if !defined(____PRAGMA_ONCE_HPP_MAINWINDOW_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_MAINWINDOW_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

/*zone_namespace_begin*/

/*
#if !defined(macro_no_copy)
#define macro_no_copy(_t_class_name_) private:_t_class_name_(const _t_class_name_ &)=delete; \
_t_class_name_(_t_class_name_ &&)=delete; \
_t_class_name_&operator=(const _t_class_name_ &)=delete; \
_t_class_name_&operator=(_t_class_name_ &&)=delete
#endif
*/

namespace zone_data{
class MainWindowData;
}
class MainWindow;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const MainWindow *)->_TYPE_TAG_ ;

class MainWindow {
/*macro_no_copy(MainWindow);*/
protected:
    std::shared_ptr<zone_data::MainWindowData> thisData_;
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const MainWindow *)->_TYPE_TAG_ ;
public:
    explicit MainWindow(decltype(nullptr)) {}
    MainWindow();
    ~MainWindow();

};

/*zone_namespace_end*/

#endif



