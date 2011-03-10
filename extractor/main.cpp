#include "extractor.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QPageExtractor extractor("test.ini", "test");
    QPageExtractorTester tester(&extractor);
    extractor.load();
    return app.exec();
}
