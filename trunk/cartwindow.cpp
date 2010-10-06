//#include <QMimeData>
#include <QFileDialog>
#include <QMessageBox>
#include "cartwindow.h"

CartWindow::CartWindow()
{
    dlg.setupUi(this);
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
    QBrush brush(Qt::lightGray);
    for(int i=0;i<pages.size();i++)
    {
        if(pages[i]->loaded)//if the links are loaded
        {
            foreach(Ed2kItem* it, pages[i]->items)
            {
                QStringList data;
                data<<it->name<<it->size<<it->link<<pages[i]->title;
                CartItem* linkitem=new CartItem((QTreeWidget*)0, data);
                if(d_history.hasLink(it->link))
                {
                    linkitem->setForeground(0, brush);
                    linkitem->setForeground(1, brush);
                    linkitem->setForeground(2, brush);
                    linkitem->setForeground(3, brush);
                }
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

void CartWindow::on_refreshButton_clicked()
{
    update();
}

void CartWindow::on_clearButton_clicked()
{
    dlg.treeWidget->clearSelection();
}

void CartWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save to file"), "links.downlist", tr("Downlist files (*.downlist)"));
    if(fileName=="")
        return;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for(int i=0;i<dlg.treeWidget->topLevelItemCount();i++)
    {
        QString link=dlg.treeWidget->topLevelItem(i)->text(2);
        if(!d_history.hasLink(link))
            out<<link<<endl;
    }
    file.close();
    appendHistory();
}

void CartWindow::appendHistory()
{
    //now append these to history
    QSet<QString> linkset;
    for(int i=0;i<dlg.treeWidget->topLevelItemCount();i++)
    {
        linkset<<dlg.treeWidget->topLevelItem(i)->text(2);
    }
    int ret=QMessageBox::question(this,"Confirm","Do you want to mark these links as downloaded?", QMessageBox::Yes, QMessageBox::No);
    //qDebug()<<ret<<QMessageBox::Yes;
    if(ret==QMessageBox::Yes)
    {
        d_history.appendHistory(linkset);
        update();
    }
}

void CartWindow::on_delButton_clicked()
{
    //delete the selected items
    foreach(QTreeWidgetItem* i, dlg.treeWidget->selectedItems())
            delete i;
}

void CartWindow::on_copyButton_clicked()
{
    QString links="";
    for(int i=0;i<dlg.treeWidget->topLevelItemCount();i++)
    {
        QString link=dlg.treeWidget->topLevelItem(i)->text(2);
        if(!d_history.hasLink(link))
            links+=QString("%1\r\n").arg(link);
    }
//    QMimeData data;
//    data.setHtml(links);
    //QApplication::clipboard()->setMimeData(&data);
    QApplication::clipboard()->setText(links);
    appendHistory();
}
