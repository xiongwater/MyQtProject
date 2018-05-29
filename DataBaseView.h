#pragma once
#include "QMainWindow"
#include <QTableView>
#include <QMenu>
#include <QMenuBar>
#include <QSqlTableModel>
#include <QHeaderView>
#include "LittleServer.h"
#include <LittleClient.h>

class DataBaseView :
	public QMainWindow
{
	Q_OBJECT
public:
	DataBaseView(void);
	virtual ~DataBaseView(void);
	QTableView* m_CentralView;//显示表格区域
	QSqlDatabase m_CurrentDataBase;//当前链接的数据库
	QSqlTableModel * model;//数据库表格模型
	LittleServer* m_LittleServer;//测试服务器
	LittleClient* m_LittleClient;//测试客户端


	void InitDataBaseView();

	bool isConnectDB();
	bool isConnecting;
	public slots:
		void ShowDataBase();
		void OpenLittleServer()
		{
			if(m_LittleServer->isHidden())
			{
				m_LittleServer->show();
			}
			else
			{
				m_LittleServer->hide();
			}
		}
		void OpenLittleClient()
		{
			if(m_LittleClient->isHidden())
			{
				m_LittleClient->show();
			}
			else
			{
				m_LittleClient->hide();
			}
		}
};

