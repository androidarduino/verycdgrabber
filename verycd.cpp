#include "verycd.h"


VeryCDListPage::VeryCDListPage(QString f, int n)
{
    pageNum=n;
    loaded=false;
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
	qDebug()<<"raw content: "<<rawContent;
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
        //page->print();
    }
    qDebug()<<"total found:"<<count;
    delete http;
    for(int i=0;i<detailPages.size();i++)
    {
        //detailPages[i]->load();
    }
    loaded=true;
    emit updated();
}

void VeryCDDetailPage::pageArrived(bool error)
{
//    qDebug()<<"Detail page arrived with error: "<<error<<http->error();
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
//    items.clear();//is this necessary?
    while(lastPos!=-1)
    {
        lastPos=rx.indexIn(rawContent, lastPos+1 );
        QStringList captured=rx.capturedTexts();
//        qDebug()<<captured[1]<<captured[2]<<captured[3]<<captured[4];
    if(link=="/topics/2844948/")
        qDebug()<<captured[1]<<captured[2]<<captured[3]<<captured[4];
        Ed2kItem* item=new Ed2kItem();
        item->link=captured[2];
        item->name=captured[3];
        item->size=captured[4];
        if(item->link!="")
        {
            items<<item;
            count++;
        }
    }
    loaded=true;
    if(files.toInt()!=count)
        qDebug()<<"$$$$$$$$$$$$$$$$$$ should found: "<<files <<"total found:"<<count<<link;
    delete http;
}

VeryCDDetailPage::VeryCDDetailPage(QStringList& p)
{
    int i=0;
    server=p[i++];
    picture=p[i++];
    if(picture.length()>200)
        picture="unaviable";
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
    loaded=loading=false;
}

void VeryCDDetailPage::load()
{
    if(loaded||loading)
        return;
    qDebug()<<server<<link<<" is now loading";
    http=new QHttp(server);
    connect(http, SIGNAL(done(bool)), this, SLOT(pageArrived(bool)));
    //to fix the login problem temporarily
    QHttpRequestHeader header("GET", link);
    header.setValue("Host", "www.verycd.com");
    header.setValue("Cookie", "uchome_auth=878e3SD9RwEEqqhc%2Be7nlKk2xjRVke9IyoqQdPOBWAxk8L%2BiNdnHBandz3hvQsTainb6clBvmct3VX9hIjqzQ4pu10oO; uchome_loginuser=vrcats; collectentry=1; uchome_view_tid=376427; sid=db0c166930aaff99dc229af1a127f1d68def3a7c; member_id=7181820; member_name=vrcats; mgroupId=93; pass_hash=1bd45fa44f53aea7d426d15b0ae83a42; rememberme=false; __utma=1.548072307.1349242133.1349432235.1349434981.6; __utmb=1.3.10.1349434981; __utmc=1; __utmz=1.1349388407.4.3.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided); favoritefolder=1; Hm_lvt_c7849bb40e146a37d411700cb7696e46=1349309769501,1349388411505,1349432238257,1349434983961; Hm_lpvt_c7849bb40e146a37d411700cb7696e46=1349436310099");
    http->setHost("www.verycd.com");
    http->request(header);
    //http->get(link);
    loading=true;
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

VeryCDHistory::VeryCDHistory(const QString& historyFile)
{
    d_historyFile=historyFile;
    update();
}

void VeryCDHistory::update()
{
    QFile file(d_historyFile);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    d_links.clear();
    while(!in.atEnd())
    {
        d_links<<in.readLine();
    }
    file.close();
}

bool VeryCDHistory::hasLink(QString link)
{
    return d_links.contains(link);
}

void VeryCDHistory::appendHistory(const QSet<QString>& links)
{
    QSet<QString> l(links);
    //remove those exists in history
    foreach(QString i, l)
        if(d_links.contains(i))
            l.remove(i);
    //write to file
    QFile file(d_historyFile);
    file.open(QIODevice::Append);
    QTextStream out(&file);
    foreach(QString i, l)
        out<<i<<endl;
    file.close();
    update();
}









