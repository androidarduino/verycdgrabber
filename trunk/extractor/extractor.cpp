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
        qDebug()<<(d_rawContent=codec->toUnicode(d_http->readAll()));
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
        qDebug()<<"captured: "<<captured;
        d_extractions<<captured;
    }
    foreach(QStringList l, d_extractions)
        qDebug()<<"Extracted: "<<l;
}







