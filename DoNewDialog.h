#pragma once
#include "qdialog.h"
#include <QSpinBox>
#include <QBrush>
#include <QTextBrowser>
#include <QComboBox>
class DoNewDialog :
	public QDialog
{
	Q_OBJECT

public:
	explicit DoNewDialog(QWidget *parent = 0);
	~DoNewDialog();
	int getWidth();  //用于返回画笔的宽
	int getHeight();  //用于返回画笔的高
	QColor getBackColor();  //用于返回画布的背景色
	void DialogInit();
	void creatColorComboBox( QComboBox*comboBox );

protected:
	void changeEvent(QEvent *e);

private:
	QSpinBox* m_widthSpinBox;//微调框部件
	QSpinBox* m_heightSpinBox;//微调框部件
	QBrush* m_brush;//画刷，暂时没用上
	QTextBrowser* m_textBrowser;//浏览框
	QComboBox* m_Combox;//一个颜色示例框
	//Ui::DoNewDialog *ui;
	QColor backColor;  //用于保存画布的背景色

	private slots:
		void on_toolButton_clicked();
};

