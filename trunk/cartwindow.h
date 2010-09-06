#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include "ui_cart.h"
#include "verycd.h"

class CartWindow: public QDialog
{
    Q_OBJECT
    public:
        CartWindow();
    private:
        Ui::Dialog dlg;
        QList<VeryCDDetailPage*> pages;
};

#endif
