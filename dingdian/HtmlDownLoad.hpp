/*HtmlDownLoad hpp*/
#if !defined(____PRAGMA_ONCE_HPP_HTMLDOWNLOAD_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_HTMLDOWNLOAD_0___HPP_0x00_() 1

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
class HtmlDownLoadData;
}
class HtmlDownLoad;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const HtmlDownLoad *)->_TYPE_TAG_ ;

class HtmlDownLoad {
/*macro_no_copy(HtmlDownLoad);*/
protected:
    using ThisDataType=std::unique_ptr<zone_data::HtmlDownLoadData,void(*)(zone_data::HtmlDownLoadData *)>;
    ThisDataType thisData_{nullptr,nullptr};
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const HtmlDownLoad *)->_TYPE_TAG_ ;
public:
    explicit HtmlDownLoad(decltype(nullptr)) {}
    HtmlDownLoad();
    ~HtmlDownLoad();

};

/*zone_namespace_end*/

#endif



