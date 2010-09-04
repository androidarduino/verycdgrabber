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
        void page(int pageNum);
        void nextPage();
        void prevPage();
        void firstPage();
        void appendToCart();
        void cartToClipboard();

        int pageNumber;
        QList<VeryCDDetailPage*> cart;
    public slots:
        void updated();

private slots:
    void on_actionNext_activated();
};

#endif
