# 添加所需的 Qt 模块 
QT += widgets 
# 指定生成目标为共享库 
TEMPLATE = lib 
# 指定生成目标为 Qt 插件 
CONFIG += plugin c++11 
# 指定生成目标的名称 
TARGET = $$qtLibraryTarget(self_startup) 
# 指定生成目标的目录 
DESTDIR = $$_PRO_FILE_PWD_ 
# 添加必要的文件到插件中 
DISTFILES += self_startup.json 
HEADERS += \
    selfstartupplugin.h \
    mainwidget.h
SOURCES += \
    selfstartupplugin.cpp \
    mainwidget.cpp
# 以下是安装相关的设定 
isEmpty(PREFIX) {
              PREFIX = /usr
            }
target.path = $${PREFIX}/lib/dde-dock/plugins/ 
INSTALLS += target