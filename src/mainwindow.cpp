#pragma once

#include "mainwindow.h"
#include <qpushbutton.h>
#include <QTextBrowser>
#include <QGridLayout>
#include <QSpacerItem>
#include <QObject>
#include <qlabel.h>

#include <HttpServer>
#include <HttpServerRequest>
#include <HttpServerResponse>



GMainWindow::GMainWindow()
{
	this->setWindowTitle("MainWindow");

	

	gridLayout = new QGridLayout();
	textinfo = new QTextBrowser();
	

	gridLayout->addWidget(textinfo, 0, 0);
	
	
}


GMainWindow::~GMainWindow()
{}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new GMainWindow)
{	
	QWidget *window = new QWidget();
	window->setLayout(ui->gridLayout);
	this->setCentralWidget(window);

	server = new Tufao::HttpServer();

	server->listen(QHostAddress::Any, 8080);
	
	connect(server,
			&Tufao::HttpServer::requestReady,
			this, 
			&MainWindow::newuser);	
}

MainWindow::~MainWindow()
{
    server_status=0;
}


void MainWindow::newuser(Tufao::HttpServerRequest& req, Tufao::HttpServerResponse& res)
{
	qDebug() << "new user";
	router.newRequest(req, res);
}


