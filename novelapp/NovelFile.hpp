/*NovelFile hpp*/
#if !defined(____PRAGMA_ONCE_HPP_NOVELFILE_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_NOVELFILE_0___HPP_0x00_() 1

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
class NovelFileData;
}
class NovelFile;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const NovelFile *)->_TYPE_TAG_ ;

class NovelFile {
/*macro_no_copy(NovelFile);*/
protected:
    std::shared_ptr<zone_data::NovelFileData> thisData_;
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const NovelFile *)->_TYPE_TAG_ ;
public:
    explicit NovelFile(decltype(nullptr)) {}
    NovelFile();
    ~NovelFile();

};

/*zone_namespace_end*/

#endif



