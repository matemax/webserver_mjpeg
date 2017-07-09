#pragma once
#include <QString>
#include <memory>
#include <qobjectdefs.h>
#include <HttpServerRequest>
#include <Headers>
//#include <assert.h>
#include <HttpServer>


//namespace Tufao
//{
//	class HttpServerRequest;
//	class HttpServerResponse;
//
//}




class BasicHandler:public QObject
{
	Q_OBJECT
protected:
	Tufao::HttpServerRequest& req;
	Tufao::HttpServerResponse& resp;
	void setMethodNotAllowed(QString method);
	int handlerId = 0;
public:
	//BasicHandler(Tufao::HttpServerRequest * tufaoReq, Tufao::HttpServerResponse *tufaResp, int handId = 0);
	BasicHandler(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp, int handId = 0);
	//BasicHandler();
	virtual ~BasicHandler();

	virtual void POST();
	virtual void PUT();
	virtual void GET();
	virtual void OPTIONS();
	virtual void PATCH();
	virtual void DELETE();
	virtual void UNKNOWN(QString method);
	void doMethod();
};


class HandlersFactorySignalsSlots : public QObject
{
	Q_OBJECT
public:

	~HandlersFactorySignalsSlots() {};
	explicit HandlersFactorySignalsSlots(QObject *parent = nullptr) :
		QObject(parent) {}
public slots:
	virtual void removeHandler(int countConnection){};
};

class BaseHandlersFactory : public HandlersFactorySignalsSlots
{
public:
	BaseHandlersFactory() : HandlersFactorySignalsSlots() {};
	~BaseHandlersFactory() {};
	virtual void newConnection(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse&tufaResp) = 0;
};



template<typename T>
class HandlersFactory: BaseHandlersFactory
{

	QMap<int, std::shared_ptr<T>> connections;
	int countConnections = 0;
public:
	HandlersFactory()	{};

	~HandlersFactory() {};

	void newConnection(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp) override
	{
		connect(&tufaoReq.socket(), SIGNAL(disconnected()), &tufaoReq, SLOT(deleteLater()));
		
		auto id = countConnections;
		auto handler = std::make_shared<T>(tufaoReq, tufaResp, id);
		
		QObject::connect(&tufaoReq, &Tufao::HttpServerRequest::close, this, [this, id]()
		{
			removeHandler(id);
		}
		);
		connect(&tufaoReq.socket(), &QAbstractSocket::disconnected,  this, [this, id]()
		{
			removeHandler(id);
		}
		);

		connections.insert(countConnections, handler);
		handler->doMethod();
		countConnections++;
	};

	void removeHandler(int countConnection) override
	{
		qDebug() << "Remove connection";
		auto countRemoveConnections = connections.remove(countConnection);
		//assert(countRemoveConnections > 0 );
	}
};