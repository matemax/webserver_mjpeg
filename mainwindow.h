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
	QPushButton *stoping;
	QPushButton *starting;
	QSpacerItem* horizontalSpacer;
	QLabel *webLabel;
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
private:
		void sendMjpeg();
private slots:
	void drawWeb();
	void on_starting_clicked();
    void on_stoping_clicked();
public slots:
    void newuser(Tufao::HttpServerRequest &req,
		Tufao::HttpServerResponse &res);

private:
	cv::Mat currentFrame;
	VideoCapture cap;
	GMainWindow *ui;
   // QTcpServer *tcpServer;
    int server_status;
    QMap<int, Tufao::HttpServerRequest *> clients;
	QMap<int, bool> aliveClients;
	int countClients = 0;
	Tufao::HttpServer* server;
	bool isBlock = true;
	//BasicHandler bhandler;
	Router router;
};

#endif // MAINWINDOW_H

