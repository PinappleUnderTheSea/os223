#include "pluginwidget.h"
#include "dde-dock/constants.h"
#include <QApplication>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#define PLUGIN_STATE_KEY    "enable"

PluginWidget::PluginWidget(QWidget *parent)
    : QWidget(parent)
{
    text = "SELF-STARTUP";
    // mp = 0;
    // cp = 0;
}

bool PluginWidget::enabled()
{
    return m_settings.value(PLUGIN_STATE_KEY, true).toBool();
}

void PluginWidget::setEnabled(const bool b)
{
    m_settings.setValue(PLUGIN_STATE_KEY, b);
}

QSize PluginWidget::sizeHint() const
{
    QFont font = qApp->font();
    font.setFamily("Noto Mono");
    QFontMetrics FM(font);
    return FM.boundingRect(" SELF-STARTUP ").size());
}

void PluginWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void PluginWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);
    QFont font = qApp->font();
    font.setFamily("Noto Mono");
    painter.setFont(font);
    painter.drawText(rect().adjusted(2,0,0,0), Qt::AlignLeft | Qt::AlignVCenter, text);
}