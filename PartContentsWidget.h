#pragma once
#include "qwidget.h"
#include <QVBoxLayout>
#include <QWebView>
#include "PainterWindow.h"
#include "CameraDialog.h"
#include "VideoDialog.h"
#include "DeskVideoWnd.h"
#include <QProcess>
#include <QLibrary>
#include <commonapi.h>
#include <DataBaseView.h>

class PartContentsWidget :
	public QWidget
{
	Q_OBJECT
private:
	DataBaseView* m_DataBaseWindow;//数据库示例窗口
	QProcess m_ProcessFeiQiu;//执行附加程序
	DeskVideoWnd* m_DeskShow;//显示桌面录制
	QWebView* m_WebView;//web浏览
	PainterWindow* m_PaintWnd;//画画用的
    CameraDialog* m_CameraDialog;//照相对话
	VideoDialog* m_VideoDialog;//播放电影
	QLibrary* testLib;//插件测试
	QHash<QString,BasicPlugin*> m_plugins;//插件管理器
public:
	PartContentsWidget(QWidget* parent=nullptr);
	virtual ~PartContentsWidget(void);
	void addItem(QString name,QString imagePath);
public:
	QVBoxLayout* m_HboxLayout;
	public slots:
		void openFolder();//打开文件夹测试
		void openCamera();//打开摄像头测试
		void openPainter();//打开画板测试
		void openVideo();//打开播放器测试
		void openWeb();//打开网页测试
		void openDeskRecording();//打开桌面录制测试
		void openQqProcess();//打开其他进程测试
		void DllTest();//动态调用dll测试
		//数据库测试
		void DataBaseTest();

protected:
	void paintEvent(QPaintEvent * e);
		
};

