#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QButtonGroup>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::vector<QButtonGroup*> Btngroups;
    void onButtonClicked(QAbstractButton *button);
};

#endif // MAINWINDOW_H
