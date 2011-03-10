#ifndef QPAGE_EXTRACTOR_H
#define QPAGE_EXTRACTOR_H
#include <QHttp>
#include <QRegExp>
#include <QTextCodec>
#include <QSettings>
#include <QStringList>
#include <QTimer>
#include <QDebug>

class QPageExtractor: public QObject
{
    Q_OBJECT
    public:
        QPageExtractor(QString fileName, QString fieldName="");//constructor by feeding setting files
//        const QMap<QString, QString>& getRowAsMap(int index);//get all extractions in a list of map
        const QStringList getRow(int row);//get all extractions in a list of map
        const QString get(int row, QString column);//get extraction value with column and row
        const QString get(int row, int column);//get extraction value with column and row
        const QStringList getColumn(QString column);//get one column from all rows
        const QStringList getColumn(int column);//get one column from all rows
        void load(int retry=0);//retrieve the page and extract, retry=0 means no reload, retry=-1 means always retry
        int count();//how many occurance has been found? -1 means not finished
        ~QPageExtractor();
    private slots:
        void pageArrived(bool error);
    signals:
        void updated();
    private:
        QHttp* d_http;//http object pointer
        bool d_finished;//indicate whether it is finished
        QString d_server, d_link;//server and path
        QString d_rawContent;//raw content retrieved
        QList<QStringList> d_extractions;//each list item contains an occurance found
        QString d_expression;//regular expression
        QStringList d_columnNames;//name of captures
        int d_retry;//retry times
        int d_count;//rows found
        void parse();
        int columnByName(QString& columnName);
};

class QPageExtractorTester: public QObject
{
    Q_OBJECT
    public:
        QPageExtractorTester(QPageExtractor* extractor);
    public slots:
        void updated();
    private:
        QPageExtractor* d_extractor;
};

#endif
