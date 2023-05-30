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
#include <QStandardItemModel>
#include <QTableView>

using namespace std;

class AppletWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppletWidget(QWidget *parent = nullptr);
    ~AppletWidget();
    QVector<QString> searchAll();

    void update();
    QPair<QString, bool> readfiles(QString);
    QString disable(QString);
    QString enable(QString);
    QString getFileName(QString);
    QString getFileDir(QString);
    void getAllFiles(QString);
    void globalSearch();
    QString Add();
    QString Delete(QString name);
    void showApps();
    void showPaths();
    void update_widget();

private:
    std::vector<QButtonGroup*> Btngroups;
    QMap<QString, bool> selfSetUp;
    QMap<QString, QString> name_path;
    QString username;
    QTableView *tableView = NULL;
    QStandardItemModel *tableModel = NULL;
    QString choosen_name;
protected slots:
    void onButtonClicked(QAbstractButton *button);
    void addButtonClicked();
    void delButtonClicked();

};

#endif // MAINWINDOW_H
