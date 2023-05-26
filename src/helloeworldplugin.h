class HelloWorldPlugin : public QObject, public DCC_NAMESPACE::ModuleInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ModuleInterface_iid)
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)
public:
    HelloWorldPlugin(QObject *parent = nullptr)
    : QObject(parent)
    , DCC_NAMESPACE::ModuleInterface() 
    {}
    
    // 重写纯虚函数
    virtual void initialize() override {
        // 进行初始化操作，对于我们的插件来说，不需要做任何事情。
    }
    virtual const QString name() const override {
        return "helloworldplugin";
    }
    virtual const QString displayName() const override {
        return tr("HelloWorld Plugin");
    }
    // 重写虚函数
    virtual QWidget* moduleWidget() const override {
        if (!m_mainPage) {
          m_mainPage = new QWidget(this);
        }
        
        return m_mainPage;
    }
private:
    QPointer<QWidget> m_mainPage;
  };
#define ModuleInterface_iid "com.deepin.dde.ControlCenter.module/1.0"
Q_DECLARE_INTERFACE(DCC_NAMESPACE::ModuleInterface, ModuleInterface_iid)