#include "plotter.h"
#include <QBrush>
#include <Qpen>
#include <QPainter>
#include <QColor>
#include <QDebug>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QPen pengrid;
    QBrush brush;
    int igridH=0;
    int igridV=0;

    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor(QColor(255,255,0));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);

    pen.setColor(QColor(255,255,0));
    pen.setWidth(2);

    painter.setPen(pen);

    painter.drawRect(0,0,width(), height());

    pengrid.setStyle(Qt::DashLine);
    pengrid.setWidth(1);
    pengrid.setColor(QColor(100,100,100));
    painter.setPen(pengrid);


    while( igridV< width()){

        painter.drawLine(igridV, 0, igridV, height());
        igridV+=width()/15;
    }

    while (igridH<height()){
        painter.drawLine(0,igridH, width(), igridH);
        igridH+=height()/15;
    }

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(QColor(255,0,0));

    painter.setPen(pen);

    for(int i=0; i<(tempo.size()-1) && tempo.size()!=0; i++){
        painter.drawLine(width()-width()*tempo[i], height()-height()*(valor[i]*0.01),
                     width()-width()*tempo[i+1], height()-height()*(valor[i+1]*0.01));
    }
}

void Plotter::recebeDados(vector<float> tempo_, vector<float> valor_)
{
    tempo=tempo_;
    valor=valor_;

    repaint(); 
}

