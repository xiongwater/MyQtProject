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
	QWidget* m_CentralWidget;//���Ĵ���
	QByteArray datagram;//���ܵ�������
	QLabel* m_Label;
	QPushButton* m_ShowButton;

	//�źŲ�
	private slots:  
		void readPendingDatagrams();
		void sendTcp();
		void ConnectToServerSuccessed();

};

