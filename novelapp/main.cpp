#include "MainWindow.hpp"
#include <QApplication>
#include "NovelFile.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::vector<QString> test;
    NovelFile file;
    file.setParagraphs(std::move(test));

    MainWindow window;
    window.show();

    return app.exec();
}
