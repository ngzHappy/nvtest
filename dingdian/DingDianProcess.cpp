/*DingDianProcess cpp*/
#include "DingDianProcess.hpp"
#include "private/DingDianProcessData.hpp"
#include "private/DingDianProcessPrivateFunction.hpp"
#include <gumbo/gumbo.h>
#include <QtCore/qbuffer.h>
#include <QtCore/qtextcodec.h>
#include <list>
#include <string>
#include <regex>
using namespace std::literals;

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::DingDianProcessData *,0>(const DingDianProcess * arg) ->zone_data::DingDianProcessData * {
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

bool genUrl(const char * argText,QByteArray & ans) {
    QByteArray varText(argText);
    if (varText.indexOf("url=")>0) {
        auto values=varText.split(';');
        for (auto i:values) {
            i=i.trimmed();
            if (i.startsWith("url=")) {
                ans=i.mid(4);
                if (ans.isEmpty()) { continue; }
                if (ans.endsWith('/')||ans.endsWith('\\')) { return true; }
                ans.push_back('/');
                return true;
            }
        }
    }
    return false;
}

void readColumn(GumboNode *argColumn,DingDianProcess::MainPage & varAns) {
    auto &children=argColumn->v.element.children;
    if (children.length==1) {
        auto * varItem=reinterpret_cast<GumboNode *>(children.data[0]);
        if (varItem->type!=GUMBO_NODE_ELEMENT) { return; }
        auto * attribute=gumbo_get_attribute(&varItem->v.element.attributes,"href");
        if (attribute==nullptr) { return; }
        DingDianProcess::MainPage::Item item;
        item.url=QString::fromUtf8(attribute->value).trimmed();
        if (varItem->v.element.children.length==1) {
            auto * textItem=reinterpret_cast<GumboNode *>(
                varItem->v.element.children.data[0]);
            if (textItem->type==GUMBO_NODE_TEXT) {
                item.title=QString::fromUtf8(
                    textItem->v.text.text).trimmed();
            }
            else { return; }
        }
        else { return; }
        varAns.items.push_back(std::move(item));
    }
}

void readRow(GumboNode *argRow,DingDianProcess::MainPage & varAns) {
    auto &children=argRow->v.element.children;
    using IntType=std::remove_const_t<std::remove_reference_t<decltype(children.length)>>;
    for (IntType i=0; i<children.length; ++i) {
        auto * varColumn=reinterpret_cast<GumboNode *>(children.data[i]);
        readColumn(varColumn,varAns);
    }
}

void processMainPage(
    const DingDianProcess * argThis,
    DingDianProcess::MainPage & varAns
) {
    zone_const_this_data(argThis);
    varAns.items.clear();
    varAns.title.clear();

    /*搜索并设置title*/
    {
        const static std::regex reg(u8R"(<dd><h1>(.*?)</h1></dd>)");
        const char * varBegin=argThis->mainPage().constBegin();
        const char * varEnd=argThis->mainPage().constEnd();
        std::cmatch rvarAns;
        if (std::regex_search(varBegin,varEnd,rvarAns,reg)) {
            varAns.title=QString::fromUtf8(rvarAns[1].first,rvarAns[1].length())
                .trimmed();
        }
        else {
            qDebug()<<"html format error!";
            return;
        }

    }

    /*解析html*/
    class _GumboParser {
    public:
        GumboOutput * parser=nullptr;
        const QByteArray html;
        _GumboParser(const QByteArray & var_html):html(var_html) {
            parser=gumbo_parse_with_options(
                fkGumboDefaultOptions(),
                html.data(),html.size());
        }
        ~_GumboParser() { gumbo_destroy_output(fkGumboDefaultOptions(),parser); }
    };
    std::shared_ptr<GumboOutput> parser;
    {
        auto varTemp=std::make_shared<_GumboParser>(var_this_data->mainPage);
        parser=std::shared_ptr<GumboOutput>(varTemp,
            varTemp->parser);
    }

    GumboNode * bodyNode=nullptr;
    QByteArray url;
    {
        GumboNode * rootNode=parser->root;
        if (rootNode==nullptr) { return; }

        {
            std::list<GumboNode *> nodes;
            nodes.push_back(rootNode);
            while (nodes.empty()==false) {

                rootNode=nodes.front(); nodes.pop_front();
                if (rootNode->type!=GumboNodeType::GUMBO_NODE_ELEMENT) {
                    continue;
                }

                auto & element=rootNode->v.element;

                if (element.tag==GUMBO_TAG_BODY) {
                    bodyNode=rootNode;
                    if (url.isEmpty()==false) { break; }
                }
                else if (element.tag==GUMBO_TAG_META) {
                    auto * attribute=gumbo_get_attribute(&element.attributes,"content");
                    if (attribute) {
                        if (genUrl(attribute->value,url)) {
                            if (bodyNode) { break; }
                        }
                    }
                }
                else {
                    auto &children=rootNode->v.element.children;
                    using IntType=std::remove_const_t<std::remove_reference_t<decltype(children.length)>>;
                    for (IntType i=0; i<children.length; ++i) {
                        nodes.push_back(reinterpret_cast<GumboNode *>(children.data[i]));
                    }
                }

            }
        }
    }

    if (bodyNode==nullptr) { return; }
    if (url.isEmpty()) { return; }
    GumboNode * tableNode=nullptr;
    /*table*/
    {
        std::list<GumboNode *> nodes;
        nodes.push_back(bodyNode);

        while (nodes.empty()==false) {
            GumboNode * rootNode=nodes.front(); nodes.pop_front();
            if (rootNode->type!=GumboNodeType::GUMBO_NODE_ELEMENT) {
                continue;
            }

            if (rootNode->v.element.tag==GUMBO_TAG_TABLE) {
                tableNode=rootNode; break;
            }
            else {
                auto &children=rootNode->v.element.children;
                using IntType=std::remove_const_t<std::remove_reference_t<decltype(children.length)>>;
                for (IntType i=0; i<children.length; ++i) {
                    nodes.push_back(reinterpret_cast<GumboNode *>(children.data[i]));
                }
            }

        }

    }

    if (tableNode==nullptr) { return; }

    {
        std::list<GumboNode *> nodes;
        nodes.push_back(tableNode);

        varAns.items.reserve(1024*3);
        while (nodes.empty()==false) {
            GumboNode * rootNode=nodes.front(); nodes.pop_front();
            if (rootNode->type!=GumboNodeType::GUMBO_NODE_ELEMENT) {
                continue;
            }

            if (rootNode->v.element.tag==GUMBO_TAG_TR) {
                readRow(rootNode,varAns);
            }
            else {
                auto &children=rootNode->v.element.children;
                using IntType=std::remove_const_t<std::remove_reference_t<decltype(children.length)>>;
                for (IntType i=0; i<children.length; ++i) {
                    nodes.push_back(reinterpret_cast<GumboNode *>(children.data[i]));
                }
            }

        }

    }

    if (varAns.items.isEmpty()==false) {
        for (auto & i:varAns.items) {
            i.url=url+i.url;
        }
    }
}
/********************************zone_function********************************/
}

