#include "basichandler.h"



void BasicHandler::setMethodNotAllowed(QString method)
{

	resp.writeHead(Tufao::HttpResponseStatus::OK);
	resp.headers().replace("Content-Type", "text/plain");
	resp.writeHead(Tufao::HttpResponseStatus::METHOD_NOT_ALLOWED);
	resp.end((QString("Method '") + method + QString("' not allowed")).toUtf8());
}

//BasicHandler::BasicHandler(Tufao::HttpServerRequest* tufaoReq, Tufao::HttpServerResponse* tufaResp, int handId)
//{
//	req = tufaoReq;
//	resp = tufaResp;
//	handlerId = handId;
//}


BasicHandler::BasicHandler(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp, int handId): req(tufaoReq), resp(tufaResp)
{
	//req = tufaoReq;
	//resp = tufaResp;
	handlerId = handId;
}
//BasicHandler::BasicHandler()
//{
//}

BasicHandler::~BasicHandler()
{
}

void BasicHandler::POST()
{
	setMethodNotAllowed("POST");
}

void BasicHandler::PUT()
{
	setMethodNotAllowed("PUT");
}

void BasicHandler::GET()
{
	setMethodNotAllowed("GET");
}

void BasicHandler::OPTIONS()
{
	setMethodNotAllowed("OPTIONS");
}

void BasicHandler::PATCH()
{
	setMethodNotAllowed("PATCH");
}

void BasicHandler::DELETE()
{
	setMethodNotAllowed("DELETE");
}

void BasicHandler::UNKNOWN(QString method)
{
	setMethodNotAllowed(method);
}

void BasicHandler::doMethod()
{
	auto requerstMethod = QString(req.method());
	if(requerstMethod == "GET")
		return GET();
	if(requerstMethod == "POST")
		return POST();
	if(requerstMethod == "PUT")
		return PUT();
	if (requerstMethod == "PATCH")
		return PATCH();
	if (requerstMethod == "OPTIONS")
		return OPTIONS();
	if (requerstMethod == "DELETE")
		return DELETE();
	return UNKNOWN(requerstMethod);
}
