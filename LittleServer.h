#pragma once
#include "qmainwindow.h"

#include <QtNetwork>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class LittleServer :
	public QMainWindow
{
	Q_OBJECT
public:
	LittleServer(void);
	virtual ~LittleServer(void);

public: 
	QUdpSocket *UdpSender;//udp套接字发送器
    QTcpSocket *TcpReciever;//tcp套接字发送器
	QTcpServer* m_TcpServer;//tcp服务器
	QWidget* m_CentralWidget;//中心窗体
	QByteArray datagram;//需要发送的数据 
	QLabel* m_Label;
	QLineEdit* m_LineEdit;
	QPushButton* m_SendButton;
	public slots:
		void slot_Send();
		void acceptConnection();
public:
		void readClient();
	
};

