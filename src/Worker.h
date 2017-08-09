#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>

#include "tcpserver.h"

class Worker : public QObject
{
	Q_OBJECT
public:
	Worker();

	void setRouter(Router router);
	void addConnection(qintptr socketDescriptor);

signals:
	void newConnection(qintptr socketDescriptor);
	void initReady();

	private slots:
	//void init();
	void onNewConnection(qintptr socketDescriptor);
	void onRequestReady();
	void onUpgrade();

private:
	Router router;
	QMutex factoryMutex;
};

#endif // WORKER_H