#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QStorageInfo>

class InformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InformationWidget(QWidget *parent = nullptr);

    inline QStorageInfo * Info() { return m_storageInfo; }

private slots:
    // 用于更新数据的槽函数
    void refreshInfo();

private:
    // 真正的数据显示在这个 Label 上
    QLabel *m_infoLabel;
    // 分区数据的来源
    QStorageInfo *m_storageInfo;
};

#endif // INFORMATIONWIDGET_H