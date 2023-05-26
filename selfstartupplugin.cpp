#include "selfstartupplugin.h"

//设置选项和默认值,静态全局变量
struct SettingItem SelfStartupPlugin::settingItems[]={
//全局设置选项
{"chartModeCheckBox",0},//图表模式开关
{"batInfoComboBox",0},//气泡电池信息开关
{"updateIntervalSpinBox",1000},//更新间隔ms

//文字模式设置选项
{"displayContentComboBox",DisplayContentSetting::ALL},
{"wordSpacingSpinBox",4},
{"cpuDiyWordLineEdit",QString("CPU:")},
{"memDiyWordLineEdit",QString("MEM:")},
{"upNetspeedDiyWordLineEdit",QString("▴")},
{"downNetspeedDiyWordLineEdit",QString("▾")},
{"fontSizeSpinBox",9},
{"fontColorComboBox",0},

//图表模式设置选项
//默认三个图表都是打开的
{"netChartCheckBox",1},{"cpuChartCheckBox",1},{"memChartCheckBox",1},
{"chartSpacingSpinBox",1},
//net图表设置
{"netUpTopSpinBox",500},//上传
{"netUpWidget",QColor(0,78,239,200)},
{"netDownTopSpinBox",500},//下载
{"netDownWidget",QColor(225,67,0,200)},
{"netBorderRoundSpinBox",30},//边框
{"netBorderWidget",QColor(255,255,255,0)},
{"netBackgroundWidget",QColor(0,0,0,128)},//背景
{"netWidthSpinBox",40},{"netHeightSpinBox",28},//宽度高度
//cpu图表设置
{"cpuWorkWidget",QColor(250,74,74,255)},
{"cpuBorderRoundSpinBox",30},//边框
{"cpuBorderWidget",QColor(255,255,255,0)},
{"cpuBackgroundWidget",QColor(0,0,0,128)},//背景
{"cpuWidthSpinBox",40},{"cpuHeightSpinBox",28},//宽度高度
//mem图表设置
{"memUsedWidget",QColor(21,199,195,255)},
{"memBorderRoundSpinBox",30},//边框
{"memBorderWidget",QColor(255,255,255,0)},
{"memBackgroundWidget",QColor(0,0,0,128)},//背景
{"memWidthSpinBox",40},{"memHeightSpinBox",28}//宽度高度
};

SelfStartupPlugin::SelfStartupPlugin(QObject *parent)
    : QObject(parent)
{

}

const QString SelfStartupPlugin::pluginName() const
{
    return QStringLiteral("self_startup");
}

//写配置信息
void SelfStartupPlugin::writeConfig(Settings *settings)
{
    QMapIterator<QString,QVariant> i(*settings);
    while(i.hasNext())
    {
        i.next();
        m_proxyInter->saveValue(this,i.key(),i.value());
    }
}

const QString SelfStartupPlugin::pluginDisplayName() const
{
    return QString("Self Startup");
}

void SelfStartupPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
    m_pluginWidget = new MainWidget;
    m_appletWidget = new AppletWidget;

    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());
        m_proxyInter->requestSetAppletVisible(this, "", true);//set applet visible
    }
}

QWidget *SelfStartupPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    
    return m_pluginWidget;

    // if (itemKey == QUICK_ITEM_KEY)
    // 	return m_pluginWidget;
    
    // return nullptr;
}

QWidget *SelfStartupPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_appletWidget;
}


// QIcon SelfStartupPlugin::icon(const DockPart &dockPart, int themeType)
// {
//     if (dockPart == DockPart::QuickShow) {
//         QIcon icon;
//         return icon;
//     }

//     return QIcon();
// }

// void SelfStartupPlugin::about()
// {
//     QMessageBox aboutMB(QMessageBox::NoIcon, "SelfStarupPlugin 1.0", "[About]\n\nDeepin Linux DDE Dock Self-startup plugin.\n");
//     aboutMB.setIconPixmap(QPixmap(":/icon.png"));
//     aboutMB.exec();
// }

// PluginFlags SelfStartupPlugin::flags() const
// {
//     // 返回的插件为Type_Common-快捷区域插件， Quick_Multi快捷插件显示两列的那种，例如网络和蓝牙
//     // Attribute_CanDrag该插件在任务栏上支持拖动，Attribute_CanInsert该插件支持在其前面插入其他的图标
//     // Attribute_CanSetting该插件支持在控制中心设置显示或隐藏
//     return PluginFlags::Type_Common // to_do
//         | PluginFlags::Quick_Single
//         //| PluginFlags::Attribute_CanDrag
//         //| PluginFlags::Attribute_CanInsert
//         | PluginFlags::Attribute_CanSetting;
// }

bool SelfStartupPlugin::pluginIsAllowDisable()
{
    // 告诉 dde-dock 本插件允许禁用
    return true;
}

bool SelfStartupPlugin::pluginIsDisable()
{
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void SelfStartupPlugin::pluginStateSwitched()
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

const QString SelfStartupPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(2);

    // QMap<QString, QVariant> setting;
    // setting["itemId"] = "setting";
    // setting["itemText"] = "设置";
    // setting["isActive"] = true;
    // items.push_back(setting);

    QMap<QString, QVariant> about;
    about["itemId"] = "about";
    about["itemText"] = "关于";
    about["isActive"] = true;
    items.push_back(about);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SelfStartupPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(checked);

    // 根据上面接口设置的 id 执行不同的操作
    // if(menuId == "setting")
    // {
    //     pluginSettingDialog setting(&settings);
    //     if(setting.exec()==QDialog::Accepted)
    //     {
    //         setting.getDisplayContentSetting(&settings);
    //         writeConfig(&settings);
    //     }
    // }

    if (menuId == "about")
    {
        aboutDialog aboutdialog;
        if(aboutdialog.exec()==QDialog::Accepted)
        {
        }
    }
}

//使用系统配置函数读配置信息
void SelfStartupPlugin::readConfig(Settings *settings)
{
    for(unsigned long i=0;i<sizeof(settingItems)/sizeof(settingItems[0]);i++)
    {
        settings->insert(settingItems[i].name,
                         m_proxyInter->getValue(this,settingItems[i].name,settingItems[i].value));
    }
}

//写配置信息
void SelfStartupPlugin::writeConfig(Settings *settings)
{
    QMapIterator<QString,QVariant> i(*settings);
    while(i.hasNext())
    {
        i.next();
        m_proxyInter->saveValue(this,i.key(),i.value());
    }
}