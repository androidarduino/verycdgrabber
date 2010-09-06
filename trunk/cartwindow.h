#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include "ui_cart.h"
#include "verycd.h"

class CartWindow: public QDialog
{
    Q_OBJECT
    public:
        CartWindow();
        QList<VeryCDDetailPage*> pages;
        int exec();
    private:
        Ui::Dialog dlg;
};

#endif
