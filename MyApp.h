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
		UPDATING,       //程序更新中
		UPDATED,        //程序更新完成
		LOADING,        //加载中
		STARTING,       //启动中
		OPERATING,      //执行中
		LOGGING_OUT,    //登出
		QUITING,        //退出
	};


public:
	QStackedLayout* m_StackedLayout;
	//主窗口
	MyAppMainWindow* m_MainWnd;
	//登陆界面
	MyAppLogin* m_Login;
	//程序启动画面类
	QSplashScreen* m_AppSplash;
	//主窗口里面的中心控件
	CentralWidget *       m_central_widget;
	//////////////////////////////////////////
	char* _application_dir;//当前应用程序的目录
	QTimer* m_pTimer_check_update;
	std::string _local_ip;   //本地IPv4地址
	QReadWriteLock          _lock;//读写锁

	static QFile *          m_pFileLog;//file for log 
	bool     m_isAppStateChanged;
	MyAppState m_AppState;


	QString _plugins_dir;
	QByteArray  _msgsvr_url;
	QByteArray  _msgsvr_username;
	QByteArray  _msgsvr_passwd;
	QByteArray  _client_addr;     
	QByteArray  _last_login_name;//上次登陆名
	QByteArray  _last_login_pwd;//上次登陆密码
	QByteArray  _user_name;//用户名
	QTimer*      checkStateTimer;
	QByteArray  m_FirstAnswer;//读取配置文件测试用例
	QByteArray  m_SecondAnswer;//读取配置文件测试用例
	QByteArray  m_LastLoginAnswer;//读取配置文件测试用例
public:
	void achieveLocalIp();//获取本地IPv4地址
	bool StartApp();
	void CreateLogFile();
	bool read_config();
	void load_local_libraries(QString app_dir);
	bool MyApp::loadLibrary(QString file_path, QString *error_msg);
	static void messageHandle(QtMsgType type, const char *msg);
	bool notify(QObject *obj, QEvent *e);//重写事件通知
	QSettings* m_Config;
};

#endif // MYPRODUCTION_H
