#include "DataBaseView.h"
#include <QDebug>
#include <MyApp.h>
DataBaseView::DataBaseView(void)
{
	InitDataBaseView();
}


DataBaseView::~DataBaseView(void)
{
	delete m_LittleServer;
	delete m_LittleClient;
}

void DataBaseView::InitDataBaseView()
{

	m_LittleServer=new LittleServer();
	m_LittleClient=new LittleClient();
	m_LittleServer->resize(this->size()/2);
	m_LittleServer->setWindowTitle(tr("С������"));
	m_LittleServer->show();
	m_LittleClient->resize(this->size()/2);
	m_LittleClient->setWindowTitle(tr("С�ͻ���"));
	m_LittleClient->show();


	isConnecting=false;
	QMenuBar* m_MenuBar=this->menuBar();

	QMenu* MenuShow=m_MenuBar->addMenu(tr("&�鿴���ݿ�"));
	QAction* DataBaseAction=new QAction(QIcon(":/Resources/GongJu.png"), tr("&��ʾ�������"), this);
	DataBaseAction->setStatusTip(tr("����鿴���ݿ�����"));
	connect(DataBaseAction, SIGNAL(triggered()), this,SLOT(ShowDataBase()));
	MenuShow->addAction(DataBaseAction);
	////////////////////////////////////////////////////////////////////////////////////
	QMenu* MenuNetServer=m_MenuBar->addMenu(tr("&С������"));
	QAction* NetServerAct=new QAction(QIcon(":/Resources/GongJu.png"),tr("&�򿪷�����"),this);
	NetServerAct->setStatusTip(tr("��ʾ��������"));
	connect(NetServerAct, SIGNAL(triggered()), this,SLOT(OpenLittleServer()));
	MenuNetServer->addAction(NetServerAct);
	QMenu* MenuNetClient=m_MenuBar->addMenu(tr("&С�ͻ���"));
	QAction* NetClientAct=new QAction(QIcon(":/Resources/GongJu.png"),tr("&�򿪿ͻ���"),this);
	NetServerAct->setStatusTip(tr("��ʾ���ͻ���"));
	connect(NetClientAct, SIGNAL(triggered()), this,SLOT(OpenLittleClient()));
	MenuNetClient->addAction(NetClientAct);
	m_CentralView=new QTableView(this);
	  model=nullptr;//Qt�ĵ�ָ�����ñ�ģ���޷������ݿ��֮ǰ������Ч��Ӧ���ڴ�֮����
	//model=new QSqlTableModel;
	this->setCentralWidget(m_CentralView);
}

void DataBaseView::ShowDataBase()
{
	if(isConnectDB())
	{
		if(!model)
		{
			model = new QSqlTableModel;
		}
		model->setTable(MyApp::getInstance()->m_Config->value("ContentTest/DataBaseTableName", "").toString());//ѡ�����ݿ�����ı��
		model->setSort(2, Qt::AscendingOrder);//�Ե�3�е�����������
		//model->setHeaderData(1, Qt::Horizontal, "Name");
		//model->setHeaderData(2, Qt::Horizontal, "Age");
		//ִ�в�ѯ��䣬�����ѯ�ɹ�����true
		if(model->select())
		{
			m_CentralView->setModel(model);
			m_CentralView->setSelectionMode(QAbstractItemView::SingleSelection);//����ѡ��
			m_CentralView->setSelectionBehavior(QAbstractItemView::SelectRows);//�е���ʽ
			//        view->setColumnHidden(0, true);
			m_CentralView->resizeColumnsToContents();//�Զ�������
			m_CentralView->setEditTriggers(QAbstractItemView::NoEditTriggers);

			QHeaderView *header = m_CentralView->horizontalHeader();
			header->setStretchLastSection(true);
			//m_CentralView->show();
		}



		
	}
}

bool DataBaseView::isConnectDB()
{

	if(isConnecting)
	{
		return true;
	}
	m_CurrentDataBase=QSqlDatabase::addDatabase("QODBC"); //�������õ���Microsoft SQL Server
	//QSqlDatabase db=QSqlDatabase::addDatabase("QODBC"); 
	/* QDB2	IBM DB2 (7.1 ����°汾)
	QIBASE	Borland InterBase
	QMYSQL	MySQL
	QOCI	Oracle Call Interface Driver
	QODBC	Open Database Connectivity (ODBC) �C Microsoft SQL Server ���������� ODBC �����ݿ�
	QPSQL	PostgreSQL (7.3 ����°汾)
	QSQLITE2	SQLite 2
	QSQLITE	SQLite 3
	QSYMSQL	��� Symbian ƽ̨��SQLite 3
	QTDS	Sybase Adaptive Server (�� Qt 4.7 ��ϳ�)*/

    QSettings*   cfg=MyApp::getInstance()->m_Config;
	m_CurrentDataBase.setDatabaseName(QString("DRIVER={SQL SERVER};" 
		"SERVER=%1;" //���������� 
		"DATABASE=%2;"//���ݿ��� 
		"UID=%3;"           //��¼�� 
		"PWD=%4;"           //���� 
		).arg(cfg->value("ContentTest/DataBaseAddress", "").toString()) //���ݿ��ַ
		.arg(cfg->value("ContentTest/DataBaseName", "").toString()) //���ݿ�����
		.arg(cfg->value("ContentTest/DataBaseUser", "").toString()) //��½���û���
		.arg(cfg->value("ContentTest/DataBasePassword", "").toString()) //��½������
		); 
	if(!m_CurrentDataBase.open())
	{  
		qDebug() << "���ݿ����ʧ��";return false;  
	}
	else
	{
		isConnecting=true;
		return true;
	}
}
