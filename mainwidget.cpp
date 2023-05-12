#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDebug>
#include "mainwidget.h"
#include <dirent.h>
#include <fstream>

MainWidget::MainWidget(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(1000,500);

    // add tableview
    QTableView *tableView = new QTableView(this);
    tableView->setMinimumSize(1000,500);
    tableView->verticalHeader()->hide(); // hide row number

    QStandardItemModel *tableModel = new QStandardItemModel(this);
    tableView->setModel(tableModel);// recommend to set model before detail settings

    //set columns
    tableModel->setColumnCount(3);
    //name of colums
    tableModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("Application"));
    tableModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("self-startup"));
    tableModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("no self-startup"));

    //colum width
    //tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->setColumnWidth(0,700);
    tableView->setColumnWidth(1,150);
    tableView->setColumnWidth(2,150);

    //update table
    update();
    

    // set contents
    int i=0;
    for(auto it = selfSetUp.begin();it != selfSetUp.end();it++) //to_do
    {
        // add button group
        if(Btngroups[i] != NULL)
        {
            delete(Btngroups[i]);
        }
        QButtonGroup * m_pButtonGroup = new QButtonGroup(this);
        Btngroups[i] = m_pButtonGroup;

        //set table content
        tableModel->setItem(i, 0, new QStandardItem(it.key()));// to_do
        tableModel->setItem(i, 1, new QStandardItem());
        tableModel->setItem(i, 2, new QStandardItem());

        // add button to the last column
        QRadioButton *button0 = new QRadioButton();
        QRadioButton *button1 = new QRadioButton();

        m_pButtonGroup->addButton(button0,0);
        m_pButtonGroup->addButton(button1,1);

        //set button property
        button0->setProperty("index", 2*i);
        button1->setProperty("index", 2*i + 1);
        button0->setProperty("APP", it.key()); //to_do
        button1->setProperty("APP",it.key()); //to_do

        //set the init button status
        if(it.value()) //to_do
        {
            button0->setChecked(1);
        }
        else
        {
            button1->setChecked(1);
        }

        // set click event
        connect(Btngroups[i], SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

        // insert the buttons
        tableView->setIndexWidget(tableModel->index(tableModel->rowCount()-1,1),button0);
        tableView->setIndexWidget(tableModel->index(tableModel->rowCount()-1,2),button1);
        i++;
    }
}

void MainWidget::onButtonClicked(QAbstractButton *button)
{
    // now button
    qDebug() << button->property("index").toInt() << Qt::endl;

    // functions         to_do
    if(button->property("index").toInt() % 2 == 0)
    {
        //add(button->property("APP").toString());
    }
    else
    {
        delete(button->property("APP").toString());
    }
    

    // change status
    QList<QAbstractButton*> list = Btngroups[(button->property("index").toInt()) / 2]->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(button->property("index").toInt()).arg(strStatus);
    }
}

MainWidget::~MainWidget()
{

}

void MainWidget::showApps(){
    for(int i=0 ; i< name_path.keys().size();i++){
        qDebug() << name_path.keys()[i];
    }
}

void MainWidget::showPaths(){
    for(int i=0 ; i< name_path.values().size();i++){
        qDebug() << name_path.values()[i];
    }
}

QPair<QString, bool> MainWidget::readfiles(QString filename){
//    qDebug() << filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return QPair<QString, bool>("InvalidFile", 0);
    }
    QTextStream in(&file);
    QString line;
    QPair<QString, bool> ret;
//    qDebug() << in.atEnd();
    int nm=1;
    while(!in.atEnd()){
        line = in.readLine();

        if(line.left(5) == "Name=" && nm==1){
            ret.first = line.mid(5);
            nm=0;
        }else if(line.left(7) == "Hidden="){
            ret.second = (line.mid(7) == "false");
            break;
        }
    }
    return ret;
}

void MainWidget::update(){
    qDebug()<<"update go";
    QVector<QString> apps = searchAll();
    for(int i=0; i<apps.size();i++){
        selfSetUp[apps[i]] = false;
    }
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir("/data/home/pundthsea/.config/autostart"))){
        qDebug()<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        if(ptr->d_name[0] == '.'){
            continue;
        }
//        qDebug() << ptr->d_name <<' ';
        QPair<QString, bool> ans= readfiles(QString("/data/home/pundthsea/.config/autostart/") + QString(ptr->d_name));
//        qDebug() << ans.first;
        if(ans.first == "InvalidFile"){
            continue;
        }
        selfSetUp[ans.first] = ans.second;
        name_path[ans.first] = QString("/data/home/pundthsea/.config/autostart/") + QString(ptr->d_name);

    }
    closedir(pDir);
    qDebug() << "update end";
}

QVector<QString> MainWidget::searchAll() {
    string path("/opt/apps");
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir("/opt/apps"))){
        qDebug()<<"Folder doesn't Exist!"<<endl;
        return QVector<QString>(1, "No app");
    }
    QVector<QString> apps;

    while((ptr = readdir(pDir))!=0) {
        if(ptr->d_name[0] == '.'){
            continue;
        }
//        qDebug() << ptr->d_name <<' ';

        string filename;
        DIR *subDir;
        struct dirent *subptr;
        if(!(subDir = opendir((path + '/' + ptr->d_name + "/entries/applications").c_str() ))){
            qDebug()<<"Folder doesn't Exist!"<<endl;
            continue;
        }
        while((subptr = readdir(subDir))!=0){
//            qDebug() << subptr->d_name;
            if(QString(subptr->d_name).right(8) == ".desktop"){
                filename = string(subptr->d_name);
                break;
            }
        }
//        qDebug() << QString(filename.c_str()) << QString(ptr->d_name);
        QPair<QString, bool> ans= readfiles(QString((path + '/' + ptr->d_name + "/entries/applications/" + filename).c_str()));
//        qDebug() << ans.first;
        closedir(subDir);
        if(ans.first == "InvalidFile"){
            continue;
        }
        apps.push_back(ans.first);
        name_path[ans.first] = QString((path + '/' + ptr->d_name + "/entries/applications/" + filename).c_str());
    }
    closedir(pDir);
    return apps;
}

QString MainWidget::disable(QString name){
    qDebug() << "disable go";
    if(!name_path.contains(name)){
        qDebug() << QString("Invalid app name");
        return QString("Invalid app name");
    }
//    qDebug() << selfSetUp[name];
    QString path = name_path[name];
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug() << QString("can not change") ;
        return QString("can not change") ;
    }
    QTextStream in(&file);
    QVector<QString> contents;
    QString line;
    while(!in.atEnd()){
        line = in.readLine();
        if(line.left(7) == "Hidden="){
            line = line.left(7) + QString("true");
        }
        contents.push_back(line);
    }
    for(int i=0; i<contents.size();i++){
        in << contents[i] << QString("\n");
    }
    selfSetUp[name] = false;
    qDebug() << QString("Success");
    return QString("Success");
}


