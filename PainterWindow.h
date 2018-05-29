#pragma once
#include "qmainwindow.h"
#include <QComboBox>
#include<QScrollArea>
#include "PaintWidget.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "DoNewDialog.h"
class PainterWindow :
	public QMainWindow
{

	Q_OBJECT

public:
	explicit PainterWindow(QWidget *parent = 0);
	~PainterWindow();

	void doNew();  //�½��ļ�����
	void doOpen();  //���ļ�����
	bool doFileSave();  //�����ļ�����
	bool doFileSaveAs();  //�ļ����Ϊ����
	//������ɫ��Ͽ�
	void creatColorComboBox(QComboBox*comboBox);
	void InitWindow();
private:
	QComboBox* m_ColorCombox;
	DoNewDialog* toolDialog;
	PaintWidget*area;
	QScrollArea*scrollArea;

	bool isSaved;  //��־�ļ��Ƿ񱣴��
	QString curFile;  //���浱ǰ�ļ���·��
	bool maybeSave();  //�Ƿ񱣴��ļ�

	bool saveFile(QString fileName);  //ʵ���ļ��Ĵ洢


protected:
	/*void changeEvent(QEvent *e);
	void closeEvent(QCloseEvent*);*/
	
	virtual void resizeEvent(QResizeEvent * e)
	{
		QMainWindow::resizeEvent(e);
		
	}
	private slots:

		void openToolDialog();
		/*void on_action_triggered();
		void on_brushColorComboBox_currentIndexChanged(int index);
		void on_penColorComboBox_currentIndexChanged(int index);
		void on_penWidthSpinBox_valueChanged(int );
		void on_penStyleComboBox_currentIndexChanged(QString );
		void on_shapeComboBox_currentIndexChanged(QString );
		void on_action_28_triggered();
		void on_action_26_triggered();
		void on_action_24_triggered();
		void on_action_23_triggered();
		void on_action_22_triggered();
		void on_action_21_triggered();
		void on_action_20_triggered();
		void on_action_P_triggered();
		void on_action_X_triggered();
		void on_action_A_triggered();
		void on_action_S_triggered();
		void on_action_O_triggered();
		void on_action_N_triggered();*/
};


