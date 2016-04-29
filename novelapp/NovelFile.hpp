/*NovelFile hpp*/
#if !defined(____PRAGMA_ONCE_HPP_NOVELFILE_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_NOVELFILE_0___HPP_0x00_() 1

#include <QtCore/qstring.h>
#include <QtCore/qobject.h>
#include <list>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <iterator>

/*zone_namespace_begin*/

namespace zone_data {
class NovelFileData;
}
class NovelFile;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const NovelFile *)->_TYPE_TAG_;

class NovelFile :public QObject {
    Q_OBJECT

private:
    template<typename ...>using void_t=void;
signals:

    void paragraphsChanged();
protected:
    std::shared_ptr<zone_data::NovelFileData> thisData_;
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const NovelFile *)->_TYPE_TAG_;
public:

    explicit NovelFile(QObject * /**/=nullptr);
    virtual ~NovelFile();

    typedef std::int32_t Integer;
    Integer size()const;

    virtual std::pair<QString,bool> process(const QString &);
    
    auto begin()const { return paragraphs().cbegin(); }
    auto end()const { return paragraphs().cend(); }

    auto cbegin() const { return paragraphs().cbegin(); }
    auto cend()const { return paragraphs().cend(); }

    auto rbegin()const { return paragraphs().crbegin(); }
    auto rend()const { return paragraphs().crend(); }

    auto crbegin()const { return paragraphs().crbegin(); }
    auto crend()const { return paragraphs().crend(); }
public:
    void setFile(const QString &);
    void setFile(QString &&);
    template<typename _readLine_>
    auto setFile(_readLine_ &&)->void_t<decltype(std::declval<_readLine_>().readLine())>;
public:
    void setParagraphs(const QString &);
    void setParagraphs(QString &&);
    void setParagraphs(const std::list<QString>& /*paragraphs*/);
    void setParagraphs(std::list<QString>&& /*paragraphs*/);
    const std::list<QString> & getParagraphs() const;
    const std::list<QString> & paragraphs() const { return getParagraphs(); }
    template<typename _Itb_,typename _Ite_>
    void setParagraphs(_Itb_,_Ite_ &&);
    template<typename _List_>
    auto setParagraphs(const _List_ &)->void_t<decltype(std::declval<const _List_>().begin())>;
    template<typename _List_>
    auto setParagraphs(_List_ &)->void_t<decltype(std::declval<_List_>().begin())>;
    template<typename _List_>
    auto setParagraphs(_List_ &&)->void_t<decltype(std::declval<_List_>().begin())>;
private:
    template<typename _t_PARAGRAPHS_t__>
    void _p_setParagraphs(_t_PARAGRAPHS_t__ && /*paragraphs*/);
};

template<typename _Itb_,typename _Ite_>
inline void NovelFile::setParagraphs(_Itb_ argB,_Ite_ && argE) {
    std::list<QString> var;
    for (; argB!=argE; ++argB) { var.push_back(*argB); }
    setParagraphs(std::move(var));
}

inline void NovelFile::setParagraphs(const QString &argP0) {
    std::list<QString> var; var.push_back(argP0);
    setParagraphs(std::move(var));
}
inline void NovelFile::setParagraphs(QString &&argP0) {
    std::list<QString> var; var.push_back(std::move(argP0));
    setParagraphs(std::move(var));
}

template<typename _List_>
inline auto NovelFile::setParagraphs(const _List_ &arg)->void_t<decltype(std::declval<const _List_>().begin())> {
    setParagraphs(arg.begin(),arg.end());
}

template<typename _List_>
inline auto NovelFile::setParagraphs(_List_ &arg)->void_t<decltype(std::declval<_List_>().begin())> {
    setParagraphs(arg.begin(),arg.end());
}

template<typename _List_>
inline auto NovelFile::setParagraphs(_List_ &&arg)->void_t<decltype(std::declval<_List_>().begin())> {
    setParagraphs(
        std::make_move_iterator(arg.begin()),
        std::make_move_iterator(arg.end()));
}

template<typename _readLine_>
inline auto NovelFile::setFile(_readLine_ && arg)->void_t<decltype(std::declval<_readLine_>().readLine())> {
    std::list<QString> var;
    while (arg.atEnd()==false) { var.push_back(arg.readLine()); }
    setParagraphs(std::move(var));
}
/*zone_namespace_end*/

#endif



