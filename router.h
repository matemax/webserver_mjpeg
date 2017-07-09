#include <QMap>
#include <QRegExp>
#include "basichandler.h"

namespace Tufao
{
	class HttpServerRequest;
	class HttpServerResponse;

}

struct RegExpComparator {
	bool operator() (const QRegExp& key1, const QRegExp& key2) const {
		return key1.pattern() > key2.pattern();
	}
};

class Router
{
	std::map < QRegExp, BaseHandlersFactory*, RegExpComparator> routerMap;

	static void notFound404(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp);
public:
	Router();
	~Router();


	void newRequest(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp);
	//bool getHandler(QString path, BasicHandler* res);
	bool addRouter(BasicHandler* handler, QRegExp pathRegExp);

};