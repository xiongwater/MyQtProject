#pragma once
#include "qmainwindow.h"
#include <QtNetwork>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
class LittleClient :
	public QMainWindow
{
	Q_OBJECT
public:
	LittleClient(void);
	virtual ~LittleClient(void);
	QTcpSocket* m_TcpSocket;
	QUdpSocket *UdpReceiver;//udp
	QWidget* m_CentralWidget;//中心窗体
	QByteArray datagram;//接受到的数据
	QLabel* m_Label;
	QPushButton* m_ShowButton;

	//信号槽
	private slots:  
		void readPendingDatagrams();
		void sendTcp();
		void ConnectToServerSuccessed();

};

