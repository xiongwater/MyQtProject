#include "MyAppMainWindow.h"
#include <QLocale>
#include <QTime>
#include <QApplication>
#include <QDesktopWidget>
#include <QEvent>
MyAppMainWindow::MyAppMainWindow( MyApp* myApp, QWidget *parent)
	: QMainWindow(parent)
	, _app(myApp)
	,m_central_widget(new CentralWidget(this,myApp))
	
{
	
	setWindowIcon(QIcon(":/Resources/Myicon.png"));
    QString aaa=this->windowTitle();
	//setIcon(QIcon("Myicon.png"));
	//QString aaaa=QApplication::applicationFilePath();
	//m_central_widget->setMouseTracking(true);
	setCentralWidget(m_central_widget);
	CreateTrayIcon();
	//setMouseTracking(true);
	//setAttribute( Qt::WA_Hover,true);
}

MyAppMainWindow::~MyAppMainWindow(void)
{
}

void MyAppMainWindow::LoginSuccessed()
{
	MainWindowStart();
}

void MyAppMainWindow::MainWindowStart()
{
	setLocale(QLocale(QLocale::Chinese, QLocale::China));
	setWindowTitle(tr("MyAppMainWindow"));
	setObjectName("MAINWINDOW");
	setStyleSheet("#MAINWINDOW{border-image:url(:/Resources/111.png)}");	
	resize(QApplication::desktop()->size()/2);
	show();

}

void MyAppMainWindow::mouseMoveEvent( QMouseEvent *event )
{
	QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
	if(mouseEvent->type() == QEvent::MouseMove)
	{
		QPoint globalPos =mouseEvent->globalPos();
		QPoint relPos =m_central_widget->mapFromGlobal(globalPos);
		m_central_widget->handleMouseMove(relPos);

	}

	QWidget::mouseMoveEvent(event);
}

void MyAppMainWindow::OnExitSys()
{
	m_pTrayIcon->hide( );
	this->close( );
}

void MyAppMainWindow::CreateTrayIcon()
{
	m_pTrayIcon = new QSystemTrayIcon(QIcon(":/Resources/GoodLuck.png"), this);
	m_pTrayIcon->setToolTip(tr("XH_TEST"));

	m_pAcExit = new QAction(QIcon(":/Resources/exit.png"), tr("退出"), this);
	connect(m_pAcExit, SIGNAL(triggered( )), this, SLOT(OnExitSys( )));

	//添加单/双击鼠标相应
	connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(OnTrayIconActivated(QSystemTrayIcon::ActivationReason)));

	QMenu * _pMenu = new QMenu(this);
	_pMenu->addAction(m_pAcExit);
	m_pTrayIcon->setContextMenu(_pMenu);
	m_pTrayIcon->show( );
}

void MyAppMainWindow::OnTrayIconActivated( QSystemTrayIcon::ActivationReason eReason )
{
	switch (eReason)
	{
		//单击托盘图标
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		//this->showNormal( );
		//this->raise( );
		//气泡提示
		m_pTrayIcon->showMessage(tr("哈哈"), tr("示例Demo"), QSystemTrayIcon::Information, 2000);
		break;
	default:
		break;
	}
}



CentralWidget::CentralWidget(MyAppMainWindow *mainw, MyApp *app)
	: QWidget(mainw)//setmousetracking只对widget有效
	, _mainw(mainw)
	, _app(app)
	, _login(NULL)
	, _bChangeState(false)
	
{
	this->setFocusPolicy(Qt::StrongFocus);//聚焦策略
	this->_current_system_wgt = NULL;
	this->_full_screen = false;
	m_MainViewWidget=new QWidget(this);
	m_PartContentsWidget=new PartContentsWidget(this);

	m_PartContentsWidget->addItem("浏览器",":/Resources/BtnBaidu.png");
	m_PartContentsWidget->addItem("调试文件",":/Resources/BtnFile.png");
	m_PartContentsWidget->addItem("轻松一刻",":/Resources/BtnMovie.png");
	m_PartContentsWidget->addItem("美拍",":/Resources/BtnCamera.png");
	m_PartContentsWidget->addItem("画家",":/Resources/GongJu.png");
	m_PartContentsWidget->addItem("桌面录制",":/Resources/BtnDesk.png");
	m_PartContentsWidget->addItem("FeiQ",":/Resources/BtnFeiQ.png");
	m_PartContentsWidget->addItem("测试dll",":/Resources/111.png");
	m_PartContentsWidget->addItem("数据库测试",":/Resources/111.png");
	m_SystemBar=new QWidget(this);
	initUi();
}

