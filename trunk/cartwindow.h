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
        void update();
    private:
        Ui::Dialog dlg;
        VeryCDHistory d_history;
    private slots:
        void on_copyButton_clicked();
        void on_delButton_clicked();
        void on_saveButton_clicked();
        void on_clearButton_clicked();
        void on_refreshButton_clicked();
        void appendHistory();
};

#endif
