#ifndef MYPRODUCTION_H
#define MYPRODUCTION_H

#include <QtGui/QMainWindow>
#include "ui_myproduction.h"
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QLocale>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcess>
#include <QSettings>
#include <QTextStream>
#include <QTimer>
#include <QRegExp>
#include <QMainWindow>
#include <QMutex>
#include <QFrame>
#include <QShowEvent>
#include <QResizeEvent>
#include <QList>
#include <QQueue>
#include <QTimer>
#include <QReadWriteLock>
#include <QStackedLayout>
#include <QSplashScreen>
#include "MyAppMainWindow.h"
#include "MyAppLogin.h"
//class MyAppMainWindow;


#define AppConfig "MyAppConfig.ini"
#define AppLog "MyAppLog.log"
#define PLUGIN_DIR  "MyPlugins"

class MyApp :  public QApplication
{
	Q_OBJECT

public:
	static MyApp *getInstance()
	{
		return qobject_cast<MyApp *>(qApp);
	}
public:
	MyApp(int& argc, char **argv, int = ApplicationFlags);
	~MyApp();

private:
	Ui::MyProductionClass ui;
public:
	enum MyAppState
	{
		CREATED = 0,    //starting state.
		UPDATING,       //���������
		UPDATED,        //����������
		LOADING,        //������
		STARTING,       //������
		OPERATING,      //ִ����
		LOGGING_OUT,    //�ǳ�
		QUITING,        //�˳�
	};


public:
	QStackedLayout* m_StackedLayout;
	//������
	MyAppMainWindow* m_MainWnd;
	//��½����
	MyAppLogin* m_Login;
	//��������������
	QSplashScreen* m_AppSplash;
	//��������������Ŀؼ�
	CentralWidget *       m_central_widget;
	//////////////////////////////////////////
	char* _application_dir;//��ǰӦ�ó����Ŀ¼
	QTimer* m_pTimer_check_update;
	std::string _local_ip;   //����IPv4��ַ
	QReadWriteLock          _lock;//��д��

	static QFile *          m_pFileLog;//file for log 
	bool     m_isAppStateChanged;
	MyAppState m_AppState;


	QString _plugins_dir;
	QByteArray  _msgsvr_url;
	QByteArray  _msgsvr_username;
	QByteArray  _msgsvr_passwd;
	QByteArray  _client_addr;     
	QByteArray  _last_login_name;//�ϴε�½��
	QByteArray  _last_login_pwd;//�ϴε�½����
	QByteArray  _user_name;//�û���
	QTimer*      checkStateTimer;
	QByteArray  m_FirstAnswer;//��ȡ�����ļ���������
	QByteArray  m_SecondAnswer;//��ȡ�����ļ���������
	QByteArray  m_LastLoginAnswer;//��ȡ�����ļ���������
public:
	void achieveLocalIp();//��ȡ����IPv4��ַ
	bool StartApp();
	void CreateLogFile();
	bool read_config();
	void load_local_libraries(QString app_dir);
	bool MyApp::loadLibrary(QString file_path, QString *error_msg);
	static void messageHandle(QtMsgType type, const char *msg);
	bool notify(QObject *obj, QEvent *e);//��д�¼�֪ͨ
	QSettings* m_Config;
};

#endif // MYPRODUCTION_H
