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
    VeryCDListPage page1("/sto/datum/page5");
    VeryCDListPage page2("/sto/datum/page6");
    VeryCDListPage page3("/sto/datum/page7");
    VeryCDListPage page4("/sto/datum/page8");
    return app.exec();
}
