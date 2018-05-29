#include "LittleServer.h"

#include <QHBoxLayout>
#include <MyApp.h>
LittleServer::LittleServer(void)
{
	m_TcpServer=new QTcpServer(this);//����������ʵ��
	TcpReciever=nullptr;//���޽�������

	m_TcpServer->listen(QHostAddress::Any, MyApp::getInstance()->m_Config->value("ContentTest/LittleServer_Port", "").toString().toInt());//�����˿ں�Ϊ8888
	connect(m_TcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));//�����µ�����
	m_Label=new QLabel("",this);









	m_CentralWidget=new QWidget(this);
	QHBoxLayout* mainLayout=new QHBoxLayout(this);
	m_SendButton=new QPushButton("����",this);
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
	datagram=m_LineEdit->text().toAscii();//�õ�����
	//UDP�㲥
	UdpSender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,6665);

	//���ض�IP����
	//��ȡ�����ļ��е�ip��ַ
 	QHostAddress serverAddress = QHostAddress(MyApp::getInstance()->m_Config->value("ContentTest/LittleServer_Url", "").toString());
	int Ret=UdpSender->writeDatagram(datagram.data(), datagram.size(),QHostAddress::LocalHost, 6665);

	/* writeDatagram����ԭ�ͣ����ͳɹ������ֽ���������-1
	qint64 writeDatagram(const char *data,qint64 size,const QHostAddress &address,quint16 port)
	qint64 writeDatagram(const QByteArray &datagram,const QHostAddress &host,quint16 port)
	*/

}

void LittleServer::acceptConnection()
{
	//���пͻ������ӵ���������ʱ�򣺾͵õ���ǰ��socket��Ȼ�������ݾͶ�ȡ
	//qDebug(State:%d\n��,mSocket->state()); // State: 2; 2����ConnectingState����ȷ��Ӧ��Ϊ3��ConnectedState��
	TcpReciever =m_TcpServer->nextPendingConnection();//�����µ�����
	
	
	connect(TcpReciever, SIGNAL(readyRead()), this, SLOT(readClient()));
	QString ipCli =TcpReciever->peerAddress().toString();//���ӷ���ַ
	qint16 portCli = TcpReciever->peerPort();//���ӷ��˿�
	QString temp = QString("�ͻ���:[%1:%2]:���ӳɹ�").arg(ipCli).arg(portCli);
	ipCli=TcpReciever->localAddress().toString();
	portCli=TcpReciever->localPort();
	temp += QString("������:[%1:%2]").arg(ipCli).arg(portCli);
	m_Label->setText(temp);
}

void LittleServer::readClient()
{

	TcpReciever->waitForReadyRead();
	QString str = TcpReciever->readAll();

	m_Label->setText(str);
	//����
	//char buf[1024];
	//m_TcpServer->read(buf,1024);
}
