#include "cartwindow.h"

CartWindow::CartWindow()
{
    dlg.setupUi(this);
}

int CartWindow::exec()
{
    //update the tree view
    dlg.treeWidget->clear();
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
    }
    return QDialog::exec();
}
