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
	QUdpSocket *UdpSender;//udp�׽��ַ�����
    QTcpSocket *TcpReciever;//tcp�׽��ַ�����
	QTcpServer* m_TcpServer;//tcp������
	QWidget* m_CentralWidget;//���Ĵ���
	QByteArray datagram;//��Ҫ���͵����� 
	QLabel* m_Label;
	QLineEdit* m_LineEdit;
	QPushButton* m_SendButton;
	public slots:
		void slot_Send();
		void acceptConnection();
public:
		void readClient();
	
};

