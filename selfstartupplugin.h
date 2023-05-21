#ifndef SELFSTARTUPPLUGIN_H
#define SELFSTARTUPPLUGIN_H

#include <dde-dock/pluginsiteminterface.h>
#include <dde-dock/pluginproxyinterface.h>

#include <QObject>
#include <QLabel>
#include <QFile>
#include <cstdio>
#include <QDebug>

#include "mainwidget.h"
#include "aboutdialog.h"
#include "type.h"

class SelfStartupPlugin : public QObject, PluginsItemInterface
{
private:
    Settings settings;

private:
    MainWidget *m_pluginWidget;
    MainWidget *m_appletWidget; 

    Q_OBJECT
    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "self_startup.json")

public:
    explicit SelfStartupPlugin(QObject *parent = nullptr);

    // 返回插件的名称，必须是唯一值，不可以和其它插件冲突
    const QString pluginName() const override;

    // 插件初始化函数
    void init(PluginProxyInterface *proxyInter) override;
    const QString pluginDisplayName() const override;

    // 返回插件的 widget
    QWidget *itemWidget(const QString &itemKey) override;
    // PluginMode status() const override;
    // QString description() const override;

    //弹窗
    QWidget *itemPopupApplet(const QString &itemKey) override;

    QIcon icon(const DockPart &dockPart, int themeType) override;
    // PluginFlags flags() const override;

    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

    void about();

    const QString itemContextMenu(const QString &itemKey) override; //TODO
    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;   //TODO
};

#endif // SELFSTARTUPPLUGIN_H