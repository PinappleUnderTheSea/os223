#ifndef PLUGINWIDGET_H
#define PLUGINWIDGET_H

#include <QWidget>
#include <QSettings>

class PluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PluginWidget(QWidget *parent = 0);
    bool enabled();
    void setEnabled(const bool b);
    QString text;
    // int mp, cp;

// signals:
//     void requestUpdateGeometry() const;

private:
    QSize sizeHint() const;
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *e);

};

#endif // PLUGINWIDGET_H