DingDianProcess::DingDianProcess():thisData_(ThisDataType(
    new zone_data::DingDianProcessData,
    [](zone_data::DingDianProcessData *arg) {delete arg; })) {
}

DingDianProcess::~DingDianProcess() {
}

const QByteArray & DingDianProcess::getMainPage() const {
    zone_const_this_data(this);
    return var_this_data->mainPage;
}

template<typename _t_MAINPAGE_t__>
void DingDianProcess::_p_setMainPage(_t_MAINPAGE_t__ &&_mainPage_) {
    zone_this_data(this);

    /*转到utf8编码*/
    QByteArray varMainPage=std::forward<_t_MAINPAGE_t__>(_mainPage_);
    do {
        QTextCodec * varGBKCodeC=QTextCodec::codecForHtml(varMainPage);
        if (varGBKCodeC==QTextCodec::codecForName("UTF-8")) { break; }
        if (varGBKCodeC) {
            QString varMainPageUtf16=varGBKCodeC->toUnicode(varMainPage);
            varMainPage=varMainPageUtf16.toUtf8();
        }
    } while (false);

    var_this_data->mainPage=std::move(varMainPage);
}

auto DingDianProcess::processMainPage() const ->MainPage {
    MainPage varAns;
    zone_const_this_data(this);
    if (var_this_data->mainPage.isEmpty()) {
        return std::move(varAns);
    }
    zone_private_function::processMainPage(this,varAns);
    return std::move(varAns);
}

