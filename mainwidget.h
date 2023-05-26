#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QBoxLayout>
#include <QRgb>
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include <dde-dock/pluginsiteminterface.h>
#include "type.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget();
    ~MainWidget();
    QSize sizeHint() const;

public:
    int dpi;
    QBoxLayout *centralLayout;
    QLabel *Label;
    // 字体
    QFont font;
};

#endif // MAINWIDGET_H
