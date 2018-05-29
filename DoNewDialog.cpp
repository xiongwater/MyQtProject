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
	
	//��ʼ��
	setWindowTitle(tr("��ͼ����"));
	backColor=Qt::white;
	DialogInit();
}

DoNewDialog::~DoNewDialog()
{
	
}


//����
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
	QColor newColor=QColorDialog::getColor();  //����ɫ�Ի�������ɫ
	if(newColor.isValid())  //����õ����ǿ��õ���ɫ
	{
		backColor=newColor;

	QPalette palette=m_textBrowser->palette();  //��ʾ�����ɫ
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
	widthLabel->setText(tr("���ʿ�"));
	m_widthSpinBox=new QSpinBox();
	widthSpinLayout->addWidget(widthLabel);
	//widthSpinLayout->addStretch();
	widthSpinLayout->addWidget(m_widthSpinBox);

	QHBoxLayout* heightSpinLayout=new QHBoxLayout();
	QLabel* heightLabel=new QLabel();
	heightLabel->setText(tr("���ʸ�"));
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
	QPushButton* btnChange=new  QPushButton(tr("ѡ����ɫ"));
	m_MainLayout->addWidget(btnChange);
	connect(btnChange,SIGNAL(clicked()),this,SLOT(on_toolButton_clicked()));


	QHBoxLayout* shapeLayout=new QHBoxLayout();
	QPushButton* None=new QPushButton(tr("����"));
	QPushButton* Rectangle=new QPushButton(tr("�ı���"));
	QPushButton* Ellipse=new QPushButton(tr("��Բ"));
	QPushButton* ERASE=new QPushButton(tr("��Ƥ"));
	shapeLayout->addWidget(None);
	shapeLayout->addWidget(Rectangle);
	shapeLayout->addWidget(Ellipse);
	shapeLayout->addWidget(ERASE);
	m_MainLayout->addLayout(shapeLayout);
	
	
}

void DoNewDialog::creatColorComboBox( QComboBox*comboBox )
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
