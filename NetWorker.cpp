#include "NetWorker.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
class NetWorker::Private
{
public:
	Private(NetWorker *q) :
	  manager(new QNetworkAccessManager(q))
	  {}

	  QNetworkAccessManager *manager;
};


NetWorker::NetWorker(QObject *parent) :
QObject(parent),
	d(new NetWorker::Private(this))
{
	connect(d->manager,SIGNAL(finished(QNetworkRequest* reply)),this, SLOT(finished(QNetworkRequest* reply)));
}

NetWorker::~NetWorker()
{
	delete d;
	d = 0;
}

void NetWorker::get(const QString &url)
{
	d->manager->get(QNetworkRequest(QUrl(url)));
}
