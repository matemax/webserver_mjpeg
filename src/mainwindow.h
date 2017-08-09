#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>

#include <HttpServerRequest>
#include <Headers>
#include <HttpServerResponse>
#include <HttpServer>
#include "basichandler.h"
#include "router.h"
#include "TCPServer.h"

class QGridLayout;
class QTextBrowser;
class QPushButton;
class QSpacerItem;
class QLabel;
#include "opencv2/opencv.hpp"
using namespace cv;





class GMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	QWidget *centralWidget;
	QGridLayout *gridLayout;
	QTextBrowser *textinfo;
	GMainWindow();
	~GMainWindow();
	
};

namespace  Tufao{
	class HttpServerRequest;
}

class QTcpServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  /*  void newuser(Tufao::HttpServerRequest &req,
		Tufao::HttpServerResponse &res);*/

private:
	GMainWindow *ui;
   // QTcpServer *tcpServer;
	TcpServer* server;
    int server_status;
	/*Tufao::HttpServer* server;
	*/bool isBlock = true;
	//BasicHandler bhandler;
	/*Router router;*/
};

#endif // MAINWINDOW_H

