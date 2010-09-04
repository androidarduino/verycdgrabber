#include "mainwindow.h"

MainWindow::MainWindow()
{
    win.setupUi(this);
    firstPage();
}

void MainWindow::addPage(VeryCDListPage* page)
{
    pages<<page;
    connect(page, SIGNAL(updated()), this, SLOT(updated()));
}

void MainWindow::firstPage()
{
    page(1);
}

void MainWindow::page(int pageNum)
{
    pageNumber=pageNum;
    qDebug()<<pageNum<<"here";
    VeryCDListPage* page=new VeryCDListPage("ziliao.exp",pageNum);
    qDebug()<<pageNum<<"added";
    addPage(page);
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
        QTreeWidgetItem* pageItem=new QTreeWidgetItem(0);
        pageItem->setText(0, QString("Page %1").arg(pages[i]->pageNum));
        pageItem->addChildren(items);
        bool duplicate=false;
        for(int k=0;k<win.treeWidget->topLevelItemCount();k++)
            if(win.treeWidget->topLevelItem(k)->text(0)==pageItem->text(0))
                duplicate=true;
        if(!duplicate&&pages[i]->loaded)
            win.treeWidget->insertTopLevelItem(0, pageItem);
        //else
            //delete pageItem;
    }
}

void MainWindow::on_actionNext_activated()
{
    page(++pageNumber);
}

void MainWindow::on_actionPrevious_activated()
{
    if(--pageNumber>1)
        page(pageNumber);

}
