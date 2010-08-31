#include "verycd.h"

VeryCDListPage::VeryCDListPage(QString link)
{
    this->link=link;
    http=new QHttp("www.verycd.com");
    connect(http, SIGNAL(done(bool)), this, SLOT(pageArrived(bool)));
    http->get(link);
    //read the reg expr
    QFile file("ziliao.exp");
    file.open(QIODevice::ReadOnly);
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    mainExpr = codec->toUnicode(file.readLine());
    mainExpr = mainExpr.left(mainExpr.length()-1);
    detailExpr = codec->toUnicode(file.readLine());
    qDebug()<<mainExpr<<detailExpr;
    file.close();
}

QStringList VeryCDListPage::allLinks()
{
    return allLinks();
}

void VeryCDListPage::pageArrived(bool error)
{
    qDebug()<<"page arrived with error: "<<error<<http->error();
    if(error)
    {
        http->get(link);
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    rawContent = codec->toUnicode(http->readAll());
/*    QFile file("test.htm");
    file.open(QIODevice::ReadOnly);
    QTextCodec *codec1 = QTextCodec::codecForName("GB18030");
    rawContent = codec1->toUnicode(file.readAll());
    file.close();
*/    //qDebug()<<rawContent<<mainExpr;
    QRegExp rx(mainExpr);
    rx.setMinimal(true);
    rx.setCaseSensitivity(Qt::CaseSensitive);
    int lastPos=0;
    int count=0;
    while(lastPos!=-1)
    {
        count++;
        lastPos=rx.indexIn(rawContent, lastPos+1 );
        QStringList captured=rx.capturedTexts();
        //here create a detailed page object to grab details
        captured[0]="\r\n"+QString().setNum(captured.size())+"**********************************\r\n";
        qDebug()<<captured;
    }
    qDebug()<<"total found:"<<count;
//    qDebug()<<rawContent;
}

void VeryCDDetailPage::pageArrived(bool error)
{
    error="";
    return;
}
