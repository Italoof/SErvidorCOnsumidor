#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  nTimers=0;
  tcpConnect();

  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));

  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));

  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(startButtom()));

  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopButtom()));
}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->lineEdit->text(),1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::startButtom(){
    if(nTimers==0){

        id=startTimer(1000/ui->horizontalSliderTiming->value());

        nTimers=1;
    }
}

void MainWindow::stopButtom(){
    if(nTimers==1){

        killTimer(id);

        nTimers=0;
    }
}

void MainWindow::getData(){
  QString str;
  QByteArray array;
  QStringList list;
  std::vector <qint64> auxtempo;
  qint64 thetime;
  qDebug() << "to get data...";
  array=QByteArray("get "+ui->lineEdit->text().toUtf8()+" 30\r\n");
  qDebug()<<array;
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write(array);
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          qDebug() <<"list.at(0)=" <<str<<"\n\r";
          thetime = str.toLongLong(&ok);
          auxtempo.push_back(thetime);
          str = list.at(1);
          valor.push_back(str.toFloat());
          qDebug() << thetime << ": " << str;
        }
      }
      for (int i=0; i<auxtempo.size(); i++){
        tempo.push_back((float)((auxtempo[i]-auxtempo[0])/(auxtempo[auxtempo.size()-1]-auxtempo[0])));
      }
    }
  }
}

void MainWindow:: timerEvent(QTimerEvent *event){
    getData();
}

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
