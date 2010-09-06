#include "mainwindow.h"

MainWindow::MainWindow()
{
    win.setupUi(this);
    firstPage();
    connect(win.treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(loadLink()));
}

void MainWindow::getLinks(bool updateCart)
{
    QList<QTreeWidgetItem*> items=win.treeWidget->selectedItems();
    if(updateCart)
        cart.pages.clear();
    for(int i=0;i<items.size();i++)
    {
        VeryCDItem* vi= dynamic_cast<VeryCDItem*>(items[i]);
        if(vi==NULL)
            continue;
        vi->page->load();
        if(updateCart)
            cart.pages<<vi->page;
    }
}

void MainWindow::loadLink()
{
    getLinks(false);
}

void MainWindow::addPage(VeryCDListPage* page)
{
    pages<<page;
    connect(page, SIGNAL(updated()), this, SLOT(updated()));
}

void MainWindow::firstPage()
{
    page(21);
}

void MainWindow::page(int pageNum)
{
    pageNumber=pageNum;
    qDebug()<<pageNum<<"here";
    VeryCDListPage* page=new VeryCDListPage("ziliao.exp",pageNum);
    qDebug()<<pageNum<<"added";
    addPage(page);
}

VeryCDItem::VeryCDItem(QTreeWidget* parent, QStringList& data, VeryCDDetailPage* pagelink):QTreeWidgetItem(parent, data)
{
    page=pagelink;
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
            VeryCDItem* item=new VeryCDItem((QTreeWidget*)0, data, (*detailPages)[j]);
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

bool VeryCDItem::operator <(const QTreeWidgetItem &other)const
{
    int column = treeWidget()->sortColumn();
    if(column==1)//files count
        return text(column).toInt() < other.text(column).toInt();
    if(column==2)//size
    {
        QString col, num, unit;
        col=text(column);
        num=col.left(col.length()-2);
        unit=col.right(2);
        float factor=1;//assume KB
        if(unit=="MB")
            factor=1024;
        if(unit=="GB")
            factor=1024*1024;
        if(unit=="TB")
            factor=1024*1024*1024;
        float resultThis=num.toFloat()*factor;
        col=other.text(column);
        num=col.left(col.length()-2);
        unit=col.right(2);
        factor=1;//assume KB
        if(unit=="MB")
            factor=1024;
        if(unit=="GB")
            factor=1024*1024;
        if(unit=="TB")
            factor=1024*1024*1024;
        float resultOther=num.toFloat()*factor;
        return resultThis < resultOther;
    }
    return QTreeWidgetItem::operator<(other);
}


void MainWindow::on_actionView_cart_activated()
{
    getLinks(true);
    cart.exec();
}

void MainWindow::on_actionPage_Range_activated()
{

}
