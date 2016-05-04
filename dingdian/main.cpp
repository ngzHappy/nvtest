#include "MainWindow.hpp"
#include <QApplication>
#include <stdexcept>
#include <QtGui/qpainter.h>
#include <QtCore/qfile.h>
#include <QtGui/QDesktopServices>
#include <QtCore/qurl.h>

static void drawAndSaveHelp() {

    {
        QFile file(qApp->applicationDirPath()+"/help.txt");
        if (file.open(QIODevice::WriteOnly)) {
            file.write("http://www.23wx.com/");
            file.write("\n");
        }
        else {
            qDebug()<<"can not create file???";
            return;
        }
    }

    QDesktopServices::openUrl(QString("http://www.23wx.com/"));

    {
        QImage image{ 512,80,QImage::Format_RGBA8888 };
        image.fill(QColor(0,0,0,0));

        QPainter painter(&image);

        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.setRenderHint(QPainter::TextAntialiasing);

        {
            auto font=painter.font();
            font.setPixelSize(22);
            painter.setFont(font);
        }

        painter.drawText(
            20,
            painter.fontMetrics().ascent(),
            QString::fromUtf8(u8R"(
默认:http://www.23wx.com/html/18/18191/
)"));

        painter.drawText(
            20,
            50+painter.fontMetrics().ascent(),
            QString::fromUtf8(u8R"(
dingdian http://www.23wx.com/html/18/18191/
)"));

        image.save(qApp->applicationDirPath()+"/help.png");
    }

}

int main(int argc,char *argv[]) try{
    QApplication app(argc,argv);

    drawAndSaveHelp();

    MainWindow window;
    window.setStyleSheet(u8R"(MainWindow{background:darkgray;})");
    if (argc>1) {
        window.setMainPage(QString::fromUtf8(argv[1]));
    }
    else {
        window.setMainPage(
            QString::fromUtf8(u8R"(http://www.23wx.com/html/18/18191/)"));
    }
    window.show();

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


