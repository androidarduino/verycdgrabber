#include "extractor.h"

QPageExtractor::QPageExtractor(QString fileName, QString fieldName)//constructor, fileName is a setting file
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec(codec);
    d_expression=settings.value(fieldName+"/expression").toString();
    d_columnNames=settings.value(fieldName+"/names").toString().split(",");
    d_server=settings.value(fieldName+"/server").toString();
    d_link=settings.value(fieldName+"/path").toString();
    qDebug()<<d_expression<<d_link<<d_columnNames;
    d_http=new QHttp(d_server);
    connect(d_http, SIGNAL(done(bool)), this, SLOT(pageArrived(bool)));
}

void QPageExtractor::pageArrived(bool error)
{
    if(!error)
    {
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        d_rawContent=codec->toUnicode(d_http->readAll());
        parse();
    }
    else
    {
        qDebug()<<"error occured: "<<d_http->errorString();
        if(d_retry>0||d_retry<0)//if there is retry left, or always retry
        {
            qDebug()<<"retrying number "<<d_retry;
            d_http->get(d_link);
            d_retry--;
        }
    }
}

void QPageExtractor::load(int retry)
{
    d_retry=retry;
    d_http->get(d_link);
}

QPageExtractor::~QPageExtractor()
{
    delete d_http;
}

void QPageExtractor::parse()
{
    //parse rawContent and capture required things
    QRegExp rx(d_expression);
    rx.setPatternSyntax(QRegExp::RegExp2);
    rx.setMinimal(true);
    rx.setCaseSensitivity(Qt::CaseSensitive);
    int lastPos=0;
    d_count=0;
    d_extractions.clear();
    while(lastPos!=-1)
    {
        d_count++;
        lastPos=rx.indexIn(d_rawContent, lastPos+1);
        QStringList captured=rx.capturedTexts();
        qDebug()<<rx.capturedTexts()[1];
        captured.removeAt(0);
        if(captured.join("")!="")
            d_extractions<<captured;
    }
//    foreach(QStringList l, d_extractions)
//        qDebug()<<"Extracted: "<<l;
    if(count()>0)
        emit(updated());
}

int QPageExtractor::count()
{
    return d_extractions.length();
}

const QStringList QPageExtractor::getRow(int row)
{
    if(row<0||row>d_extractions.length()-1)
        return QStringList();
    return d_extractions.at(row);
}

const QString QPageExtractor::get(int row, int column)
{
    if(row<0||row>d_extractions.length()-1)
        return "";
    QStringList l=d_extractions.at(row);
    if(column<0||column>l.length()-1)
        return "";
    return l.at(column);
}

const QStringList QPageExtractor::getColumn(int column)
{
    if(column<0)
        return QStringList();
    QStringList ret;
    foreach(QStringList l, d_extractions)
        if(column>l.length()-1)
            continue;
        else
            ret<<l.at(column);
    return ret;
}

const QString QPageExtractor::get(int row, QString column)
{
    return get(row, columnByName(column));
}

const QStringList QPageExtractor::getColumn(QString column)
{
    return getColumn(columnByName(column));
}

int QPageExtractor::columnByName(QString& columnName)
{
    for(int i=0;i<d_columnNames.count();i++)
        if(d_columnNames.at(i).trimmed()==columnName.trimmed())
            return i;
    return -1;
}

QPageExtractorTester::QPageExtractorTester(QPageExtractor* extractor)
{
    d_extractor=extractor;
    connect(extractor, SIGNAL(updated()), this, SLOT(updated()));
}

void QPageExtractorTester::updated()
{
    qDebug()<<"Test begin";
    qDebug()<<"getRow(int row); row=0, -1, 2, 7, 15, 550";
    qDebug()<<d_extractor->getRow(0);
    qDebug()<<d_extractor->getRow(-1);
    qDebug()<<d_extractor->getRow(2);
    qDebug()<<d_extractor->getRow(7);
    qDebug()<<d_extractor->getRow(15);
    qDebug()<<d_extractor->getRow(550);
    qDebug()<<"get(int row, int column); row,column=3,7 6,5 0,1 2,111 -9,4";
    qDebug()<<d_extractor->get(3,7);
    qDebug()<<d_extractor->get(6,5);
    qDebug()<<d_extractor->get(0,1);
    qDebug()<<d_extractor->get(2,111);
    qDebug()<<d_extractor->get(-9,4);
    qDebug()<<"get(int row, QString column); row,column=3,test1 6,test2 0,1, 2,test9 -9,666";
    qDebug()<<d_extractor->get(3,"test1");
    qDebug()<<d_extractor->get(6,"test2");
    qDebug()<<d_extractor->get(0,"1");
    qDebug()<<d_extractor->get(2,"test9");
    qDebug()<<d_extractor->get(-9,"666");
    qDebug()<<"getColumn(int column); column=0, -1, 2, 7, 15, 550";
    qDebug()<<d_extractor->getColumn(0);
    qDebug()<<d_extractor->getColumn(-1);
    qDebug()<<d_extractor->getColumn(2);
    qDebug()<<d_extractor->getColumn(7);
    qDebug()<<d_extractor->getColumn(15);
    qDebug()<<d_extractor->getColumn(550);
    qDebug()<<"getColumn(QString column); column=test1, test2, 754, """;
    qDebug()<<d_extractor->getColumn("test1");
    qDebug()<<d_extractor->getColumn("test2");
    qDebug()<<d_extractor->getColumn("754");
    qDebug()<<d_extractor->getColumn("");
}
