/*NovelFile cpp*/
#include "NovelFile.hpp"
#include "private/NovelFileData.hpp"
#include "private/NovelFilePrivateFunction.hpp"
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::NovelFileData *,0>(const NovelFile * arg) ->zone_data::NovelFileData *{
    return const_cast<NovelFile *>(arg)->thisData_.get();
}

template<>
inline auto getThisData<const zone_data::NovelFileData *,1>(const NovelFile * arg) ->const zone_data::NovelFileData *{
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::NovelFileData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::NovelFileData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
NovelFileData::NovelFileData() {
}


NovelFileData::~NovelFileData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

NovelFile::NovelFile(QObject * parent):
    QObject(parent),
    thisData_(std::make_shared<zone_data::NovelFileData>()) {
}


NovelFile::~NovelFile() {
}

NovelFile::Integer NovelFile::size() const {
    zone_const_this_data(this);
    return Integer(var_this_data->paragraphs.size());
}

const std::list<QString> & NovelFile::getParagraphs() const{
    zone_const_this_data(this);
    return var_this_data->paragraphs;
}

template<typename _t_PARAGRAPHS_t__>
void NovelFile::_p_setParagraphs(_t_PARAGRAPHS_t__ &&_paragraphs_){
    zone_this_data(this);
    std::list<QString> var;
    for(auto &i:_paragraphs_){
        auto varTemp=process(i);
        if (varTemp.second) {
            var.push_back(std::move(varTemp.first));
        }
    }
    var_this_data->paragraphs=std::move(var);
    paragraphsChanged();
}

std::pair<QString,bool> NovelFile::process(const QString &arg) {
    if (arg.isEmpty()) { return{ {},false }; }
    auto var=arg.trimmed();
    if (var.isEmpty()) { return{ {},false }; }
    return {std::move(var),true};
}

void NovelFile::setParagraphs(const std::list<QString>&_paragraphs_){
    _p_setParagraphs(_paragraphs_);
}

void NovelFile::setParagraphs(std::list<QString>&&_paragraphs_){
    _p_setParagraphs(std::move(_paragraphs_));
}

void NovelFile::setFile(const QString & arg) {
    QFile varFile(arg);
    std::list<QString> varParagraphs;
    if(varFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream varStream(&varFile);
        while (varStream.atEnd()==false) {
            QString varLine=varStream.readLine();
            varParagraphs.push_back(std::move(varLine));
        }
    }
    setParagraphs(std::move(varParagraphs));
}

void NovelFile::setFile(QString &&arg) {
    const QString var(std::move(arg));
    setFile(var);
}

/*zone_namespace_end*/


