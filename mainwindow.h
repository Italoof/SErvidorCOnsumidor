#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

    int nTimers;
    int id;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

    void timerEvent(QTimerEvent * event);

public slots:
  void getData();
  void tcpConnect();
  void tcpDisconnect();
  void startButtom();
  void stopButtom();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
