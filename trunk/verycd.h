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

class VeryCDListPage: public QObject
{
    Q_OBJECT
    public:
        VeryCDListPage(QString f, int n);
        QStringList allLinks();
    private slots:
        void pageArrived(bool error);
    private:
        QHttp* http;
        QString server, link, rawContent, mainExpr, detailExpr;
        QList<VeryCDDetailPage*> detailPages;
        QStringList pageLinks, AllLinks;
};

class VeryCDDetailPage: public QObject
{
    Q_OBJECT
    public:
        QString detailExpr;
    public:
        VeryCDDetailPage(QStringList& p);
        void print();
        void load();
    private slots:
        void pageArrived(bool error);
    private:
        QHttp* http;
        QString server, picture, category, link, title, publisher, language, year, description, created, modified, files, size, comments;
        QString rawContent;
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
