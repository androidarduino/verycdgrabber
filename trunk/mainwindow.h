#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "verycd.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow();
        void addPage(VeryCDListPage* page);
    private:
        Ui::MainWindow win;
        QList<VeryCDListPage*> pages;
    public slots:
        void updated();
};

#endif
