#include "plotter.h"
#include <QBrush>
#include <Qpen>
#include <QPainter>
#include <QColor>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor(QColor(255,255,0));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);

    pen.setColor(QColor(255,0,0));
    pen.setWidth(2);

    painter.setPen(pen);

    painter.drawRect(0,0,width(), height());
}

