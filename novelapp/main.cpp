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
   
    MainWindow window;
    window.setNovelLayout(layout);
    layout->setNovelFile(file);
    window.showMaximized();
    auto font=layout->font();
    font.setPixelSize(26);
    layout->setFont(font);
    layout->setNeedLayout(true);

    return app.exec();
}
