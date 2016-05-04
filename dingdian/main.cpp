#include "MainWindow.hpp"
#include <QApplication>
#include <NovelFile.hpp>
#include <NovelLayout.hpp>
#include <HtmlDownLoad.hpp>
#include <QtCore/qurl.h>
#include <QtCore/qdebug.h>
#include <QtCore/qfile.h>
#include <QTimer>
#include "DingDianProcess.hpp"
#include <stdexcept>
static int test=0;

int main(int argc,char *argv[]) try{
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


/*
    HtmlDownLoad downLoad;
    downLoad.connect(&downLoad,&HtmlDownLoad::downLoadFinished,
        [](QByteArray arg,auto) {
            {
                QFile file(QString("xxx%1.txt")
                    .arg(test++,6,10,QChar('0'))
                );
                file.open(QIODevice::WriteOnly);
                file.write(arg);
            }

            DingDianProcess process;
            process.setMainPage(arg);
            auto mainPage= process.processMainPage();
             
            QTimer * timer=new QTimer;
            typedef void(QTimer::*T)();

            class Pack {
            public:
                DingDianProcess::MainPage page;
                QVector<DingDianProcess::MainPage::Item>::iterator pos;
                HtmlDownLoad downLoad;
                Pack() {
                    downLoad.connect(&downLoad,&HtmlDownLoad::downLoadFinished,
                        [](QByteArray arg,auto) {
                           
                            DingDianProcess process;
                            auto xw=process.processAPage(arg);

                            {
                                QFile file(QString("xxx%1.txt")
                                    .arg(test++,6,10,QChar('0'))
                                );
                                file.open(QIODevice::WriteOnly);
                                for (auto &i:xw) { 
                                    file.write(i.toUtf8()+"\n");
                                }
                            }

                    });
                }
            };
            auto pack=std::make_shared<Pack>();
            pack->page=mainPage;
            pack->pos=pack->page.items.begin();
            timer->connect(timer,T(&QTimer::timeout),
                [pack,timer]() {
                if (pack->pos!=pack->page.items.end()) {
                    QUrl url(pack->pos->url);
                    pack->downLoad.download(url);              
                    ++(pack->pos);
                }
            });
            timer->start(100);
    });
    downLoad.download(QUrl("http://www.23wx.com/html/18/18191/"));*/

   

    return app.exec();
}
catch (const std::exception&e) {
    qDebug().noquote()<<e.what();
    return -89999;
}
catch (...) {
    qDebug().noquote()<<"unknow exception";
    return -99999;
}


