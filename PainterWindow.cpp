#include "PainterWindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QLayout>
PainterWindow::PainterWindow(QWidget *parent)
{

    //setAttribute(Qt::WA_DeleteOnClose);//在没有指针指向的时候才应该使用该函数
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

	QMenu* Edit=m_MenuBar->addMenu(tr("&编辑"));
	QAction* toolAction=new QAction(QIcon(":/Resources/GongJu.png"), tr("&工具"), this);
	//openAction->setShortcuts(QKeySequence::);
	toolAction->setStatusTip(tr("打开画图工具"));
	connect(toolAction, SIGNAL(triggered()), this,SLOT(openToolDialog()));
	Edit->addAction(toolAction);

	QMenu* Open=m_MenuBar->addMenu(tr("&资源"));
	QAction* openAction=new QAction(QIcon(":/Resources/Myicon.png"), tr("&打开"), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("打开已保存图画"));
	connect(openAction, SIGNAL(triggered()), this,SLOT(hide()));
	Open->addAction(openAction);

	QMenu* Save=m_MenuBar->addMenu(tr("&保存"));
	QMenu* SaveAs=m_MenuBar->addMenu(tr("&另存"));
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
	QStringList m_colorlist = QColor::colorNames(); //获取Qt已知名称的颜色列表  
	QString m_color;  
	foreach (m_color, m_colorlist) 
	{ //遍历颜色列表  
		QPixmap pix(QSize(84,20)); //新建pix图标对象用于显示颜色  
		pix.fill(QColor(m_color)); //将当前遍历的颜色填充到pix  
		comboBox->addItem(QIcon(pix),m_color);  
		comboBox->setIconSize(QSize(84,20));  
		comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);  
		//设置下拉列表尺寸调整为“符合内容大小”  
	}
}
