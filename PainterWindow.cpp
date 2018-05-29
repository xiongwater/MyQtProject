#include "PainterWindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QLayout>
PainterWindow::PainterWindow(QWidget *parent)
{

    //setAttribute(Qt::WA_DeleteOnClose);//��û��ָ��ָ���ʱ���Ӧ��ʹ�øú���
	this->setParent(parent);
	area=new PaintWidget();
	this->setCentralWidget(area);
	toolDialog=new DoNewDialog(this);
	//m_ColorCombox=new QComboBox();
	//toolDialog->layout()->addWidget(m_ColorCombox);
	InitWindow();
	
}


PainterWindow::~PainterWindow(void)
{
	if(area)
	{
		delete area;
	}
}

void PainterWindow::InitWindow()
{

	//creatColorComboBox(m_ColorCombox);

	resize(QApplication::desktop()->size()/2);
	QMenuBar* m_MenuBar=this->menuBar();

	QMenu* Edit=m_MenuBar->addMenu(tr("&�༭"));
	QAction* toolAction=new QAction(QIcon(":/Resources/GongJu.png"), tr("&����"), this);
	//openAction->setShortcuts(QKeySequence::);
	toolAction->setStatusTip(tr("�򿪻�ͼ����"));
	connect(toolAction, SIGNAL(triggered()), this,SLOT(openToolDialog()));
	Edit->addAction(toolAction);

	QMenu* Open=m_MenuBar->addMenu(tr("&��Դ"));
	QAction* openAction=new QAction(QIcon(":/Resources/Myicon.png"), tr("&��"), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("���ѱ���ͼ��"));
	connect(openAction, SIGNAL(triggered()), this,SLOT(hide()));
	Open->addAction(openAction);

	QMenu* Save=m_MenuBar->addMenu(tr("&����"));
	QMenu* SaveAs=m_MenuBar->addMenu(tr("&���"));
}

void PainterWindow::openToolDialog()
{
	if(toolDialog->isHidden())
	{
		toolDialog->show();
		toolDialog->raise();
	//	m_ColorCombox->show();
	//	m_ColorCombox->raise();
	}
}

void PainterWindow::creatColorComboBox( QComboBox*comboBox )
{
	QStringList m_colorlist = QColor::colorNames(); //��ȡQt��֪���Ƶ���ɫ�б�  
	QString m_color;  
	foreach (m_color, m_colorlist) 
	{ //������ɫ�б�  
		QPixmap pix(QSize(84,20)); //�½�pixͼ�����������ʾ��ɫ  
		pix.fill(QColor(m_color)); //����ǰ��������ɫ��䵽pix  
		comboBox->addItem(QIcon(pix),m_color);  
		comboBox->setIconSize(QSize(84,20));  
		comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);  
		//���������б�ߴ����Ϊ���������ݴ�С��  
	}
}
