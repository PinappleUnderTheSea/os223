#include "mainwidget.h"
#include <DFontSizeManager>
#include <DGuiApplicationHelper>

DGUI_USE_NAMESPACE

MainWidget::MainWidget()
{
    centralLayout=NULL;
    //setMinimumSize(5,5);
    //设置等宽字体
    font.setFamily("Noto Mono");
    // 获取dpi，一般默认都是96，根据dpi进行字体的缩放，直接设置pointsize无法解决hidpi问题
    dpi = QApplication::primaryScreen()->logicalDotsPerInch();
}

MainWidget::~MainWidget()
{
    if(centralLayout!=NULL){delete centralLayout;centralLayout=NULL;}
}

QSize MainWidget::sizeHint() const
{
    if(centralLayout==NULL)return QSize(100,30);
    int w,h;
    w=QFontMetrics(font).boundingRect(QString("SELF-STARTUP")).size().width();
    h=QFontMetrics(font).boundingRect(QString("SELF-STARTUP")).size().height();
    QSize size(w,h);
    //qDebug()<<size;
    //qDebug()<<QString("width:%1    height:%2").arg(width()).arg(height());
    return size;
}