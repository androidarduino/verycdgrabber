#ifndef VERYCD_H
#define VERYCD_H
#include <QHttp>
#include <QRegExp>
#include <QClipboard>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QTextCodec>

class VeryCDHistory;
class VeryCDDetailPage;

class Ed2kItem: public QObject
{
    Q_OBJECT
    public:
        Ed2kItem(){}
        QString name, link, size;
};

class VeryCDListPage: public QObject
{
    Q_OBJECT
    public:
        VeryCDListPage(QString f, int n);
        QList<VeryCDDetailPage*> detailPages;
        int pageNum;
        bool loaded;
    private slots:
        void pageArrived(bool error);
    signals:
        void updated();
    private:
        QHttp* http;
        QString server, link, rawContent, mainExpr, detailExpr;
};

class VeryCDDetailPage: public QObject
{
    Q_OBJECT
    public:
        QString detailExpr;
        QString server, picture, category, link, title, publisher, language, year, description, created, modified, files, size, comments;
    public:
        VeryCDDetailPage(QStringList& p);
        void print();
        void load();
        QList<Ed2kItem*> items;
        bool loading, loaded;
    private slots:
        void pageArrived(bool error);
    private:
        QHttp* http;
        QString rawContent;
    signals:
        void loadComplete();
};

class VeryCDGrabber: public QObject
{
    Q_OBJECT
    public:
        VeryCDGrabber();
        void update();
        void setHistory(VeryCDHistory* h);
    private:
        VeryCDHistory* history;
};

class VeryCDHistory: public QObject
{
    Q_OBJECT
    public:
        VeryCDHistory(QString historyFile="verycd.history");
        bool hasLink(QString link);
    private:
        void loadHistory(QString file);
        QSet<QString> links;
};


#endif
