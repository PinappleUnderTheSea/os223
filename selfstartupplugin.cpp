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

    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

QWidget *SelfStarupPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    
    return m_pluginWidget;
}


QIcon SelfStarupPlugin::icon(const DockPart &dockPart, int themeType)
{
    if (dockPart == DockPart::QuickShow) {
        QIcon icon;
        return icon;
    }

    return QIcon();
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
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void SelfStarupPlugin::pluginStateSwitched()
{
    // 获取当前禁用状态的反值作为新的状态值
    const bool disabledNew = !pluginIsDisable();
    // 存储新的状态值
    m_proxyInter->saveValue(this, "disabled", disabledNew);

    // 根据新的禁用状态值处理主控件的加载和卸载
    if (disabledNew) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        m_proxyInter->itemAdded(this, pluginName());
    }
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
    Q_UNUSED(checked)

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