#include "PartContentsWidget.h"
#include <QPushButton>
#include <QImage>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QDesktopWidget>
#include <QPluginLoader>
#include "../LibirayTest/libiraytest.h"
#include "../LibirayTest/libiraytest_global.h"
#include <MyApp.h>
PartContentsWidget::PartContentsWidget(QWidget* parent)
	:QWidget(parent),
	m_PaintWnd(nullptr),
	m_CameraDialog(nullptr),
	m_VideoDialog(nullptr),
	m_WebView(nullptr),
	m_DeskShow(nullptr),
	m_DataBaseWindow(nullptr)
	
{
	m_HboxLayout=new QVBoxLayout(this);
	setLayout(m_HboxLayout);

}


PartContentsWidget::~PartContentsWidget(void)
{
	if(m_PaintWnd)
	{
		delete m_PaintWnd;
	}
	if(m_CameraDialog)
	{
		delete m_CameraDialog;
	}
	if(m_WebView)
	{
		delete m_WebView;
	}
	if(m_VideoDialog)
	{
		delete m_VideoDialog;
	}
	if(m_DeskShow)
	{
		delete m_DeskShow;
	}
	if(m_DataBaseWindow)
	{
		delete m_DataBaseWindow;
	}
}

void PartContentsWidget::addItem( QString name,QString imagePath )
{
	if(m_HboxLayout)
	{
		QPushButton* btn=new QPushButton(name);
		connect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
		if(name=="画家")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(openPainter()));
		}
		else if(name=="美拍")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(openCamera()));
		}
		else if(name=="轻松一刻")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(openVideo()));
		}
		else if(name=="浏览器")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(openWeb()));
		}
		else if(name=="桌面录制")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(openDeskRecording()));
		}
		else if(name=="FeiQ")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(openQqProcess()));
		}
		else if(name=="测试dll")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(DllTest()));
		}
		else if(name=="数据库测试")
		{
			disconnect(btn,SIGNAL(clicked()),this,SLOT(openFolder()));
			connect(btn,SIGNAL(clicked()),this,SLOT(DataBaseTest()));
		}
		QImage btnImage(imagePath);
		QString styleStr="border-image:url("+imagePath+")";
		btn->setStyleSheet(styleStr);
		//btn->setStyleSheet("background-color: rgb(170, 0, 255);");
		m_HboxLayout->addWidget(btn);
		
	}
}

void PartContentsWidget::openFolder()
{
	//QString strPath=QApplication::applicationFilePath();
	QString strPath=QApplication::applicationDirPath();
	QDesktopServices::openUrl(QUrl(QString("file:///%0").arg(strPath), QUrl::TolerantMode));
}

void PartContentsWidget::openCamera()
{
	if(!m_CameraDialog)
	{
		m_CameraDialog=new CameraDialog();
		m_CameraDialog->setWindowTitle("摄像头对话框");
		m_CameraDialog->resize(QApplication::desktop()->size()/2);
	}
	m_CameraDialog->show();
	m_CameraDialog->raise();
}

void PartContentsWidget::openPainter()
{
	if(!m_PaintWnd)
	{
		m_PaintWnd=new PainterWindow();
		m_PaintWnd->setWindowTitle("画板");
	}
	m_PaintWnd->show();
	m_PaintWnd->raise();
}

void PartContentsWidget::openVideo()
{
	if(!m_VideoDialog)
	{
		m_VideoDialog=new VideoDialog();
		m_VideoDialog->setWindowTitle("看大片");
		m_VideoDialog->resize(QApplication::desktop()->size()/2);
	}
	m_VideoDialog->show();
	m_VideoDialog->raise();
}

void PartContentsWidget::openWeb()
{
	
	if(!m_WebView)
	{
		m_WebView = new QWebView();
		m_WebView->setWindowTitle("主页");
	}
	m_WebView ->load(QUrl(MyApp::getInstance()->m_Config->value("ContentTest/TestWebUrl", "").toString())); 
	m_WebView->show();  
}

