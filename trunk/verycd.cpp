#include "verycd.h"


VeryCDListPage::VeryCDListPage(QString f, int n)
{
   //read the reg expr
    QFile file(f);
    file.open(QIODevice::ReadOnly);
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    server = codec->toUnicode(file.readLine());
    server = server.left(server.length()-1);
    link = codec->toUnicode(file.readLine());
    link = link.left(link.length()-1);
    mainExpr = codec->toUnicode(file.readLine());
    mainExpr = mainExpr.left(mainExpr.length()-1);
    detailExpr = codec->toUnicode(file.readLine());
    detailExpr = detailExpr.left(detailExpr.length()-1);
    qDebug()<<mainExpr<<detailExpr;
    file.close();
    http=new QHttp(server);
    connect(http, SIGNAL(done(bool)), this, SLOT(pageArrived(bool)));
    link=link.arg(n);
    qDebug()<<server<<link;
    http->get(link);
}

QStringList VeryCDListPage::allLinks()
{
    return allLinks();
}

void VeryCDListPage::pageArrived(bool error)
{
    qDebug()<<"Main page arrived with error: "<<error<<http->error()<<server;
    if(error)
    {
        http->get(link);
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    rawContent = codec->toUnicode(http->readAll());
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
        if(captured.join("")=="")
            continue;
        captured[0]=this->server;
        VeryCDDetailPage * page=new VeryCDDetailPage(captured);
        page->detailExpr=detailExpr;
        detailPages<<page;
        page->print();
//        captured[0]="\r\n"+QString().setNum(captured.size())+"**********************************\r\n";
//        qDebug()<<captured;
    }
    qDebug()<<"total found:"<<count;
    delete http;
    detailPages[0]->load();
}

void VeryCDDetailPage::pageArrived(bool error)
{
    qDebug()<<"Detail page arrived with error: "<<error<<http->error();
    if(error)
    {
        http->get(link);
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    rawContent = codec->toUnicode(http->readAll());
    QRegExp rx(detailExpr);
    rx.setMinimal(true);
    rx.setCaseSensitivity(Qt::CaseSensitive);
    int lastPos=0;
    int count=0;
    while(lastPos!=-1)
    {
        count++;
        lastPos=rx.indexIn(rawContent, lastPos+1 );
        QStringList captured=rx.capturedTexts();
        qDebug()<<captured[1]<<captured[2];
    }
    qDebug()<<"total found:"<<count;
    delete http;
}

VeryCDDetailPage::VeryCDDetailPage(QStringList& p)
{
    int i=0;
    server=p[i++];
    picture=p[i++];
    category=p[i++];
    link=p[i++];
    title=p[i++];
    publisher=p[i++];
    language=p[i++].replace("&nbsp;","");
    year=p[i++].replace("&nbsp;","");
    description=p[i++].trimmed();
    created=p[i++];
    modified=p[i++];
    files=p[i++];
    size=p[i++];
    comments=p[i++];
}

void VeryCDDetailPage::load()
{
    qDebug()<<server<<link;
    http=new QHttp(server);
    connect(http, SIGNAL(done(bool)), this, SLOT(pageArrived(bool)));
    http->get(link);
}

void VeryCDDetailPage::print()
{
    qDebug()<<"\r\r\r\r--------------------Detailed Page-------------\r ";
    qDebug()<<"\rpicture:\t"<<picture;
    qDebug()<<"\rcategory:\t"<<category;
    qDebug()<<"\rlink:  \t\t"<<link;
    qDebug()<<"\rtitle:  \t"<<title;
    qDebug()<<"\rpublisher:\t"<<publisher;
    qDebug()<<"\rlanguage:\t"<<language;
    qDebug()<<"\ryear:  \t\t"<<year;
    qDebug()<<"\rdescription:\t"<<description;
    qDebug()<<"\rcreated:  \t"<<created;
    qDebug()<<"\rmodified  \t"<<modified;
    qDebug()<<"\rfiles  \t\t"<<files;
    qDebug()<<"\rsize:  \t\t"<<size;
    qDebug()<<"\rcomments: \t"<<comments;
}











