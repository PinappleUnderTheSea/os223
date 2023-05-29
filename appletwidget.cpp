#include <QHeaderView>
#include <QStringList>
#include <QString>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDebug>
#include "appletwidget.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <qfiledialog.h>
#include<QPushButton>

QString getName(){

    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir("/home"))){
        qDebug()<<"home doesn't Exist!"<<Qt::endl;
        return "Get user Name err";
    }
//    qDebug() << " 111";
    QString uname;
    while((ptr = readdir(pDir))!=0) {
        if(ptr->d_name[0] == '.'){
            continue;
        }
        qDebug() << ptr->d_name <<' ';
        uname = (ptr->d_name);
    }


    closedir(pDir);
    return uname;
}

AppletWidget::AppletWidget(QWidget *parent) :
    QMainWindow(parent)
{

    setFixedSize(500,700);
    QString uname = getName();

    username = uname;
    // add tableview
    update_widget();
}

void AppletWidget::update_widget()
{
    if(tableView != NULL)
    {
        delete(tableView);
    }
    if(tableModel != NULL)
    {
        delete(tableModel);
    }
    tableView = new QTableView(this);
    tableView->setMinimumSize(500,700);
    tableView->verticalHeader()->hide(); // hide row number

    tableModel = new QStandardItemModel(this);
    tableView->setModel(tableModel);// recommend to set model before detail settings

    //set columns
    tableModel->setColumnCount(3);
    //name of colums
    tableModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("Application"));
    tableModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("self-startup"));
    tableModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("no self-startup"));

    //colum width
    //tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->setColumnWidth(0,280);
    tableView->setColumnWidth(1,110);
    tableView->setColumnWidth(2,110);

    //update table
    update();
    
    qDebug()<<"applet1";
    // set contents
    int i=0;
    for(auto it = selfSetUp.begin();it != selfSetUp.end(); it++) //to_do
    {
        // add button group
        qDebug()<<"applet1--";

        QButtonGroup * m_pButtonGroup = new QButtonGroup(this);

        if(i >= Btngroups.size())
        {
            Btngroups.push_back(m_pButtonGroup);
        }else{
            if(Btngroups[i] != NULL)
                delete(Btngroups[i]);
            Btngroups[i] = m_pButtonGroup;
        }
        qDebug()<<"applet2";
        //set table content
        tableModel->setItem(i, 0, new QStandardItem(it.key()));// to_do
        tableModel->setItem(i, 1, new QStandardItem());
        tableModel->setItem(i, 2, new QStandardItem());
        qDebug()<<"applet3";
        // add button to the last column
        QRadioButton *button0 = new QRadioButton();
        QRadioButton *button1 = new QRadioButton();

        m_pButtonGroup->addButton(button0,0);
        m_pButtonGroup->addButton(button1,1);
        qDebug()<<"applet4";
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
        qDebug()<<"applet5";
        // set click event
        connect(Btngroups[i], SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

        // insert the buttons
        tableView->setIndexWidget(tableModel->index(tableModel->rowCount()-1,1),button0);
        tableView->setIndexWidget(tableModel->index(tableModel->rowCount()-1,2),button1);
        i++;
    }
    qDebug()<<"applet6";

    //add + - button
    QPushButton * btn_add = new QPushButton("+", this);
    btn_add->resize(30,30);
    QPushButton * btn_del = new QPushButton("-", this);
    btn_del->resize(30,30);
    btn_del->move(30,0);

    connect(btn_add, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(btn_del, SIGNAL(clicked()), this, SLOT(delButtonClicked(QAbstractButton*)));

}

void AppletWidget::onButtonClicked(QAbstractButton *button)
{
    // now button
    qDebug() << button->property("index").toInt() << Qt::endl;

    // functions         to_do
     if(button->property("index").toInt() % 2 == 0)
     {
          enable(button->property("APP").toString());
     }
     else
     {
          disable(button->property("APP").toString());
     }

    // change status
    QList<QAbstractButton*> list = Btngroups[(button->property("index").toInt()) / 2]->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(pButton->property("index").toInt()).arg(strStatus);
    }
}

void AppletWidget::addButtonClicked()
{
    // add button
    Manual();
    update_widget();
}

void AppletWidget::delButtonClicked(QAbstractButton *button)
{
    // now button
    qDebug() << button->property("index").toInt() << Qt::endl;

    // functions         TODO
    update_widget();
    
}

AppletWidget::~AppletWidget()
{
    if(tableView != NULL)
    {
        delete(tableView);
    }
    if(tableModel != NULL)
    {
        delete(tableModel);
    }
}

void AppletWidget::showApps(){
    for(int i=0 ; i< name_path.keys().size();i++){
        qDebug() << name_path.keys()[i];
    }
}

void AppletWidget::showPaths(){
    for(int i=0 ; i< name_path.values().size();i++){
        qDebug() << name_path.values()[i];
    }
}

QString AppletWidget::getFileName(QString path){
    int index;
    for(index = path.length()-1;index>=0;index--){
        if(path[index]=="/"){
            break;
        }
    }
    return path.right(path.length()-index-1);
}

QPair<QString, bool> AppletWidget::readfiles(QString filename){
//    qDebug() << filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return QPair<QString, bool>("InvalidFile", 0);
    }
    QTextStream in(&file);
    QString line;
    QPair<QString, bool> ret;
    ret.second = false;