void CentralWidget::initUi()
{


	QRect WidgetRect=_mainw->rect();
	int w=WidgetRect.width();
	int h=WidgetRect.height();
	
	//m_PartContentsWidget->setStyleSheet("border-image:url(:/Resources/444.png)");
	m_PartContentsWidget->setStyleSheet("border-image:url(:/Resources/partContent.png)");	
	m_PartContentsWidget->setGeometry(QRect(WidgetRect.x(),WidgetRect.y(),w/3,h));
	//m_PartContentsWidget->raise();

	m_MainViewWidget->setStyleSheet("border-image:url(:/Resources/222.png)");	
	m_MainViewWidget->setGeometry(WidgetRect);

	m_SystemBar->setStyleSheet("border-image:url(:/Resources/444.png)");	
	m_SystemBar->setGeometry(QRect(WidgetRect.x()+w/3,WidgetRect.y()+h*5/6,w/3*2,h/6));  
}


CentralWidget::~CentralWidget()
{

}

void CentralWidget::resizeEvent( QResizeEvent *event )
{
	QWidget::resizeEvent(event);
	ReizeMembers();
}

void CentralWidget::ReizeMembers()
{
	QRect WidgetRect=_mainw->rect();
	int w=WidgetRect.width();
	int h=WidgetRect.height();
	m_PartContentsWidget->setGeometry(QRect(WidgetRect.x(),WidgetRect.y(),w/3,h));
	m_MainViewWidget->setGeometry(WidgetRect);
	m_SystemBar->setGeometry(QRect(WidgetRect.x()+w/3,WidgetRect.y()+h*5/6,w/3*2,h/6));
}


void CentralWidget::handleMouseMove(QPoint &p)
{
	

	int wScreen = width();
	int hScreen = height();
	int SysBarWidth = wScreen / 6 * 3;
	int SysBarHeight = m_SystemBar->height();
	QRect toolRect = QRect((wScreen - SysBarWidth) / 2,hScreen-SysBarHeight,SysBarWidth, SysBarHeight);
	QRect toolControlRect = toolRect;
	//toolControlRect.setHeight(3);
	if(toolControlRect.contains(p))
	{
		if(toolRect.bottomLeft().y()- p.y()<10)
		{
			if(m_SystemBar->isHidden())
			{
				m_SystemBar->setGeometry(toolRect);
				m_SystemBar->show();
				m_SystemBar->raise();
				
			}
		}
		
	}
	else if(!toolRect.contains(p))
	{
		if(!m_SystemBar->isHidden())
		{
			m_SystemBar->hide();
		}
	}



	int webWidgetWidth=wScreen/6;
	int webWidgetHeight=hScreen;

	QRect webWidgetRect = QRect(this->pos().x(),this->pos().y(), webWidgetWidth, webWidgetHeight);

	if(webWidgetRect.contains(p))
	{
		if(p.x()< webWidgetRect.x()+10 )
		{
			if(m_PartContentsWidget->isHidden())
			{

				m_PartContentsWidget->setGeometry(webWidgetRect);
				m_PartContentsWidget->show();
				m_PartContentsWidget->raise();

			}
		}

	}
	else if(!webWidgetRect.contains(p))
	{
		if(!m_PartContentsWidget->isHidden())
		{
			m_PartContentsWidget->hide();
		}
	}

}

//void CentralWidget::mouseMoveEvent( QMouseEvent *event )
//{
//
//	QPoint globalPos =event->globalPos();
//	QPoint relPos = mapFromGlobal(globalPos);
//	handleMouseMove(relPos);
//	QWidget::mouseMoveEvent(event);
//}
