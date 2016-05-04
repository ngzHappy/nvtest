/*DingDianModel hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DINGDIANMODEL_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_DINGDIANMODEL_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QAbstractListModel>
#include "DingDianProcess.hpp"
/*zone_namespace_begin*/

namespace zone_data {
class DingDianModelData;
}
class DingDianModel;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const DingDianModel *)->_TYPE_TAG_;

class DingDianModel :public QAbstractListModel {
    Q_OBJECT

protected:
    using ThisDataType=std::unique_ptr<zone_data::DingDianModelData,void(*)(zone_data::DingDianModelData *)>;
    ThisDataType thisData_{ nullptr,nullptr };
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const DingDianModel *)->_TYPE_TAG_;
public:
    explicit DingDianModel(decltype(nullptr)) {}
    DingDianModel();
    ~DingDianModel();

    enum Role {
        URL_ROLE=Qt::UserRole+1,
        TITLE_ROLE=Qt::DisplayRole,
        TOOLTIP_ROLE=Qt::ToolTipRole,
    };
    QVariant data(const QModelIndex &index,int role) const override;
    int rowCount(const QModelIndex &) const override;
public:
    void setMainPage(const DingDianProcess::MainPage& /*mainPage*/);
    void setMainPage(DingDianProcess::MainPage&& /*mainPage*/);
    const DingDianProcess::MainPage & getMainPage() const;
    const DingDianProcess::MainPage & mainPage() const { return getMainPage(); }
private:
    template<typename _t_MAINPAGE_t__>
    void _p_setMainPage(_t_MAINPAGE_t__ && /*mainPage*/);

};

/*zone_namespace_end*/

#endif



