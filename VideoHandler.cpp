#include "VideoHandler.h"
#include "pleer.h"
#include <thread>

#include <QJsonValue>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QUrlQuery>

int VidoeHandler::start()
{
	return 0;
}

void VidoeHandler::stop()
{
}

void VidoeHandler::reDraw(std::shared_ptr<QByteArray> frame)
{
	QByteArray BoundaryString = ("--boundary\r\n" \
		"Content-Type: image/jpeg\r\n" \
		"Content-Length: ");
	BoundaryString.append(QString::number(frame->length()));
	BoundaryString.append("\r\n\r\n");
	//auto client = req;
	req.socket().write(BoundaryString);
	req.socket().write(*frame.get()); // Write The Encoded Image
	req.socket().flush();
}

VidoeHandler::VidoeHandler(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp, int handId):BasicHandler(tufaoReq, tufaResp, handId)
{
}

VidoeHandler::~VidoeHandler()
{
}

void VidoeHandler::GET()
{
	auto queryes = QUrlQuery(req.url());
	auto id = -1;
	for(auto queryPair : queryes.queryItems())
	{
		if(queryPair.first == "id")
		{
			id = queryPair.second.toInt();
		}
	}
	if(id == -1)
	{
		resp.headers().replace("Content-Type", "text/plain");
		resp.writeHead(Tufao::HttpResponseStatus::BAD_REQUEST);

		resp.end(QString("Video not found").toUtf8());
	}

	QByteArray ContentType = ("HTTP/1.0 200 OK\r\n" \
		"Server: en.code-bude.net example server\r\n" \
		"Cache-Control: no-cache\r\n" \
		"Cache-Control: private\r\n" \
		"Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n\r\n");
	req.socket().write(ContentType);
	auto pleer = PleerFactory::getPleer(id);
	connect(pleer.get(), &Pleer::newFrame, this, &VidoeHandler::reDraw);
	connect(pleer.get(), &Pleer::newFrame, this, [this](std::shared_ptr<QByteArray> frame)
	{
		QByteArray BoundaryString = ("--boundary\r\n" \
			"Content-Type: image/jpeg\r\n" \
			"Content-Length: ");
		BoundaryString.append(QString::number(frame->length()));
		BoundaryString.append("\r\n\r\n");
		//auto client = req;
		req.socket().write(BoundaryString);
		req.socket().write(*frame.get()); // Write The Encoded Image
		req.socket().flush();
	});
}

void VidoeHandler::POST()
{
	auto pleerAndId = PleerFactory::preparePleer();
	auto pleer = pleerAndId.second;
	//std::thread thr([&]() {pleer->start(); });
	//thr.detach();
	emit pleer->startPlay();
	QJsonObject responsePayload;
	responsePayload["video_id"] = pleerAndId.first;

	resp.writeHead(Tufao::HttpResponseStatus::OK);
	resp.headers().replace("Content-Type", "application/json");

	QJsonDocument doc(responsePayload);
	resp.end(doc.toJson());

}
