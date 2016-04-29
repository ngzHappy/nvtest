#include "MainWindow.hpp"
#include <QApplication>
#include "NovelFile.hpp"
#include "NovelLayout.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto file=std::make_shared<NovelFile>();
    file->setFile(R"(D:\opencv_project_test\a.txt)");
    auto layout=std::make_shared<NovelLayout>();
    layout->setNovelFile(file);

    MainWindow window;
    window.setNovelLayout(layout);
    window.show();

    return app.exec();
}
