#include "MainWindow.hpp"
#include <QApplication>
#include <NovelFile.hpp>
#include <NovelLayout.hpp>
#include <HtmlDownLoad.hpp>
#include <QtCore/qurl.h>
#include <QtCore/qdebug.h>
#include <QtCore/qfile.h>
#include "DingDianProcess.hpp"

int main(int argc,char *argv[]) {
    QApplication app(argc,argv);

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
            {
                QFile file("xxx.txt");
                file.open(QIODevice::WriteOnly);
                file.write(arg);
            }

            DingDianProcess process;
            process.setMainPage(arg);
            process.processMainPage();

    });
    downLoad.download(QUrl("http://www.23wx.com/html/18/18191/"));

    HtmlDownLoad downLoad1;
    downLoad1.connect(&downLoad1,&HtmlDownLoad::downLoadFinished,
        [](QByteArray arg,auto) {
            {
                QFile file("xxx1.txt");
                file.open(QIODevice::WriteOnly);
                file.write(arg);
            }

            DingDianProcess process;
            process.processAPage(arg);

    });
    downLoad1.download(QUrl("http://m.23wx.com/html/18/18191/25448822.html"));

    return app.exec();
}



