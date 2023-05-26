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
    if(centralLayout==NULL)
    {
        //创建新的ui
        qDebug()<<"创建新的文字ui";
        Label=new QLabel();
        Label->setAlignment(Qt::AlignCenter);
        centralLayout = new QBoxLayout(QBoxLayout::LeftToRight);
        centralLayout->addWidget(Label);
        centralLayout->setMargin(0);
        setLayout(centralLayout);
    }
    centralLayout->setSpacing(4);
    font.setPixelSize((dpi*9)/72);
    Label->setFont(font);

    QString style;
    style=QString("QLabel {color: %1;}").arg("#000");
    Label->setStyleSheet(style);

    Label->setVisible(true);
    Label->setText(QString("SELF_STARTUP"));
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