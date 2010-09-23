#include <QMimeData>
#include "cartwindow.h"

CartWindow::CartWindow()
{
    dlg.setupUi(this);
    connect(dlg.downButton, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
}

void CartWindow::copyToClipboard()
{
    QString links="";
    for(int i=0;i<dlg.treeWidget->topLevelItemCount();i++)
    {
        links+=QString("%1\r\n").arg(dlg.treeWidget->topLevelItem(i)->text(2));
    }
    QMimeData data;
    data.setHtml(links);
    //QApplication::clipboard()->setMimeData(&data);
    QApplication::clipboard()->setText(links);
    qDebug()<<links<<" are the links";
}

int CartWindow::exec()
{
    update();
    return QDialog::exec();
}

bool CartItem::operator <(const QTreeWidgetItem& other)const
{
    int column = treeWidget()->sortColumn();
    if(column==1)//size
    {
        QString col, num, unit;
        col=text(column);
        num=col.left(col.length()-2);
        unit=col.right(2);
        float factor=1;//assume KB
        if(unit=="B")
            factor=1/1024;
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
        if(unit=="B")
            factor=1/1024;
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

CartItem::CartItem(QTreeWidget* parent, QStringList& data):QTreeWidgetItem(parent, data)
{

}



void CartWindow::update()
{
    QString statusLoad;
    int statusFiles=0;
    float statusSize=0;
    dlg.treeWidget->clear();
    int unloadedPage=0;
    for(int i=0;i<pages.size();i++)
    {
        if(pages[i]->loaded)//if the links are loaded
        {
            foreach(Ed2kItem* it, pages[i]->items)
            {
                QStringList data;
                data<<it->name<<it->size<<it->link<<pages[i]->title;
                CartItem* linkitem=new CartItem((QTreeWidget*)0, data);
                dlg.treeWidget->addTopLevelItem(linkitem);
                //calculate the size and count
                statusFiles++;
                float factor=1.0;
                float num=it->size.left(it->size.length()-2).toFloat();
                QString unit=it->size.right(2);
                if(unit=="MB")
                    factor=1024;
                if(unit=="GB")
                    factor=1024*1024;
                if(unit=="TB")
                    factor=1024*1024*1024;
                statusSize+=num*factor/1024;
            }
        }
        else
            unloadedPage++;
    }
    if(unloadedPage>0)
        statusLoad= QString("%1 pages still loading, please wait...").arg(unloadedPage);
    else
        statusLoad="All pages loaded";
    dlg.status->setText(QString("Total %1 MB in %2 files. %3").arg(statusSize).arg(statusFiles).arg(statusLoad));
}
