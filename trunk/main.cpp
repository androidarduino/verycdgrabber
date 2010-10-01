#include "mainwindow.h"
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
    MainWindow win;
    
    
    VeryCDHistory history;
    QSet<QString> set;
    set<<"test1"<<"test2"<<"test3";
    history.appendHistory(set);
    
    
    win.show();
    return app.exec();
}
