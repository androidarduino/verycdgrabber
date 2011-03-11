#include "extractor.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QPageExtractor extractor("test.ini", "163_news");
    //QPageExtractorTester tester(&extractor);
    extractor.load();
    return app.exec();
}
