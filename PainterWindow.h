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

	void doNew();  //新建文件操作
	void doOpen();  //打开文件操作
	bool doFileSave();  //保存文件操作
	bool doFileSaveAs();  //文件另存为操作
	//构建颜色组合框
	void creatColorComboBox(QComboBox*comboBox);
	void InitWindow();
private:
	QComboBox* m_ColorCombox;
	DoNewDialog* toolDialog;
	PaintWidget*area;
	QScrollArea*scrollArea;

	bool isSaved;  //标志文件是否保存过
	QString curFile;  //保存当前文件的路径
	bool maybeSave();  //是否保存文件

	bool saveFile(QString fileName);  //实现文件的存储


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


