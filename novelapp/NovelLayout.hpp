/*NovelLayout hpp*/
#if !defined(____PRAGMA_ONCE_HPP_NOVELLAYOUT_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_NOVELLAYOUT_0___HPP_0x00_() 1

#include <QtCore/qobject.h>
#include <QtGui/qfont.h>
#include <QtGui/QFontMetricsF>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

/*zone_namespace_begin*/

namespace zone_data {
class NovelLayoutData;
}
class NovelLayout;
class NovelFile;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const NovelLayout *)->_TYPE_TAG_;

class NovelLayout :public QObject {
    Q_OBJECT

private:
    template<typename ...>using void_t=void;
protected:
    std::shared_ptr<zone_data::NovelLayoutData> thisData_;
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const NovelLayout *)->_TYPE_TAG_;
public:
    explicit NovelLayout(decltype(nullptr)) {}
    NovelLayout();
    virtual ~NovelLayout();
public:
    void setNovelFile(const std::shared_ptr<NovelFile>& /*novelFile*/);
    void setNovelFile(std::shared_ptr<NovelFile>&& /*novelFile*/);
    const std::shared_ptr<NovelFile> & getNovelFile() const;
    const std::shared_ptr<NovelFile> & novelFile() const { return getNovelFile(); }
public:
    void setWidth(const double& /*width*/);
    void setWidth(double&& /*width*/);
    const double & getWidth() const;
    const double & width() const{ return getWidth();}
public:
    void setHeight(const double& /*height*/);
    void setHeight(double&& /*height*/);
    const double & getHeight() const;
    const double & height() const{ return getHeight();}
public:
    void setFont(const QFont& /*font*/);
    void setFont(QFont&& /*font*/);
    const QFont & getFont() const;
    const QFont & font() const{ return getFont();}
    const QFontMetricsF &fontMetrics()const;
    const QFontMetricsF &getFontMetrics()const { return fontMetrics(); }
private:
    template<typename _t_NOVELFILE_t__>
    void _p_setNovelFile(_t_NOVELFILE_t__ && /*novelFile*/);
    template<typename _t_WIDTH_t__>
    void _p_setWidth(_t_WIDTH_t__ && /*width*/);
    template<typename _t_HEIGHT_t__>
    void _p_setHeight(_t_HEIGHT_t__ && /*height*/);
    template<typename _t_FONT_t__>
    void _p_setFont(_t_FONT_t__ && /*font*/);
};

/*zone_namespace_end*/

#endif



