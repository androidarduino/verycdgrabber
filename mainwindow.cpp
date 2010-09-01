#include "mainwindow.h"

MainWindow::MainWindow()
{
    win.setupUi(this);
}

void MainWindow::addPage(VeryCDListPage* page)
{
    pages<<page;
    connect(page, SIGNAL(updated()), this, SLOT(updated()));
}

void MainWindow::updated()
{
    qDebug()<<"........................update message received.......................";
    QList<QTreeWidgetItem *> items;
    for(int i=0;i<pages.size();i++)
    {
        //clear the tree, and insert again
        QList<VeryCDDetailPage*>* detailPages=&(pages[i]->detailPages);
        for(int j=0;j<detailPages->size();j++)
        {
            VeryCDDetailPage & p=*(*detailPages)[j];
            QStringList data;
            data<<p.title<<p.files<<p.size<<p.category;
            data<<p.link<<p.language<<p.year<<p.created;
            data<<p.modified<<p.publisher<<p.picture<<p.comments;
            data<<p.description;
            QTreeWidgetItem* item=new QTreeWidgetItem((QTreeWidget*)0, data);
            items<<item;
        }
    }
    win.treeWidget->insertTopLevelItems(0, items);
}
