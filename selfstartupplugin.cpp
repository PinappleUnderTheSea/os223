#include "selfstartupplugin.h"
#include <cstdlib>
#include <dirent.h>
#inlucde <fstream>
SelfStarupPlugin::SelfStarupPlugin(QObject *parent)
    : QObject(parent)
{

}

const QString SelfStarupPlugin::pluginName() const
{
    return QStringLiteral("self_startup");
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

vector<string> SelfStarupPlugin::searchAll() {
    vector<string> ret;
    for(auto i = selfSetUp.begin(); i!=selfSetUp.end();i++){
        if(!(*i).second){
            ret.push_back((*i).first);
        }
    }
    return ret;
}

pair<string, bool> SelfStarupPlugin::readfiles(string filename){
    ifstream f;
    string path("/data/home/pundthsea/.config/autostart");
    f.open(path + filename);
    string line;
    pair<string, bool> ret;
    while(getline(f, line)){
        if(line.substr(0, 5) == "Name="){
            ret.first = line.substr(5);
        }else if(line.substr(0, 7) == "Hidden="){
            ret.second = (line.substr(7) == "false");
            break;
        }
    }
    return ret;
}

void SelfStarupPlugin::update(){
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir("/data/home/pundthsea/.config/autostart"))){
        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        pair<string, bool> ans= readfiles(string(ptr->d_name));
        selfSetUp[ans.first] = ans.second;
    }
    closedir(pDir);
}
