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
	QTableView* m_CentralView;//��ʾ�������
	QSqlDatabase m_CurrentDataBase;//��ǰ���ӵ����ݿ�
	QSqlTableModel * model;//���ݿ���ģ��
	LittleServer* m_LittleServer;//���Է�����
	LittleClient* m_LittleClient;//���Կͻ���


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

