#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGlobal>
#include <QMainWindow>
#include <vector>
#include <unordered_map>
#include <QButtonGroup>
#include <QFile>
#include <QMap>
#include <QDebug>
using namespace std;

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    QVector<QString> searchAll();
    void update();
    QPair<QString, bool> readfiles(QString);
    QString disable(QString);
    void showApps();
    void showPaths();

private:
    QMap<int,QButtonGroup*> Btngroups;
    void onButtonClicked(QAbstractButton *button);
    QMap<QString, bool> selfSetUp;
    QMap<QString, QString> name_path;

};

#endif // MAINWINDOW_H