void PartContentsWidget::openDeskRecording()
{
	if(!m_DeskShow)
	{
		m_DeskShow=new DeskVideoWnd();
	}
	m_DeskShow->show();
	m_DeskShow->raise();


}

void PartContentsWidget::openQqProcess()
{
	//QProcess::startDetached("C:\\Users\\hewei\\Desktop\\FeiQ.exe");//必须是双斜杠
	m_ProcessFeiQiu.startDetached(MyApp::getInstance()->m_Config->value("ContentTest/TestProcessAddress", "").toString());
}

void PartContentsWidget::paintEvent( QPaintEvent * e )
{
	QStyleOption opt;

	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void PartContentsWidget::DllTest()
{
	
	//QString testDllPath="D:/code/MyProduction/Win32/Debug/LibirayTest.dll";//测试的dll路径
	QString testDllPath=QApplication::applicationDirPath()+"/LibirayTest.dll";
	testLib=new QLibrary(testDllPath,this);
	testLib->load();
	if(testLib->isLoaded())
	{
		 typedef void* (*GetPluginFunType)();

		// GetPluginFunType fun=(GetPluginFunType)testLib->resolve("CreatePluginInstance");
		 GetPluginFunType fun=(GetPluginFunType)testLib->resolve("CreatePluginInstance");
		 if(fun)
		 {
			 BasicPlugin* plugin=(BasicPlugin*)fun();
			 if(plugin)
			 {
				 QString name=plugin->GetPluginStrName();
				 m_plugins.insert(plugin->GetPluginStrName(),plugin);
			 }

		 }
		
	}

	QHash<QString, BasicPlugin*>::iterator i;
	for( i=m_plugins.begin(); i!=m_plugins.end(); ++i)
	{
		if(*i!=NULL)
		{
			//(*i)->show();
			(*i)->DoPluginFunction();
		}
	}




	//QPluginLoader loader(testDllPath);

	//bool b = loader.load();
	//if(b)
	//	qDebug("loder ok!\r\n");
	//else
	//	qDebug("loder error!\r\n");

	//QObject *plugin = loader.instance();
	//if (plugin)
	//{
	//	//LibirayTest* MyLibWidget = qobject_cast<LibirayTest *>(plugin);
	//	QLabel* MyLibWidget = qobject_cast<QLabel *>(plugin);
	//	
	//	if( MyLibWidget ){
	//		MyLibWidget->raise();
	//		MyLibWidget->show();
	//	}
	//}
	//else
	//	qDebug("loader.instance() error\r\n");

	return ;

}

void PartContentsWidget::DataBaseTest()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//QSqlDatabase db=QSqlDatabase::addDatabase("QODBC"); 
	//db.setDatabaseName(QString("DRIVER={SQL SERVER};" 
	//	"SERVER=%1;" //服务器名称 
	//	"DATABASE=%2;"//数据库名 
	//	"UID=%3;"           //登录名 
	//	"PWD=%4;"        //密码 
	//	).arg("192.168.20.156") //数据库地址
	//	.arg("dogkeep") //数据库名称
	//	.arg("sa") //登陆的用户名
	//	.arg("123456") //登陆的密码
	//	); 
	//if(!db.open()){  
	//	qDebug() << "数据库操作失败";return ;  
	//}  
	//QSqlQuery query;  
	//bool success = query.exec("select * from dbo.test2");  
	//if(!success){  
	//	qDebug() << "查询user失败";return ;  
	//} 
	//while (query.next()) {
	//	QSqlRecord rec = query.record(); 
	//	
	//	for(int i=0;i<rec.count();++i)
	//	{
	//		QString strResult = query.value(i).toString();//cmf_menu表第i个字段的内容
	//	}
	//
	//	
	//}
	if(!m_DataBaseWindow)
	{
		m_DataBaseWindow=new DataBaseView();
		m_DataBaseWindow->setWindowTitle("数据库示例");
		m_DataBaseWindow->resize(QApplication::desktop()->size()/2);
	}
	m_DataBaseWindow->show();
	m_DataBaseWindow->raise();
}
