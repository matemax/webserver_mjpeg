#include "router.h"
#include <HttpServerRequest>

#include <HttpServerResponse>
#include <HttpServer>
#include "basichandler.h"
#include "VideoHandler.h"
#include <Headers>
#include <QtCore>



Router::Router()
{
	auto hf = new HandlersFactory<BasicHandler> ;
	auto hv = new HandlersFactory<VidoeHandler>;
	routerMap.insert(std::make_pair(QRegExp("/testReg"), reinterpret_cast<BaseHandlersFactory*>(hf)));
	routerMap.insert(std::make_pair(QRegExp("/video"), reinterpret_cast<BaseHandlersFactory*>(hv)));
}

Router::~Router()
{
}

void Router::newRequest(Tufao::HttpServerRequest& req, Tufao::HttpServerResponse& resp)
{
	auto path = req.url().path();
	for (auto iter = routerMap.begin(); iter != routerMap.end(); ++iter)
	{
		if(iter->first.exactMatch(path))
		{
			return iter->second->newConnection(req, resp);
		}
	}
	notFound404(req, resp);
}


bool Router::addRouter(BasicHandler* handler, QRegExp pathRegExp)
{
	auto res = routerMap.find(pathRegExp);
	if (res != routerMap.end())
		return false;
	return true;
}



void Router::notFound404(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp)
{
	qDebug() << "NOT FOUND";
	tufaResp.headers().replace("Content-Type", "text/plain");
	tufaResp.writeHead(Tufao::HttpResponseStatus::NOT_FOUND);
	tufaResp.end("Resource not found");
}