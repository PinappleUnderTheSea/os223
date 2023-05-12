#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QButtonGroup>

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    std::vector<QButtonGroup*> Btngroups;
    void onButtonClicked(QAbstractButton *button);
};

#endif // MAINWINDOW_H
