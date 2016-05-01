/*MainWindow hpp*/
#if !defined(____PRAGMA_ONCE_HPP_MAINWINDOW_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_MAINWINDOW_0___HPP_0x00_() 1

#include <QtWidgets/qmainwindow.h>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

/*zone_namespace_begin*/
class NovelLayout;
namespace zone_data {
class MainWindowData;
}
class MainWindow;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const MainWindow *)->_TYPE_TAG_;

class MainWindow :public QMainWindow {
    Q_OBJECT

protected:
    using DataType=std::unique_ptr<zone_data::MainWindowData,void(*)(zone_data::MainWindowData*)>;
    DataType thisData_{ nullptr,nullptr };
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const MainWindow *)->_TYPE_TAG_;
public:
    explicit MainWindow(decltype(nullptr)) {}
    MainWindow();
    ~MainWindow();

public:
    void setNovelLayout(const std::shared_ptr<NovelLayout>& /*novelLayout*/);
    void setNovelLayout(std::shared_ptr<NovelLayout>&& /*novelLayout*/);
    const std::shared_ptr<NovelLayout> & getNovelLayout() const;
    const std::shared_ptr<NovelLayout> & novelLayout() const { return getNovelLayout(); }
private:
    template<typename _t_NOVELLAYOUT_t__>
    void _p_setNovelLayout(_t_NOVELLAYOUT_t__ && /*novelLayout*/);
};

/*zone_namespace_end*/

#endif



