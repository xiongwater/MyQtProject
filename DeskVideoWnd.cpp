#include "DeskVideoWnd.h"
#include <QMenuBar>
#include <QApplication>
DeskVideoWnd::DeskVideoWnd(void)
{
	m_Desk=QApplication::desktop();
	setWindowTitle("����¼��");
	m_CentralWidget=new QWidget(this);
	m_Label=new QLabel(this);
	m_Label->setText("ӫĻ");
	setCentralWidget(m_Label);
	//setCentralWidget(m_CentralWidget);
	isRecording=false;

	QMenuBar* m_MenuBar=this->menuBar();
	QAction* ActStart=m_MenuBar->addAction("��ʼ¼��");
	connect(ActStart, SIGNAL(triggered()), this,SLOT(startRecording()));

	QAction* ActStop=m_MenuBar->addAction("ֹͣ¼��");
	connect(ActStop, SIGNAL(triggered()), this,SLOT(stopRecording()));

	mTimer.setInterval(25);
	connect(&mTimer,SIGNAL(timeout()),this,SLOT(Recording()));


}


DeskVideoWnd::~DeskVideoWnd(void)
{
}

void DeskVideoWnd::startRecording()
{
	mTimer.start();
}

void DeskVideoWnd::stopRecording()
{
	mTimer.stop();
}

void DeskVideoWnd::Recording()
{
	
	mPix=QPixmap::grabWindow(m_Desk->winId());
	m_Label->setPixmap(mPix);
	


}
