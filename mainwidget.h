#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGlobal>
#include <QMainWindow>
#include <vector>
#include <unordered_map>
#include <QButtonGroup>
#include <QFile>
#include <QMap>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> searchAll();
    void update();
    QPair<QString, bool> readfiles(QString);

private:
    std::vector<QButtonGroup*> Btngroups;
    void onButtonClicked(QAbstractButton *button);
    QMap<QString, bool> selfSetUp;
    
};

#endif // MAINWINDOW_H
