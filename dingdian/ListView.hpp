﻿/*hpp*/
#if !defined(__LISTVIEW_0___HPP_0x00_)
#define __LISTVIEW_0___HPP_0x00_() 1

#include <QtWidgets/QListView>
#include <functional>
#include <memory>

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

/*zone_namespace_begin*/

namespace zone_data {
class ListViewData;
}

class ListView :public QListView {
    Q_OBJECT
    
MACRO_PROTECTED:
    zone_data::ListViewData * data_=nullptr;
public:
    using CreateFunction=std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> ;
public:

    ListView(QWidget * /*parent*/=nullptr);
    ~ListView();
public:

    void setCreateFunction(const CreateFunction& /*createFunction*/);
    void setCreateFunction(CreateFunction&& /*createFunction*/);
    const CreateFunction & getCreateFunction() const;
    const CreateFunction & createFunction() const { return getCreateFunction(); }

    void closeAllItem();
    void setModel(QAbstractItemModel *model)override;
signals:
    void onCurrentChanged(QPrivateSignal);
private:
    template<typename _t_CREATEFUNCTION_t__>
    void _p_setCreateFunction(_t_CREATEFUNCTION_t__ && /*createFunction*/);
protected:
    void paintGC();
    void paintEvent(QPaintEvent*)override;
    void currentChanged(const QModelIndex &current,const QModelIndex &previous)override;
};

/*zone_namespace_end*/

#endif


