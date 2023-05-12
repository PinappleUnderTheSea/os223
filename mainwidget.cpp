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

MainWindow::MainWindow(QWidget *parent) :
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

    // set contents
    for(int i = 0;i < 100/*num_of_apps*/; i++) //to_do
    {
        // add button group
        QButtonGroup * m_pButtonGroup = new QButtonGroup(this);
        Btngroups.push_back(m_pButtonGroup);

        //set table content
        tableModel->setItem(i, 0, new QStandardItem(QString("app%1"). arg(i)));// to_do
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
        button0->setProperty("APP","app"); //to_do
        button1->setProperty("APP","app"); //to_do

        //set the init button status
        if(0/*has_selfstarting[i]*/) //to_do
        {
            button0->setChecked(1);
        }
        else
        {
            button1->setChecked(1);
        }

        // set click event
        connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

        // insert the buttons
        tableView->setIndexWidget(tableModel->index(tableModel->rowCount()-1,1),button0);
        tableView->setIndexWidget(tableModel->index(tableModel->rowCount()-1,2),button1);
    }
}

void MainWindow::onButtonClicked(QAbstractButton *button)
{
    // now button
    qDebug() << button->property("index").toInt() << Qt::endl;

    // functions         to_do
    /* if(button->property("index").toInt() % 2 == 0)
     * {
     *      add(button->property("APP").toQString());
     * }
     * else
     * {
     *      delete(button->property("APP").toQString());
     * }
    */

    // change status
    QList<QAbstractButton*> list = Btngroups[(button->property("index").toInt()) / 2]->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(button->property("index").toInt()).arg(strStatus);
    }
}

MainWindow::~MainWindow()
{

}

QVector<QString> MainWindow::searchAll() {
    QVector<QString> ret;
    for(auto i = selfSetUp.begin(); i!=selfSetUp.end();i++){
        if(!(i.value())){
            ret.push_back(i.key());
        }
    }
    return ret;
}

QPair<QString, bool> MainWindow::readfiles(QString filename){

    QString path("/data/home/pundthsea/.config/autostart");
    QFile file(path + filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

    }
    QTextStream in(&file);
    QString line;
    QPair<QString, bool> ret;
    while(!in.atEnd()){
        line = in.readLine();
        if(line.left(5) == "Name="){
            ret.first = line.mid(5);
        }else if(line.left(5) == "Hidden="){
            ret.second = (line.mid(7) == "false");
            break;
        }
    }
    return ret;
}

void MainWindow::update(){
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir("/data/home/pundthsea/.config/autostart"))){
//        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        QPair<QString, bool> ans= readfiles(QString(ptr->d_name));
        selfSetUp[ans.first] = ans.second;
    }
    closedir(pDir);
}
