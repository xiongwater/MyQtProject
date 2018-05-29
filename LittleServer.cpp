#include "LittleServer.h"

#include <QHBoxLayout>
#include <MyApp.h>
LittleServer::LittleServer(void)
{
	m_TcpServer=new QTcpServer(this);//创建服务器实例
	TcpReciever=nullptr;//暂无接收数据

	m_TcpServer->listen(QHostAddress::Any, MyApp::getInstance()->m_Config->value("ContentTest/LittleServer_Port", "").toString().toInt());//监听端口号为8888
	connect(m_TcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));//接受新的链接
	m_Label=new QLabel("",this);









	m_CentralWidget=new QWidget(this);
	QHBoxLayout* mainLayout=new QHBoxLayout(this);
	m_SendButton=new QPushButton("发送",this);
	m_LineEdit=new QLineEdit(this);
	mainLayout->addStretch();
	mainLayout->addWidget(m_SendButton);
    mainLayout->addWidget(m_LineEdit);
	mainLayout->addStretch();
	mainLayout->addWidget(m_Label);
	this->setCentralWidget(m_CentralWidget);
	m_CentralWidget->setLayout(mainLayout);
	UdpSender = new QUdpSocket(this);
	//

    connect(m_SendButton,SIGNAL(clicked()),this,SLOT(slot_Send()));

}


LittleServer::~LittleServer(void)
{
}

void LittleServer::slot_Send()
{
	datagram=m_LineEdit->text().toAscii();//得到数据
	//UDP广播
	UdpSender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,6665);

	//向特定IP发送
	//读取配置文件中的ip地址
 	QHostAddress serverAddress = QHostAddress(MyApp::getInstance()->m_Config->value("ContentTest/LittleServer_Url", "").toString());
	int Ret=UdpSender->writeDatagram(datagram.data(), datagram.size(),QHostAddress::LocalHost, 6665);

	/* writeDatagram函数原型，发送成功返回字节数，否则-1
	qint64 writeDatagram(const char *data,qint64 size,const QHostAddress &address,quint16 port)
	qint64 writeDatagram(const QByteArray &datagram,const QHostAddress &host,quint16 port)
	*/

}

void LittleServer::acceptConnection()
{
	//当有客户端连接到服务器的时候：就得到当前的socket，然后有数据就读取
	//qDebug(State:%d\n”,mSocket->state()); // State: 2; 2代表ConnectingState，正确的应该为3（ConnectedState）
	TcpReciever =m_TcpServer->nextPendingConnection();//接收新的链接
	
	
	connect(TcpReciever, SIGNAL(readyRead()), this, SLOT(readClient()));
	QString ipCli =TcpReciever->peerAddress().toString();//链接方地址
	qint16 portCli = TcpReciever->peerPort();//链接方端口
	QString temp = QString("客户端:[%1:%2]:连接成功").arg(ipCli).arg(portCli);
	ipCli=TcpReciever->localAddress().toString();
	portCli=TcpReciever->localPort();
	temp += QString("服务器:[%1:%2]").arg(ipCli).arg(portCli);
	m_Label->setText(temp);
}

void LittleServer::readClient()
{

	TcpReciever->waitForReadyRead();
	QString str = TcpReciever->readAll();

	m_Label->setText(str);
	//或者
	//char buf[1024];
	//m_TcpServer->read(buf,1024);
}
