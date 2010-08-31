#include "verycd.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
/*    VeryCDGrabber grabber;
    VeryCDHistory history;
    grabber.setHistory(&history);
    QApplication::connect(&grabber, SIGNAL(finished()), &app, SLOT(quit()));
    grabber.update();
    */
    VeryCDListPage page1("ziliao.exp", 10);
    return app.exec();
}
