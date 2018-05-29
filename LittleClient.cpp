#include "LittleClient.h"
#include <MyApp.h>

LittleClient::LittleClient(void)
	:UdpReceiver(new QUdpSocket(this))
{

	UdpReceiver->bind(QHostAddress::LocalHost, 6665);//绑定端口
	connect(UdpReceiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
	m_CentralWidget=new QWidget(this);
	QHBoxLayout* mainLayout=new QHBoxLayout(this);
	m_ShowButton=new QPushButton("显示",this);
	m_Label=new QLabel("开始",this);

	mainLayout->addStretch();
	mainLayout->addWidget(m_ShowButton);
	mainLayout->addWidget(m_Label);
	mainLayout->addStretch();
	this->setCentralWidget(m_CentralWidget);
	m_CentralWidget->setLayout(mainLayout);
	


	m_TcpSocket=new QTcpSocket(this);
	//m_TcpSocket->abort();
	connect(m_TcpSocket,SIGNAL(connected()),this,SLOT(ConnectToServerSuccessed()));
	m_TcpSocket->connectToHost(QHostAddress::LocalHost,MyApp::getInstance()->m_Config->value("ContentTest/LittleServer_Port", "").toString().toInt());//链接服务器
	bool isConnected=m_TcpSocket->waitForConnected();//只有使用waitForConnected()后,QTcpSocket才真正尝试连接服务器，并返回是否连接的结果。
	//m_TcpSocket->connectToHost("192.168.20.156", 9999);//先建立链接
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
		//数据接收在datagram里
		/* readDatagram 函数原型
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
	bool isSend=m_TcpSocket->waitForBytesWritten(); //当使用waitForBytesWritten()后，QTcpSocket才真正发送数据。 
}

void LittleClient::ConnectToServerSuccessed()
{
	
	m_Label->setText(QString("服务器:[%1:%2 客户端：%3:%4]").arg(m_TcpSocket->peerAddress().toString()).arg(m_TcpSocket->peerPort()).arg(m_TcpSocket->localAddress().toString()).arg(m_TcpSocket->localPort()));

}
