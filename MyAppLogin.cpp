#include "MyAppLogin.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QColor>
//#include "FaceRecognitionWindow.h"
#include "MyApp.h"
MyAppLogin::MyAppLogin(QWidget *parent)
	:QMainWindow(parent)
{
	InitLogin();
}

MyAppLogin::~MyAppLogin(void)
{
}

void MyAppLogin::SetUi()
{
	this->setCentralWidget(m_CentralWidget);
	this->setWindowTitle( QString::fromLocal8Bit("日落映山红,倦鸟孤飞晚霞中"));
	QVBoxLayout* mainLayout=new QVBoxLayout();
	QHBoxLayout* questionLayout=new QHBoxLayout();
	QHBoxLayout* answerLayout=new QHBoxLayout();
	QHBoxLayout* btnLayout=new QHBoxLayout();
	m_LabelAnswer->setText( QString::fromLocal8Bit("不负如来不负卿"));
	m_LabelQuestion->setText( QString::fromLocal8Bit("世间安得双全法"));

	//设置字体颜色
	QPalette pe;
	pe.setColor(QPalette::WindowText,Qt::yellow);
	m_LabelAnswer->setPalette(pe);
	m_LabelQuestion->setPalette(pe);
	questionLayout->addStretch();
	questionLayout->addWidget(m_LabelQuestion);
	questionLayout->addWidget(m_LineEditQuestion);
	questionLayout->addStretch();
	answerLayout->addStretch();
	answerLayout->addWidget(m_LabelAnswer);
	answerLayout->addWidget(m_LineEditAnswer);
	answerLayout->addStretch();
	mainLayout->addStretch();
	mainLayout->addLayout(questionLayout);
	mainLayout->addLayout(answerLayout);
	mainLayout->addLayout(btnLayout);
	m_ButtonOk->setText(QString::fromLocal8Bit("冉起朝阳艳，大雁携偶云中采"));
	//pe.setColor(QPalette::WindowText,Qt::green);
	//对于button上述设置字体颜色方法不管用
	m_ButtonOk->setStyleSheet("background-color: rgb(170, 0, 255);");
	mainLayout->addWidget(m_ButtonOk);
	//this->setLayout(mainLayout);
	this->centralWidget()->setLayout(mainLayout);
    QDesktopWidget* desk=QApplication::desktop();
	this->resize(desk->size()/4);
	//setStyleSheet("background-color:blue");
	setObjectName("JUSTLOGINWINDOW");
	setStyleSheet("#JUSTLOGINWINDOW{border-image:url(:/Resources/login.png)}");	
	//setStyleSheet("border-image:url(login.png)");
}

void MyAppLogin::CreatMenber()
{
	m_ButtonOk=new QPushButton();
	m_LabelAnswer=new QLabel();
	m_LabelQuestion=new QLabel();
	m_LineEditAnswer=new QLineEdit();
	m_LineEditQuestion=new QLineEdit();
	m_CentralWidget=new QWidget();
}

void MyAppLogin::InitLogin()
{
	CreatMenber();
	SetUi();
	this->hide();

	connect(m_ButtonOk, SIGNAL(clicked()), this, SLOT(OnBtnOk()));  
	connect(m_LineEditAnswer,SIGNAL(returnPressed()),this,SLOT(OnReturnPressed()));  
	QSettings*   cfg=MyApp::getInstance()->m_Config;
	//QSettings   cfg(QApplication::applicationDirPath() + "\\" + AppConfig, QSettings::IniFormat, NULL);
	m_LineEditQuestion->setText(cfg->value("ContentTest/LastLogin", "").toString());

}

int MyAppLogin::OnReturnPressed()
{
	OnBtnOk();  
	return 0;
}

int MyAppLogin::OnBtnOk()
{
	QString user = m_LineEditQuestion->text();  
	QString Paswd = m_LineEditAnswer->text(); 
	QSettings*   cfg=MyApp::getInstance()->m_Config;
	//QSettings   cfg(QApplication::applicationDirPath() + "\\" + AppConfig, QSettings::IniFormat, NULL);

	cfg->setValue("/ContentTest/LastLogin",user.toLatin1());  

	if(MyApp::getInstance()->m_FirstAnswer==user.toLatin1()&&(MyApp::getInstance()->m_SecondAnswer==Paswd.toLatin1()))
	{
		//这里执行登陆
		QMessageBox::information(this,"流年啊","带我去未来"); 
		emit LoginSuccessed();
		hide();
		return 0;
	}
	else  
	{  
		QMessageBox::information(this,"安稳啊","永远是谎言"); 
		return 1;
	}  
	return -1;
}
