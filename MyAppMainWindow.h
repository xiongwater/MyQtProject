#pragma once
#include "qmainwindow.h"
#include <QMouseEvent>
#include "MyAppLogin.h"
#include "PartContentsWidget.h"
#include <QSystemTrayIcon>
class MyApp;
class CentralWidget; 
class MyAppMainWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	MyAppMainWindow( MyApp* myApp, QWidget *parent = 0);
	virtual ~MyAppMainWindow(void);

public:
	MyApp* _app;//父类
	//主窗口里面的中心控件
	CentralWidget *       m_central_widget;
	QSystemTrayIcon* m_pTrayIcon;
	QAction* m_pAcExit;
public:
	void MainWindowStart();
	void initUi()
	{

	}
	
	void CreateTrayIcon( );
	
	
signals:
	void DisPlay(int);
public slots:
	void OnExitSys( );
	void LoginSuccessed();
	void OnTrayIconActivated(QSystemTrayIcon::ActivationReason eReason);
protected:
	
	void mouseMoveEvent(QMouseEvent *event);
	

};

class CentralWidget: public QWidget
{
	Q_OBJECT
	
	
public:
	CentralWidget(MyAppMainWindow *, MyApp *app);
	~CentralWidget();

	void initUi();
	void ReizeMembers();
	

	/**
	 * @brief handleMouseMove 处理客户端鼠标移动事件，支持工具栏显示隐藏
	 * @param p 客户端相对坐标
	 */
	void handleMouseMove(QPoint &p);

public:
	//void do_quit_system();
	//void set_login_window(MyAppLogin *);
	//void login_successed(QSet<QString> permittedPluginUuids, const char* pUserPhoto);
	//void logout_successed();
	//void show_homepage();
	//void enter_fullscreen(bool ensure = false);
	//bool exit_fullscreen();
	//bool is_fullscreen();//是否全屏
	//void toggle_full_screen(bool full_screen, bool cmd_by_plugin = false);
	//void toggle_sysbar();
	//void handle_error(int error_no, QString error_msg);
	////void handle_emer_request(IOTP::MapNamedValue *);
	////void handle_plan_request(QString eveType, IOTP::MapNamedValue *);
	////void handle_video_polling_request(IOTP::MapNamedValue *);
	////void append_post_info(IOTP::HUUID** pPoshUuid, QList<QString>* pPostName);
	//void request_user_logout();
	//void heartbeat_logout();
	//void to_loginwindow();
	//void active_system();
	/**
	 * @brief modify_user_pwd_result 修改用户密码返回成功标识
	 * @param success
	 */
//	void modify_user_pwd_result(bool success);
//
//	//void query_device_result(IOTP::ArrayNamedValue *pArValue);
//
//	/**
//	 * @brief setSysbarVisible 设置系统菜单是否可见
//	 * @param visible
//	 */
//	void setSysbarVisible(bool visible);
//
//	/**
//	 * @brief setToolbarVisible 设置工具栏是否可见
//	 * @param visible
//	 */
//	void setToolbarVisible(bool visible);
//public slots:
//	void slot_modify_pwd();//修改密码
//	void slot_check_camera();//检查摄像头网络连接情况
//
//	/**
//	 * @brief slot_query_device_resource 重新查询相关待检测资源
//	 */
//	void slot_query_device_resource();	
protected:
//	//依据情况看是否需要重写相关事件
//	//void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);
//	//void keyPressEvent(QKeyEvent *event);
//	//void closeEvent(QCloseEvent *event);
//private:
//	void cancel_login();
//	void login(QString& username, QString& passwd, int post);
//
//	//用于窗口的第一次布局移动到屏幕中央
//	void moveChildWidgetToCenter(QWidget* win);
//	
//
//	
//	QPoint getWndMovePos();
//
//	
//	//void createButteryWeb(QString strUrl, QSize sizeWeb);
//
//	//void createDispatchView();
//
//	/*void popWidgetControl(IOTP::MapNamedValue* mapValue);
//
//	void popCreateWidget(IOTP::MapNamedValue* mapValue);
//
//	void popDeleteWidget(IOTP::MapNamedValue* mapValue);
//
//	void popMoveWidget(IOTP::MapNamedValue* mapValue);
//	QtClientPlugin *ensureThirdpartPlugin(const QString &pluginType);*/
//
//	void setWidgetAttribute(int wndType, QWidget* widget);
//	private slots:
//	
//	void slot_check_update();
//	void slot_load_user_photo(QByteArray*);
//	void slot_dlg_show_hide(bool);
//	void slot_plugin_link(IOTP::HUUID*, void*);
//	void slot_alarmSimulator_show_hide();
//	void slot_show_hide_preferences();//显示(隐藏)系统设置窗口
//	void slot_polledStatus(QString & polledStr);   //轮巡状态修改
//	void slot_movePosition(QRect rectMove);   //上屏窗口移动坐标与尺寸
private:
	//bool bHadFullScreen;//是否进入过全屏模式，这里用于多屏时 候判断是否有之前位置信息的保存
	//CountDownWidget* m_countDownWidget;
	//CountDownWidget* m_BigScreenCountDownWidget;
	//Ui::CentralWidget *ui;
	MyAppMainWindow *_mainw;
	MyApp *_app;
    MyAppLogin *_login;
	

	bool _full_screen;
	bool _bChangeState;
	QWidget* _current_system_wgt;
	QRect _normal_geometry;//记录大小用
	bool _isMaxWindow;//是否最大化


public:
	PartContentsWidget* m_PartContentsWidget;
	QWidget* m_MainViewWidget;
	QWidget* m_SystemBar;
signals:
	
};