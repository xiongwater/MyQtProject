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
	int getWidth();  //���ڷ��ػ��ʵĿ�
	int getHeight();  //���ڷ��ػ��ʵĸ�
	QColor getBackColor();  //���ڷ��ػ����ı���ɫ
	void DialogInit();
	void creatColorComboBox( QComboBox*comboBox );

protected:
	void changeEvent(QEvent *e);

private:
	QSpinBox* m_widthSpinBox;//΢���򲿼�
	QSpinBox* m_heightSpinBox;//΢���򲿼�
	QBrush* m_brush;//��ˢ����ʱû����
	QTextBrowser* m_textBrowser;//�����
	QComboBox* m_Combox;//һ����ɫʾ����
	//Ui::DoNewDialog *ui;
	QColor backColor;  //���ڱ��滭���ı���ɫ

	private slots:
		void on_toolButton_clicked();
};

