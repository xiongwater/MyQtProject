#include "LittleClient.h"
#include <MyApp.h>

LittleClient::LittleClient(void)
	:UdpReceiver(new QUdpSocket(this))
{

	UdpReceiver->bind(QHostAddress::LocalHost, 6665);//�󶨶˿�
	connect(UdpReceiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
	m_CentralWidget=new QWidget(this);
	QHBoxLayout* mainLayout=new QHBoxLayout(this);
	m_ShowButton=new QPushButton("��ʾ",this);
	m_Label=new QLabel("��ʼ",this);

	mainLayout->addStretch();
	mainLayout->addWidget(m_ShowButton);
	mainLayout->addWidget(m_Label);
	mainLayout->addStretch();
	this->setCentralWidget(m_CentralWidget);
	m_CentralWidget->setLayout(mainLayout);
	


	m_TcpSocket=new QTcpSocket(this);
	//m_TcpSocket->abort();
	connect(m_TcpSocket,SIGNAL(connected()),this,SLOT(ConnectToServerSuccessed()));
	m_TcpSocket->connectToHost(QHostAddress::LocalHost,MyApp::getInstance()->m_Config->value("ContentTest/LittleServer_Port", "").toString().toInt());//���ӷ�����
	bool isConnected=m_TcpSocket->waitForConnected();//ֻ��ʹ��waitForConnected()��,QTcpSocket�������������ӷ��������������Ƿ����ӵĽ����
	//m_TcpSocket->connectToHost("192.168.20.156", 9999);//�Ƚ�������
	connect(m_ShowButton,SIGNAL(clicked()),this,SLOT(sendTcp()));
	
}


LittleClient::~LittleClient(void)
{
}

void LittleClient::readPendingDatagrams()
{
   	while (UdpReceiver->hasPendingDatagrams()) {
		datagram.resize(UdpReceiver->pendingDatagramSize());
		UdpReceiver->readDatagram(datagram.data(), datagram.size());
		m_Label->setText(QString(datagram));
		//���ݽ�����datagram��
		/* readDatagram ����ԭ��
		qint64 readDatagram(char *data,qint64 maxSize,QHostAddress *address=0,quint16 *port=0)
		*/
	}
}

void LittleClient::sendTcp()
{
	QString str=m_Label->text();
	//m_TcpSocket->write(str.toAscii());
	
	m_TcpSocket->write("12345",5);
	//m_TcpSocket->write(str.toStdString().c_str(), strlen(str.toStdString().c_str()));
	bool isSend=m_TcpSocket->waitForBytesWritten(); //��ʹ��waitForBytesWritten()��QTcpSocket�������������ݡ� 
}

void LittleClient::ConnectToServerSuccessed()
{
	
	m_Label->setText(QString("������:[%1:%2 �ͻ��ˣ�%3:%4]").arg(m_TcpSocket->peerAddress().toString()).arg(m_TcpSocket->peerPort()).arg(m_TcpSocket->localAddress().toString()).arg(m_TcpSocket->localPort()));

}
