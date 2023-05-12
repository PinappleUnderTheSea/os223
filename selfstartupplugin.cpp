#include "selfstartupplugin.h"

SelfStarupPlugin::SelfStarupPlugin(QObject *parent)
    : QObject(parent)
{

}

const QString SelfStarupPlugin::pluginName() const
{
    return QStringLiteral("self_startup");
}

//写配置信息
void SelfStarupPlugin::writeConfig(Settings *settings)
{
    QMapIterator<QString,QVariant> i(*settings);
    while(i.hasNext())
    {
        i.next();
        m_proxyInter->saveValue(this,i.key(),i.value());
    }
}

const QString SelfStarupPlugin::pluginDisplayName() const
{
    return QString("Self Startup");
}

void SelfStarupPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
    m_pluginWidget = new MainWidget;
    m_appletWidget = new MainWidget;

    if (!pluginIsDisable() and m_centralWidget->enabled()) {
        m_proxyInter->itemAdded(this, pluginName());
        m_proxyInter->requestSetAppletVisible(this, "", true);//set applet visible
    }
}

QWidget *SelfStarupPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    
    return m_pluginWidget;
}

QWidget *SelfStarupPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_appletWidget;
}


QIcon SelfStarupPlugin::icon(const DockPart &dockPart, int themeType)
{
    if (dockPart == DockPart::QuickShow) {
        QIcon icon;
        return icon;
    }

    return QIcon();
}

void SelfStarupPlugin::about()
{
    QMessageBox aboutMB(QMessageBox::NoIcon, "SelfStarupPlugin 1.0", "[About]\n\nDeepin Linux DDE Dock Self-startup plugin.\n");
    aboutMB.setIconPixmap(QPixmap(":/icon.png"));
    aboutMB.exec();
}

PluginFlags SelfStarupPlugin::flags() const
{
    // 返回的插件为Type_Common-快捷区域插件， Quick_Multi快捷插件显示两列的那种，例如网络和蓝牙
    // Attribute_CanDrag该插件在任务栏上支持拖动，Attribute_CanInsert该插件支持在其前面插入其他的图标
    // Attribute_CanSetting该插件支持在控制中心设置显示或隐藏
    return PluginFlags::Type_Common // to_do
        | PluginFlags::Quick_Single
        //| PluginFlags::Attribute_CanDrag
        //| PluginFlags::Attribute_CanInsert
        | PluginFlags::Attribute_CanSetting;
}

bool SelfStarupPlugin::pluginIsAllowDisable()
{
    // 告诉 dde-dock 本插件允许禁用
    return true;
}

bool SelfStarupPlugin::pluginIsDisable()
{
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    //return m_proxyInter->getValue(this, "disabled", false).toBool();
    return !m_centralWidget->enabled();
}

void SelfStarupPlugin::pluginStateSwitched()
{
    m_centralWidget->setEnabled(!m_centralWidget->enabled());
    if (m_centralWidget->enabled())
        m_proxyInter->itemAdded(this, pluginName());
    else
        m_proxyInter->itemRemoved(this, pluginName());
}

const QString SelfStarupPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(2);

    QMap<QString, QVariant> setting;
    setting["itemId"] = "setting";
    setting["itemText"] = "设置";
    setting["isActive"] = true;
    items.push_back(setting);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SelfStarupPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(checked);

    // 根据上面接口设置的 id 执行不同的操作
    if(menuId == "setting")
    {
        pluginSettingDialog setting(&settings);
        if(setting.exec()==QDialog::Accepted)
        {
            setting.getDisplayContentSetting(&settings);
            writeConfig(&settings);
        }
    }
}