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

void CartWindow::update()
{
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
                QTreeWidgetItem* linkitem=new QTreeWidgetItem((QTreeWidget*)0, data);
                dlg.treeWidget->addTopLevelItem(linkitem);
            }
        }
        else
            unloadedPage++;
    }
    if(unloadedPage>0)
        setWindowTitle(QString("%1 pages still loading, please wait...").arg(unloadedPage));
    else
        setWindowTitle("All pages loaded");
}