//    qDebug() << in.atEnd();
    int nm=1;
    while(!in.atEnd()){
        line = in.readLine();

        if(line.left(5) == "Name=" && nm==1){
            ret.first = line.mid(5);
            nm=0;
        }else if(line.left(7) == "Hidden="){
            ret.second = (line.mid(7) == "false");
//            break;
        }
    }
    return ret;
}

void AppletWidget::update(){
    qDebug()<<"update go";
    QVector<QString> apps = searchAll();
    for(int i=0; i<apps.size();i++){
        selfSetUp[apps[i]] = false;
    }
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir((QString("/data/home/")+username+QString("/.config/autostart")).toStdString().c_str()))){
        qDebug()<<"Folder doesn't Exist!"<<Qt::endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        if(ptr->d_name[0] == '.'){
            continue;
        }
//        qDebug() << ptr->d_name <<' ';
        QPair<QString, bool> ans= readfiles(QString("/data/home/")+username+QString("/.config/autostart/") + QString(ptr->d_name));
//        qDebug() << ans.first;
        if(ans.first == "InvalidFile"){
            continue;
        }
        selfSetUp[ans.first] = ans.second;
        name_path[ans.first] = QString("/data/home/")+username+QString("/.config/autostart/") + QString(ptr->d_name);

    }
    closedir(pDir);
    qDebug() << "update end";
}

QVector<QString> AppletWidget::searchAll() {
    string path("/opt/apps");
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir("/opt/apps"))){
        qDebug()<<"Folder doesn't Exist!"<<Qt::endl;
        return QVector<QString>(0);
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
            qDebug()<<"Folder doesn't Exist!"<<Qt::endl;
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

QString AppletWidget::disable(QString name){
    qDebug() << "disable go";
    if(!name_path.contains(name)){
        qDebug() << QString("Invalid app name");
        return QString("Invalid app name");
    }
    QString path = name_path[name];
    QFile file(path);
//    qDebug() << path;
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
            qDebug() << line;
            line = line.left(7) + QString("true");
            qDebug() << QString("change");
        }
        contents.push_back(line);
    }
    QFile outfile(path);
//    qDebug() << path;
    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << QString("can not change") ;
        return QString("can not change") ;
    }
    QTextStream out(&outfile);
    for(int i=0; i<contents.size();i++){
        out << contents[i] << QString("\n");
    }
    selfSetUp[name] = false;
    qDebug() << QString("Success");
    return QString("Success");
}

QString AppletWidget::enable(QString name) {
    if(!name_path.contains(name)){
        qDebug() << QString("Invalid app name");
        return QString("Invalid app name");
    }
    QString path = name_path[name];
    if(path.left(5) == "/data"){
        QFile file(path);
    //    qDebug() << path;
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
                qDebug() << line;
                line = line.left(7) + QString("false");
                qDebug() << QString("change");
            }
            contents.push_back(line);
        }
        QFile outfile(path);
    //    qDebug() << path;
        if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug() << QString("can not change") ;
            return QString("can not change") ;
        }
        QTextStream out(&outfile);
        for(int i=0; i<contents.size();i++){
            out << contents[i] << QString("\n");
        }
        selfSetUp[name] = false;
        qDebug() << QString("Success");
        return QString("Success");
    }

    QFile infile(path);
    QFile outfile(QString("/data/home/")+username+QString("/.config/autostart/") + name + QString(".desktop"));

    QTextStream in(&infile);
    if (!infile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << QString("can not change") ;
        return QString("can not change") ;
    }
    QVector<QString> contents;
    int count =0;
    QString line;
    while(!in.atEnd()){
        line = in.readLine();
        if(count == 1){
            contents.push_back(QString("Hidden=false"));
        }
        contents.push_back(line);
        count ++;
    }

    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << QString("can not change") ;
        return QString("can not change") ;
    }
    QTextStream out(&outfile);
    for(int i=0; i<contents.size();i++){
        out << contents[i] << QString("\n");
    }
    selfSetUp[name] = true;
    qDebug() << QString("Success");
    return QString("Success");

}


void AppletWidget::getAllFiles(QString path)
{
    DIR *pDir;
    struct dirent* ptr;

    if(!(pDir = opendir(path.toStdString().c_str()))){
//        qDebug()<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
            string filepath = path.toStdString() + "/" + ptr->d_name;
            if (path == QString("/")){
                qDebug() << QString(filepath.c_str());
            }
            struct stat buf;
            stat(filepath.c_str(), &buf);
            if(S_ISDIR(buf.st_mode)){
                getAllFiles(QString(filepath.c_str()));
            }else if(QString(filepath.c_str()).right(8) != ".desktop"){
                continue;
            }else{
                QPair<QString, bool> ans = readfiles(QString(filepath.c_str()));
                name_path[ans.first] = QString(filepath.c_str());
                qDebug() << path;
            }
        }
    }
    closedir(pDir);
}

void AppletWidget::globalSearch(){
    getAllFiles(QString("/"));
}

void AppletWidget::Manual(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->exec();
    auto selectDir = fileDialog->selectedFiles();
    if (selectDir.size()>0)
    {
        QString path = selectDir.at(0);
        qDebug() << "Path:" << selectDir;
        if(path.right(8) == ".desktop"){
            QPair<QString, bool> ans = readfiles(path);
            name_path[ans.first] = path;
            selfSetUp[ans.first] = false;
        }else{
            QString ans = getFileName(path);
            name_path[ans] = path;
        }
        return;
    }
    qDebug() << "Not Executable";
}
