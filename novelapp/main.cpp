#include "MainWindow.hpp"
#include <QApplication>
#include "NovelFile.hpp"
#include "NovelLayout.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    auto file=std::make_shared<NovelFile>();
    file->setFile(R"(D:\opencv_project_test\a.txt)");
    NovelLayout layout;
    layout.setNovelFile(file);

    MainWindow window;
    window.show();

    return app.exec();
}
