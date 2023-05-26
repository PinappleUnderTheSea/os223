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
#include <QVBoxLayout>
#include <QRgb>
#include <QScreen>
#include <QApplication>

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
    QString enable(QString);
    QString getFileName(QString);
    void getAllFiles(QString);
    void globalSearch();
    void Manual();
    void showApps();
    void showPaths();

private:
    std::vector<QButtonGroup*> Btngroups;
    QMap<QString, bool> selfSetUp;
    QMap<QString, QString> name_path;
    QString username;
protected slots:
    void onButtonClicked(QAbstractButton *button);

};

#endif // MAINWINDOW_H
