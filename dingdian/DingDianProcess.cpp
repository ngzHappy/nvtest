/*DingDianProcess cpp*/
#include "DingDianProcess.hpp"
#include "private/DingDianProcessData.hpp"
#include "private/DingDianProcessPrivateFunction.hpp"
#include <gumbo/gumbo.h>

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::DingDianProcessData *,0>(const DingDianProcess * arg) ->zone_data::DingDianProcessData *{
    return const_cast<DingDianProcess *>(arg)->thisData_.get(); 
}

template<>
inline auto getThisData<const zone_data::DingDianProcessData *,1>(const DingDianProcess * arg) ->const zone_data::DingDianProcessData *{ 
    return arg->thisData_.get();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=getThisData<zone_data::DingDianProcessData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=getThisData<const zone_data::DingDianProcessData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
DingDianProcessData::DingDianProcessData() {
}


DingDianProcessData::~DingDianProcessData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/
void processMainPage(
    const DingDianProcess * argThis,
    DingDianProcess::MainPage & varAns
) {
    zone_const_this_data(argThis);
    varAns.items.clear();
    class _GumboParser {
    public:
        GumboOutput * parser=nullptr;
        const QByteArray html;
        _GumboParser(const QByteArray & var_html):html(var_html) {
            parser=gumbo_parse_with_options(
                &kGumboDefaultOptions,
                html.data(),html.size());
        }
        ~_GumboParser() { gumbo_destroy_output(&kGumboDefaultOptions,parser); }
    };
    std::shared_ptr<GumboOutput> parser;
    {
        auto varTemp=std::make_shared<_GumboParser>(var_this_data->mainPage);
        parser=std::shared_ptr<GumboOutput>(varTemp,
            varTemp->parser);
    }
    


}
/********************************zone_function********************************/
}

DingDianProcess::DingDianProcess():thisData_(ThisDataType(
                         new zone_data::DingDianProcessData,
                         [](zone_data::DingDianProcessData *arg){delete arg;})) {
}

DingDianProcess::~DingDianProcess() {
}

const QByteArray & DingDianProcess::getMainPage() const{
    zone_const_this_data(this);
    return var_this_data->mainPage;
}

template<typename _t_MAINPAGE_t__>
void DingDianProcess::_p_setMainPage(_t_MAINPAGE_t__ &&_mainPage_){
    zone_this_data(this);
    var_this_data->mainPage=std::forward<_t_MAINPAGE_t__>(_mainPage_);
}

auto DingDianProcess::processMainPage() const ->MainPage{
    MainPage varAns;
    zone_const_this_data(this);
    if (var_this_data->mainPage.isEmpty()) {
        return std::move(varAns);
    }
    zone_private_function::processMainPage(this,varAns);
    return std::move(varAns);
}

void DingDianProcess::setMainPage(const QByteArray&_mainPage_){
    _p_setMainPage(_mainPage_);
}

void DingDianProcess::setMainPage(QByteArray&&_mainPage_){
    _p_setMainPage(std::move(_mainPage_));
}

/*zone_namespace_end*/


