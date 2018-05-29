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
	m_LittleServer->setWindowTitle(tr("小服务器"));
	m_LittleServer->show();
	m_LittleClient->resize(this->size()/2);
	m_LittleClient->setWindowTitle(tr("小客户端"));
	m_LittleClient->show();


	isConnecting=false;
	QMenuBar* m_MenuBar=this->menuBar();

	QMenu* MenuShow=m_MenuBar->addMenu(tr("&查看数据库"));
	QAction* DataBaseAction=new QAction(QIcon(":/Resources/GongJu.png"), tr("&显示表格内容"), this);
	DataBaseAction->setStatusTip(tr("点击查看数据库内容"));
	connect(DataBaseAction, SIGNAL(triggered()), this,SLOT(ShowDataBase()));
	MenuShow->addAction(DataBaseAction);
	////////////////////////////////////////////////////////////////////////////////////
	QMenu* MenuNetServer=m_MenuBar->addMenu(tr("&小服务器"));
	QAction* NetServerAct=new QAction(QIcon(":/Resources/GongJu.png"),tr("&打开服务器"),this);
	NetServerAct->setStatusTip(tr("打开示例服务器"));
	connect(NetServerAct, SIGNAL(triggered()), this,SLOT(OpenLittleServer()));
	MenuNetServer->addAction(NetServerAct);
	QMenu* MenuNetClient=m_MenuBar->addMenu(tr("&小客户端"));
	QAction* NetClientAct=new QAction(QIcon(":/Resources/GongJu.png"),tr("&打开客户端"),this);
	NetServerAct->setStatusTip(tr("打开示例客户端"));
	connect(NetClientAct, SIGNAL(triggered()), this,SLOT(OpenLittleClient()));
	MenuNetClient->addAction(NetClientAct);
	m_CentralView=new QTableView(this);
	  model=nullptr;//Qt文档指出，该表模型无法在数据库打开之前定义有效，应该在打开之后定义
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
		model->setTable(MyApp::getInstance()->m_Config->value("ContentTest/DataBaseTableName", "").toString());//选择数据库里面的表格
		model->setSort(2, Qt::AscendingOrder);//以第3列的数升序排序
		//model->setHeaderData(1, Qt::Horizontal, "Name");
		//model->setHeaderData(2, Qt::Horizontal, "Age");
		//执行查询语句，如果查询成功返回true
		if(model->select())
		{
			m_CentralView->setModel(model);
			m_CentralView->setSelectionMode(QAbstractItemView::SingleSelection);//单排选择
			m_CentralView->setSelectionBehavior(QAbstractItemView::SelectRows);//行的形式
			//        view->setColumnHidden(0, true);
			m_CentralView->resizeColumnsToContents();//自动调整列
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
	m_CurrentDataBase=QSqlDatabase::addDatabase("QODBC"); //我这里用的是Microsoft SQL Server
	//QSqlDatabase db=QSqlDatabase::addDatabase("QODBC"); 
	/* QDB2	IBM DB2 (7.1 或更新版本)
	QIBASE	Borland InterBase
	QMYSQL	MySQL
	QOCI	Oracle Call Interface Driver
	QODBC	Open Database Connectivity (ODBC) – Microsoft SQL Server 及其它兼容 ODBC 的数据库
	QPSQL	PostgreSQL (7.3 或更新版本)
	QSQLITE2	SQLite 2
	QSQLITE	SQLite 3
	QSYMSQL	针对 Symbian 平台的SQLite 3
	QTDS	Sybase Adaptive Server (自 Qt 4.7 起废除)*/

    QSettings*   cfg=MyApp::getInstance()->m_Config;
	m_CurrentDataBase.setDatabaseName(QString("DRIVER={SQL SERVER};" 
		"SERVER=%1;" //服务器名称 
		"DATABASE=%2;"//数据库名 
		"UID=%3;"           //登录名 
		"PWD=%4;"           //密码 
		).arg(cfg->value("ContentTest/DataBaseAddress", "").toString()) //数据库地址
		.arg(cfg->value("ContentTest/DataBaseName", "").toString()) //数据库名称
		.arg(cfg->value("ContentTest/DataBaseUser", "").toString()) //登陆的用户名
		.arg(cfg->value("ContentTest/DataBasePassword", "").toString()) //登陆的密码
		); 
	if(!m_CurrentDataBase.open())
	{  
		qDebug() << "数据库操作失败";return false;  
	}
	else
	{
		isConnecting=true;
		return true;
	}
}
