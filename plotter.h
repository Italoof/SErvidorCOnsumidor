#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <vector>

using namespace std;

class Plotter : public QWidget
{
    Q_OBJECT
    vector <float> tempo, valor;
public:
    explicit Plotter(QWidget *parent = 0);
    void paintEvent(QPaintEvent * event);
signals:

public slots:
    void recebeDados(vector<float> tempo_,vector<float> valor_);
};

#endif // PLOTTER_H
