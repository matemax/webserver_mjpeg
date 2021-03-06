/*
  Copyright (c) 2013 Vinícius dos Santos Oliveira

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>

#include <HttpServer>
#include <HttpServerRequest>
#include <Headers>
#include <HttpServerResponse>
#include "mainwindow.h"
#include <QApplication>


using namespace Tufao;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //HttpServer server;

    //QObject::connect(&server, &HttpServer::requestReady,
    //                 [](HttpServerRequest &req, HttpServerResponse &res) {
    //                     res.writeHead(Tufao::HttpResponseStatus::OK);
    //                     res.headers().replace("Content-Type", "text/plain");
				//		 //res.write)()
    //                     res.end("Hello " + req.url().path().toUtf8());
    //                 });

    //server.listen(QHostAddress::Any, 8080);

    //return a.exec();


	qRegisterMetaType<std::shared_ptr<QByteArray>>("std::shared_ptr<QByteArray>");



	QApplication a(argc, argv);
	MainWindow w;
	w.show();




	return a.exec();


}
