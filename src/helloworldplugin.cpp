#include "interface/namespace.h"
#include "interface/moduleinterface.h"
#include "interface/frameproxyinterface.h"

// preInitialize会在模块初始化时被调用，用于模块在准备阶段进行资源的初始化；
// preInitialize不允许进行高资源的操作；
virtual void preInitialize(bool sync = false,FrameProxyInterface::PushType = FrameProxyInterface::PushType::Normal) {Q_UNUSED(sync)}
// initialize初始化相应的模块，参数proxy用于Moudle向Frame信息查询和主动调用；
// 返回Module的id；
// initialize的时候不能做资源占用较高的操作；
virtual void initialize() = 0;
// 保留，该接口用于重设插件的所有设置。
virtual void reset() {}
///
/// \brief name
/// 插件提供的模块名称，用于内部标识。
/// \return
///
virtual const QString name() const = 0;
///
/// \brief name
/// 模块名，用于显示
/// \return
///
virtual const QString displayName() const = 0;
///
/// \brief icon
/// 获取模块的图标路径。
/// \return
///
virtual QIcon icon() const {
    return QIcon::fromTheme(QString("dcc_nav_%1").arg(name()));
}
///
/// \brief translationPath
/// 获取多语言文件的路径，用以搜索
/// \return QString
///
virtual QString translationPath() const {
    return QStringLiteral(":/translations/dde-control-center_%1.ts");
}
// 应该暂时不需要finalize；
// virtual void finalize();
// 获取Module的Metadata;
// virtual ModuleMetadata getMetadata();
///
/// \brief showPage
/// 显示指定的某个页面
/// \param pageName
/// the page name
///
virtual void showPage(const QString &pageName) { Q_UNUSED(pageName); }
// 返回模块主Widget；
virtual QWidget *moduleWidget() { return nullptr;}
///
/// \brief contentPopped
/// 弹出指定的页面
/// \param w
///
virtual void contentPopped(QWidget *const w) { Q_UNUSED(w);}
///
/// \brief active
/// 当模块第一次被点击进入时，active会被调用,如果是插件,重载的时候必须声明为slots,否则加载不了
virtual void active() {}
///
/// \brief active
/// 当模块被销毁时，deactive会被调用
virtual void deactive() {}
///
/// \brief load
/// 当搜索到相关字段后，lead会被调用
/// 如果可以正常显示则返回 0, 否则返回非0
virtual int load(const QString &path) {
    Q_UNUSED(path);
    return 0;
}
virtual QStringList availPage() const { return QStringList(); }
/**
 * @brief path
 * @return 插件级别及二级菜单插件所属模块
 */
virtual QString path() const {
    return QString();
}
/**
 * @brief follow
 * @return 插件插入位置，可以字符串或者数字
 */
virtual QString follow() const {
    return QString();
}
/**
 * @brief enabled
 * @return 插件是否处于可用状态
 */
virtual bool enabled() const {
    return true;
}
