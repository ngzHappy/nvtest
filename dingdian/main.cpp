#include "MainWindow.hpp"
#include <QApplication>
#include <NovelFile.hpp>
#include <NovelLayout.hpp>
#include <HtmlDownLoad.hpp>
#include <QtCore/qurl.h>
#include <QtCore/qdebug.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    {
        auto file=std::make_shared<NovelFile>();
        file->setFile(R"(D:\opencv_project_test\b.txt)");
        auto layout=std::make_shared<NovelLayout>();

        window.setNovelLayout(layout);
        layout->setNovelFile(file);
        window.show();
        auto font=layout->font();
        font.setPixelSize(26);
        layout->setFont(font);
        layout->setNeedLayout(true);
    }

    HtmlDownLoad downLoad;
    downLoad.connect(&downLoad,&HtmlDownLoad::downLoadFinished,
        [](QByteArray arg,auto) {
        qDebug()<<arg.size();
    });
    downLoad.download(QUrl("http://www.baidu.com"));

    return app.exec();
}
