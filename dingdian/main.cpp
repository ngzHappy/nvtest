#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <stdexcept>
#include <QtCore/qresource.h>
#include <QtCore/qbytearray.h>
#include <QtGui/qpainter.h>
#include <QtCore/qfile.h>
#include <QtGui/QDesktopServices>
#include <QtCore/qurl.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qtextcodec.h>
#include "DingDianSytle.hpp"
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

    do{
        QString styleName=
            QApplication::applicationDirPath()+"/style.lua";
        QFileInfo info{styleName};
        if (info.exists()) { break; }
        QFile file{styleName};
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream stream{&file};
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        QResource source(":/style.lua");
        QByteArray source_data(
            reinterpret_cast<const char *>(source.data()),
            source.size());
        if(source.isCompressed()){
            source_data=qUncompress(source_data);
        }
        stream<<source_data;
    } while (false);

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

    {
        auto style=DingDianSytle::instance();
        style->loadFile(app.applicationDirPath()+"/style.lua");
        app.setStyleSheet(style->styleSheet());
    }

    MainWindow window;

    if (argc>1) {
        window.setMainPage(QString::fromUtf8(argv[1]));
    }
    else {
        QDesktopServices::openUrl(QString("http://www.23wx.com/"));
        window.setMainPage(
            QString::fromUtf8(u8R"(http://www.23wx.com/html/18/18191/)"));
    }

    window.showMaximized();

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


