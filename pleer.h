#pragma once
#include <QObject>
#include <opencv2/videoio.hpp>
#include <map>
#include <memory>


namespace cv {
	class Mat;
}

class Pleer : public QObject
{
	Q_OBJECT

	cv::Mat currentFrame;
	cv::VideoCapture cap;
public:
	Pleer();
	~Pleer();

public slots:
	void start();

signals:
	void newFrame(std::shared_ptr<QByteArray> frame);

	void startPlay();
};


class PleerFactory
{

	static int count;
	static std::map <int, std::shared_ptr< Pleer>> pleers;
public:
	PleerFactory();
	~PleerFactory();

	static std::pair<int, std::shared_ptr<Pleer>>  preparePleer();
	static std::shared_ptr<Pleer> getPleer(int id);

};