void DingDianProcess::setMainPage(const QByteArray&_mainPage_) {
    _p_setMainPage(_mainPage_);
}

void DingDianProcess::setMainPage(QByteArray&&_mainPage_) {
    _p_setMainPage(std::move(_mainPage_));
}

std::list<QString> DingDianProcess::processAPage(const QByteArray&argHtml)const {
    std::list<QString> varAns;
    if (argHtml.isEmpty()) { return{}; }

    QByteArray varHtml=argHtml;
    do {
        /*转到utf8编码*/
        QTextCodec * varGBKCodeC=QTextCodec::codecForHtml(varHtml);
        if (varGBKCodeC==QTextCodec::codecForName("UTF-8")) { break; }
        if (varGBKCodeC) {
            QString varMainPageUtf16=varGBKCodeC->toUnicode(varHtml);
            varHtml=varMainPageUtf16.toUtf8();
        }

    } while (false);

    /*解析html*/
    class _GumboParser {
    public:
        GumboOutput * parser=nullptr;
        const QByteArray html;
        _GumboParser(const QByteArray & var_html):html(var_html) {
            parser=gumbo_parse_with_options(
                fkGumboDefaultOptions(),
                html.data(),html.size());
        }
        ~_GumboParser() { gumbo_destroy_output(fkGumboDefaultOptions(),parser); }
    };
    std::shared_ptr<GumboOutput> parser;
    {
        auto varTemp=std::make_shared<_GumboParser>(varHtml);
        parser=std::shared_ptr<GumboOutput>(varTemp,
            varTemp->parser);
    }

    GumboNode * rootNode=parser->root;
    if (rootNode==nullptr) { return{}; }
    GumboNode * textNode=nullptr;

    {
        std::list<GumboNode *>nodes;
        nodes.push_back(rootNode);

        while (nodes.empty()==false) {
            rootNode=nodes.front(); nodes.pop_front();
            if (rootNode->type!=GUMBO_NODE_ELEMENT) { continue; }
            auto &element=rootNode->v.element;

            if (element.tag==GUMBO_TAG_DIV) {
                auto * att_text=gumbo_get_attribute(&element.attributes,"class");
                if (att_text) {
                    auto * att_id=gumbo_get_attribute(&element.attributes,"id");
                    if (att_id) {
                        if (att_id->value=="txt"s) {
                            if (att_text->value=="txt"s) {
                                textNode=rootNode;
                                break;
                            }
                        }
                    }
                }
            }

            auto &children=rootNode->v.element.children;
            using IntType=std::remove_const_t<std::remove_reference_t<decltype(children.length)>>;
            for (IntType i=0; i<children.length; ++i) {
                nodes.push_back(reinterpret_cast<GumboNode *>(children.data[i]));
            }

        }

    }

    if (textNode==nullptr) { return{}; }

    if (textNode->v.element.children.length<=0) { return{}; }

    using IntType=std::remove_const_t<std::remove_reference_t<
        decltype(textNode->v.element.children.length)>>;
    for (IntType i=0; i<textNode->v.element.children.length; ++i) {
        GumboNode * node=
            reinterpret_cast<GumboNode *>(textNode->v.element.children.data[i]);
        if (node->type==GUMBO_NODE_TEXT) {
            varAns.push_back(QString::fromUtf8(node->v.text.text)
            .trimmed());
        }
    }

    return std::move(varAns);
}

/*zone_namespace_end*/


