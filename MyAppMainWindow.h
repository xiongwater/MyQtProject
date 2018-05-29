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
	MyApp* _app;//����
	//��������������Ŀؼ�
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
	 * @brief handleMouseMove ����ͻ�������ƶ��¼���֧�ֹ�������ʾ����
	 * @param p �ͻ����������
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
	//bool is_fullscreen();//�Ƿ�ȫ��
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
	 * @brief modify_user_pwd_result �޸��û����뷵�سɹ���ʶ
	 * @param success
	 */
//	void modify_user_pwd_result(bool success);
//
//	//void query_device_result(IOTP::ArrayNamedValue *pArValue);
//
//	/**
//	 * @brief setSysbarVisible ����ϵͳ�˵��Ƿ�ɼ�
//	 * @param visible
//	 */
//	void setSysbarVisible(bool visible);
//
//	/**
//	 * @brief setToolbarVisible ���ù������Ƿ�ɼ�
//	 * @param visible
//	 */
//	void setToolbarVisible(bool visible);
//public slots:
//	void slot_modify_pwd();//�޸�����
//	void slot_check_camera();//�������ͷ�����������
//
//	/**
//	 * @brief slot_query_device_resource ���²�ѯ��ش������Դ
//	 */
//	void slot_query_device_resource();	
protected:
//	//����������Ƿ���Ҫ��д����¼�
//	//void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);
//	//void keyPressEvent(QKeyEvent *event);
//	//void closeEvent(QCloseEvent *event);
//private:
//	void cancel_login();
//	void login(QString& username, QString& passwd, int post);
//
//	//���ڴ��ڵĵ�һ�β����ƶ�����Ļ����
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
//	void slot_show_hide_preferences();//��ʾ(����)ϵͳ���ô���
//	void slot_polledStatus(QString & polledStr);   //��Ѳ״̬�޸�
//	void slot_movePosition(QRect rectMove);   //���������ƶ�������ߴ�
private:
	//bool bHadFullScreen;//�Ƿ�����ȫ��ģʽ���������ڶ���ʱ ���ж��Ƿ���֮ǰλ����Ϣ�ı���
	//CountDownWidget* m_countDownWidget;
	//CountDownWidget* m_BigScreenCountDownWidget;
	//Ui::CentralWidget *ui;
	MyAppMainWindow *_mainw;
	MyApp *_app;
    MyAppLogin *_login;
	

	bool _full_screen;
	bool _bChangeState;
	QWidget* _current_system_wgt;
	QRect _normal_geometry;//��¼��С��
	bool _isMaxWindow;//�Ƿ����


public:
	PartContentsWidget* m_PartContentsWidget;
	QWidget* m_MainViewWidget;
	QWidget* m_SystemBar;
signals:
	
};