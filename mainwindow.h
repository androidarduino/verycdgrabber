#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
  todo:
  1. Subclass tree widget item, resolve the sorting problem
  2. Add function to populate links to the cart
  3. Function the cart with retrieving ed2k links
  4. When the link is retrieved, mark it as a seperate color
  5. User can manually retry getting the links
  6. Copy all the ed2k links to the clipboard/text file
*/

#include "ui_mainwindow.h"
#include "verycd.h"
#include "cartwindow.h"

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
        void firstPage();
        void getLinks();
        void cartToClipboard();
        CartWindow cart;
        int pageNumber;
    public slots:
        void updated();

private slots:
    void on_actionPrevious_activated();
    void on_actionNext_activated();
};

class VeryCDItem: public QTreeWidgetItem
{
    public:
        VeryCDItem(QTreeWidget* parent, QStringList& data, VeryCDDetailPage* pagelink);
        VeryCDDetailPage* page;
    private:
        bool operator<(const QTreeWidgetItem& other)const;
};

#endif
