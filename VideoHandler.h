#include "basichandler.h"

class VidoeHandler: public  BasicHandler
{
	int start();
	void stop();

	
public:
	VidoeHandler();
	VidoeHandler(Tufao::HttpServerRequest& tufaoReq, Tufao::HttpServerResponse& tufaResp, int handId = 0);
	~VidoeHandler();
	void reDraw(std::shared_ptr<QByteArray> frame);
	
	void GET() override;
	void POST() override;
};