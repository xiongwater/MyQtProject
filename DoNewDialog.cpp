#include "DoNewDialog.h"
#include<QColorDialog>
#include<QDebug>
#include <QEvent>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
DoNewDialog::DoNewDialog(QWidget *parent) :
QDialog(parent),
	m_Combox(new QComboBox())
	
{
	
	//初始化
	setWindowTitle(tr("绘图工具"));
	backColor=Qt::white;
	DialogInit();
}

DoNewDialog::~DoNewDialog()
{
	
}


//定义
void DoNewDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch(e->type())
	{
	case QEvent::LanguageChange:
		//retranslateUi(this);
		break;
	default:
		break;
	}
}

int DoNewDialog::getWidth()
{
	return m_widthSpinBox->text().toInt();

}

int DoNewDialog::getHeight()
{
 return m_heightSpinBox->text().toInt();
}

QColor DoNewDialog::getBackColor()
{
	return backColor;
}





void DoNewDialog::on_toolButton_clicked()
{
	QColor newColor=QColorDialog::getColor();  //从颜色对话框获得颜色
	if(newColor.isValid())  //如果得到的是可用的颜色
	{
		backColor=newColor;

	QPalette palette=m_textBrowser->palette();  //显示这个颜色
	palette.setColor(QPalette::Base,backColor);
	m_textBrowser->setPalette(palette);
		update();
	}

}

void DoNewDialog::DialogInit()
{
	
	QVBoxLayout* m_MainLayout=new QVBoxLayout(this);
	this->setLayout(m_MainLayout);


	QHBoxLayout* widthSpinLayout=new QHBoxLayout();
	QLabel* widthLabel=new QLabel();
	widthLabel->setText(tr("画笔宽"));
	m_widthSpinBox=new QSpinBox();
	widthSpinLayout->addWidget(widthLabel);
	//widthSpinLayout->addStretch();
	widthSpinLayout->addWidget(m_widthSpinBox);

	QHBoxLayout* heightSpinLayout=new QHBoxLayout();
	QLabel* heightLabel=new QLabel();
	heightLabel->setText(tr("画笔高"));
	m_heightSpinBox=new QSpinBox();
	heightSpinLayout->addWidget(heightLabel);
	//heightSpinLayout->addStretch();
	heightSpinLayout->addWidget(m_heightSpinBox);

	m_textBrowser=new QTextBrowser();
	m_MainLayout->addWidget(m_textBrowser);
	m_MainLayout->addLayout(widthSpinLayout);
	m_MainLayout->addLayout(heightSpinLayout);
	creatColorComboBox(m_Combox);
	m_MainLayout->addWidget(m_Combox);
	QPushButton* btnChange=new  QPushButton(tr("选择颜色"));
	m_MainLayout->addWidget(btnChange);
	connect(btnChange,SIGNAL(clicked()),this,SLOT(on_toolButton_clicked()));


	QHBoxLayout* shapeLayout=new QHBoxLayout();
	QPushButton* None=new QPushButton(tr("常规"));
	QPushButton* Rectangle=new QPushButton(tr("四边形"));
	QPushButton* Ellipse=new QPushButton(tr("椭圆"));
	QPushButton* ERASE=new QPushButton(tr("橡皮"));
	shapeLayout->addWidget(None);
	shapeLayout->addWidget(Rectangle);
	shapeLayout->addWidget(Ellipse);
	shapeLayout->addWidget(ERASE);
	m_MainLayout->addLayout(shapeLayout);
	
	
}

void DoNewDialog::creatColorComboBox( QComboBox*comboBox )
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
