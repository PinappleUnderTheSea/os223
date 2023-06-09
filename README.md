# DDE 自启动管理插件

DDE 自启动管理插件可用于集中管理`Deepin`系统中软件开机自启动设置的插件。

## 参赛信息

本项目参加2023全国大学生计算机系统能力大赛操作系统设计赛-功能挑战赛，选题为[proj223-control-center-startup-management-plugin](https://github.com/oscomp/proj223-control-center-startup-management-plugin)。

参赛小组：

- 复旦大学 朱元依
- 复旦大学 沈扬
- 复旦大学 朱俊杰

指导老师：

- 复旦大学 张亮
- 复旦大学 陈辰
- 企业导师 王子冲

## 完成情况

项目文档位于根目录的`初赛报告.md`。\
博客地址：https://y-aang.github.io （题目：DDE 自启动管理插件）

| 任务                                                         | 完成情况                       |
| ------------------------------------------------------------ | ------------------------------ |
| （必须）完成一个控制中心插件，能够展示当前所有开机启动项的列表 | 完成                           |
| （必须）插件以单独的仓库提供，并能够单独构建，不需要合并入 dde-control-center 项目 | 完成                           |
| （必须）能够在插件中，通过用户界面的交互来管理（添加、删除、启用、禁用）开机启动项 | 完成                           |
| （必须）编写博客，记录开发过程的心得与体会，并将博客投递至 planet.deepin.org | 完成博客编写，待deepin官方审核 |

## 成果展示

插件图标：

![图标](./images/图标.png)

自启动管理窗口：

![前端界面](./images/前端界面.png)

## 部署方式

### 1、系统环境

开发环境：Deepin 20Beta版

系统架构：x86

镜像下载链接：http://uni.mirrors.163.com/deepin-cd/20/deepin-desktop-community-1003-amd64.iso

虚拟机平台：WMware Workstation 16Pro

操作系统环境搭建参考博客：https://blog.csdn.net/qq_44133136/article/details/105887560

### 2、安装依赖库

安装包 `build-essential`、`git`、`g++`、`cmake`、`dde`、`dtk`

```shell
sudo apt install build-essential git g++ cmake
sudo apt install dde-dock-dev libdtkwidget-dev
```

### 3、安装插件

克隆该仓库，进入文件夹后以`sudo`权限运行`install.sh`脚本

```shell
git clone https://github.com/PinappleUnderTheSea/os223.git
cd os233
sudo su
sh install.sh
```

出现`成果展示`章节的图标，即为安装成功。

## 提交仓库目录和文件描述
. \
├── CMakeLists.txt \
├── README.md \
├── aboutdialog.cpp&emsp;&emsp;&emsp;&ensp;#关于窗口的实现文件 \
├── aboutdialog.h&emsp;&emsp;&emsp;&emsp;&ensp;#关于窗口的头文件 \
├── aboutdialog.ui&emsp;&emsp;&emsp;&emsp;&ensp;#关于窗口的UI文件 \
├── appletwidget.cpp&emsp;&emsp;&emsp;#自启动管理窗口的实现文件 \
├── appletwidget.h&emsp;&emsp;&emsp;&emsp;#自启动管理窗口的头文件 \
├── images&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;#图片 \
│   ├── QT_IDE.png \
│   ├── QT_前端.png \
│   ├── deepin自启动修改.png \
│   ├── 类图.jpg \
│   ├── 右键.png \
│   ├── 图标.png \
│   ├── 结果.png \
│   ├── 中期类图.jpg \
│   ├── 中期测试.png \
│   └── 前端界面.png \
├── install.sh&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;#插件安装脚本 \
├── main_aboutdialog_test.cpp&emsp;#关于窗口的测试文件 \
├── main_test.cpp&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;#测试文件 \
├── mainwidget.cpp&emsp;&emsp;&emsp;&emsp;&emsp;#插件类的实现文件 \
├── mainwidget.h&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;#插件类的头文件 \
├── self_startup.json&emsp;&emsp;&emsp;&emsp;&ensp;#插件的元数据文件，指明了当前插件所使用的 dde-dock 的接口版本 \
├── self_startup.pro&emsp;&emsp;&emsp;&emsp;&emsp;#辅助 cmake 的配置文件 \
├── self_startup.qrc&emsp;&emsp;&emsp;&emsp;&emsp;#用于展示插件图片 \
├── selfstartupplugin.cpp&emsp;&emsp;&emsp;#部件类的实现文件 \
├── selfstartupplugin.h&emsp;&emsp;&emsp;&emsp;#部件类的头文件 \
├── uninstall.sh&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&ensp;#插件卸载脚本 \
├── 初赛报告.md \
└── 过程文档.md 
## 分工

朱元依：插件类框架开发、部件类前端开发

沈扬：自启动管理功能逻辑设计、插件类右键功能开发

朱俊杰：自启动管理窗口后端接口开发（添加、删除、启用、禁用）

## 开发计划

### 第一步（4/9～4/18）

- [x] 调研`Deepin`、`dde-dock`、`QT`框架等相关内容
- [x] 设计项目方案
- [x] 分工

### 第二步（4/19～5/2）

- [x] 搭建主体插件类的框架
- [x] 设计启动项管理窗口的前端展示页面

### 第三步（5/3～5/13）

- [x] 开发部件类接口
- [x] 完善插件类功能

### 第四步（5/14～5/21）

- [x] 插件类右键功能开发
- [x] 完成配置文件

### 第五步（5/22～5/31）

- [x] Debug
- [x] 撰写文档