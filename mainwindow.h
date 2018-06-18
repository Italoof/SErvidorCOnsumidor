#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

    int nTimers;
    int id;
    std::vector <float> tempo, valor;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

    void timerEvent(QTimerEvent * event);

    void enviarDados();
public slots:
  void getData();
  void tcpConnect();
  void tcpDisconnect();
  void startButtom();
  void stopButtom();

signals:
  std::vector <float> emiteDados(std::vector<float>, std::vector<float>);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
