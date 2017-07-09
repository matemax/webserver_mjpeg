#include "pleer.h"
#include "opencv2/opencv.hpp"
#include <QtCore/QCoreApplication>
#include  <QObject>
#include <QDebug>
#include <memory>
#include <QThread>


int PleerFactory::count = 0;
std::map <int,std::shared_ptr< Pleer>> PleerFactory::pleers;


Pleer::Pleer()
{
}

Pleer::~Pleer()
{
}

void Pleer::start()
{
	qDebug() << "Start video";
	if (!cap.open(0))
		return;
	while (true)
	{
		cap >> currentFrame;
		if (currentFrame.empty()) break; 

		std::vector<uchar> buff;
		imencode(".jpg", currentFrame, buff);

		QByteArray CurrentImg(reinterpret_cast<char*>(buff.data()), buff.size());

		auto imgArray = std::make_shared<QByteArray>(CurrentImg);

		emit newFrame(imgArray);
		QCoreApplication::processEvents();
	}

}

std::shared_ptr<Pleer> PleerFactory::getPleer(int id)
{
	return  pleers[id];
}

PleerFactory::PleerFactory()
{
}

PleerFactory::~PleerFactory()
{
}

std::pair<int, std::shared_ptr<Pleer>> PleerFactory::preparePleer()
{
	count++;

	auto pleer = std::make_shared<Pleer>();
	
	auto pleerThread = new QThread();
	pleerThread->start();

	pleer->moveToThread(pleerThread);
	QObject::connect(pleer.get(), &Pleer::startPlay, pleer.get(), &Pleer::start);
	pleers[count] = pleer;
	return  std::make_pair(count, pleer);

}
