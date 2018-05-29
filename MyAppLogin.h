#pragma once
#include "qmainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
class MyAppLogin :
	public QMainWindow
{
	Q_OBJECT 
public:
	MyAppLogin(QWidget *parent = nullptr);
	virtual ~MyAppLogin(void);
	
	QString FirstAnswer;
	QString SecondAnswer;
	//////////////     UI   /////////////////////////////////////////////
	QPushButton* m_ButtonOk;
	QLabel* m_LabelQuestion;
	QLabel* m_LabelAnswer;
	QLineEdit* m_LineEditQuestion;
	QLineEdit* m_LineEditAnswer;
	QWidget* m_CentralWidget;
	///////////////////////////////////////////////////////////
	void CreatMenber();
	void SetUi();
	void InitLogin();
	private slots:  
		int OnBtnOk();  
		int OnReturnPressed();  
   signals:
			void DisPlay(int);
			void LoginSuccessed();
};

