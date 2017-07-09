#pragma once

#include "mainwindow.h"
#include <qpushbutton.h>
#include <QTextBrowser>
#include <QGridLayout>
#include <QSpacerItem>
#include <QPixmap>
#include <QBitmap>
#include <QObject>
#include <qlabel.h>
#include <QtCore/QCoreApplication>

#include <HttpServer>
#include <HttpServerRequest>
#include <Headers>
#include <HttpServerResponse>
#include <memory>
#include <QRegExp>
#include "pleer.h"



GMainWindow::GMainWindow()
{
	this->setGeometry( QRect(0, 0, 796, 484));
	this->setWindowTitle("MainWindow");

	horizontalSpacer = new QSpacerItem(653, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
	

	gridLayout = new QGridLayout();
	textinfo = new QTextBrowser();
	stoping = new QPushButton("stop");
	starting = new QPushButton("start");
	webLabel = new QLabel;
	

	gridLayout->addWidget(textinfo, 0, 0);
	gridLayout->addWidget(webLabel, 0, 1, Qt::AlignHCenter);
	gridLayout->addWidget(stoping, 1, 0);
	gridLayout->addItem(horizontalSpacer, 1, 1);
	gridLayout->addWidget(starting, 1, 2);
	
	
}


GMainWindow::~GMainWindow()
{}

void MainWindow::drawWeb() 
{
	//auto pl = PleerFactory::preparePleer();
	//pl->start();
	//if (server_status == 1)
	//{
	//	// open the default camera, use something different from 0 otherwise;
	//	// Check VideoCapture documentation.
	//	if (!cap.open(0))
	//		return;
	//	while (server_status == 1)
	//	{
	//	
	//		cap >> currentFrame;
	//		if (currentFrame.empty()) break; // end of video stream

	//		auto pixmap = QPixmap::fromImage(QImage((unsigned char*)currentFrame.data, currentFrame.cols, currentFrame.rows, QImage::Format_RGB888));
	//		
	//		ui->webLabel->setPixmap(pixmap);
	//		ui->webLabel->setMask(pixmap.mask());


	//		sendMjpeg();
	//		QCoreApplication::processEvents();
	//		
	//		//imshow("this is you, smile! :)", frame);
	//		//if (waitKey(10) == 27) break; // stop capturing by pressing ESC 
	//	}
	//	

	//}
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new GMainWindow)
{
	
	QWidget *window = new QWidget();
	window->setLayout(ui->gridLayout);
	this->setCentralWidget(window);
	//ui->show();
	connect(ui->starting,
		SIGNAL(clicked()),
		this,
		SLOT(on_starting_clicked()));

	connect(ui->stoping,
		SIGNAL(clicked()),
		this,
		SLOT(on_stoping_clicked()));

	server = new Tufao::HttpServer();

	server->listen(QHostAddress::Any, 8080);
	
	connect(server,
			&Tufao::HttpServer::requestReady,
			this, 
			&MainWindow::newuser);	
	//QObject::connect(server, &Tufao::HttpServer::requestReady,
	//	[](Tufao::HttpServerRequest &req, Tufao::HttpServerResponse &res) {
	//	res.writeHead(Tufao::HttpResponseStatus::OK);
	//	res.headers().replace("Content-Type", "text/plain");
	//	res.end("Hello " + req.url().path().toUtf8());
	//});
}

MainWindow::~MainWindow()
{
    server_status=0;
}

void MainWindow::on_starting_clicked()
{
   /* tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, 33333) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        ui->textinfo->append(tcpServer->errorString());
    } else {
        server_status=1;
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        ui->textinfo->append(QString::fromUtf8("Сервер запущен!"));
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }*/
	qDebug() << server->isListening();

	drawWeb();
}

void MainWindow::on_stoping_clicked()
{
    if(server_status==1){
        //tcpServer->close();
        ui->textinfo->append(QString::fromUtf8("Сервер остановлен!"));
        qDebug() << QString::fromUtf8("Сервер остановлен!");
        server_status=0;
    }
}

void MainWindow::newuser(Tufao::HttpServerRequest& req, Tufao::HttpServerResponse& res)
{
	qDebug() << "new user";
	router.newRequest(req, res);
	return;
	qDebug() << req.url().path() << req.url().query();
	auto testReg = QRegExp("/test");

	auto currentCount = countClients;
	qDebug() << "New client" << currentCount;
	clients.insert( countClients, &req);
	aliveClients.insert(countClients, true);
	countClients++;
	connect(&req.socket(), SIGNAL(disconnected()), &req, SLOT(deleteLater()));
	req.setTimeout(10000000);
	connect(&req.socket(), &QAbstractSocket::disconnected, this, [this, currentCount]()
	{
		aliveClients[currentCount] = false;
		qDebug() << "Removing element " << currentCount;
		auto countRemovingElement = clients.remove(currentCount);
		qDebug() << "Was removed: " << countRemovingElement;

	});
	QByteArray ContentType = ("HTTP/1.0 200 OK\r\n" \
		"Server: en.code-bude.net example server\r\n" \
		"Cache-Control: no-cache\r\n" \
		"Cache-Control: private\r\n" \
		"Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n\r\n");
	req.socket().write(ContentType);
}


void MainWindow::sendMjpeg()
{
	std::vector<uchar> buff;
	imencode(".jpg", currentFrame, buff);
	//std::string content(buff.begin(), buff.end());

	QByteArray CurrentImg(reinterpret_cast<char*>(buff.data()), buff.size());//QByteArray::fromStdString(content));
	QByteArray BoundaryString = ("--boundary\r\n" \
		"Content-Type: image/jpeg\r\n" \
		"Content-Length: ");
	BoundaryString.append(QString::number(CurrentImg.length()));
	BoundaryString.append("\r\n\r\n");
	//qDebug() << clients.size();
	for(auto iter = aliveClients.begin(); iter != aliveClients.end(); ++iter)
	{
		if (iter.value())
		{
			auto client = clients[iter.key()];
			client->socket().write(BoundaryString);
			client->socket().write(CurrentImg); // Write The Encoded Image
			client->socket().flush();
		}	
	}
	auto iter = aliveClients.begin();
	while(iter != aliveClients.end())
	{
		if(!iter.value())
		{
			iter = aliveClients.erase(iter);
			continue;
		}
		iter++;
	}
	QCoreApplication::processEvents();
	//qDebug() << "end send frame";
}
