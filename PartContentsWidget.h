#pragma once
#include "qwidget.h"
#include <QVBoxLayout>
#include <QWebView>
#include "PainterWindow.h"
#include "CameraDialog.h"
#include "VideoDialog.h"
#include "DeskVideoWnd.h"
#include <QProcess>
#include <QLibrary>
#include <commonapi.h>
#include <DataBaseView.h>

class PartContentsWidget :
	public QWidget
{
	Q_OBJECT
private:
	DataBaseView* m_DataBaseWindow;//���ݿ�ʾ������
	QProcess m_ProcessFeiQiu;//ִ�и��ӳ���
	DeskVideoWnd* m_DeskShow;//��ʾ����¼��
	QWebView* m_WebView;//web���
	PainterWindow* m_PaintWnd;//�����õ�
    CameraDialog* m_CameraDialog;//����Ի�
	VideoDialog* m_VideoDialog;//���ŵ�Ӱ
	QLibrary* testLib;//�������
	QHash<QString,BasicPlugin*> m_plugins;//���������
public:
	PartContentsWidget(QWidget* parent=nullptr);
	virtual ~PartContentsWidget(void);
	void addItem(QString name,QString imagePath);
public:
	QVBoxLayout* m_HboxLayout;
	public slots:
		void openFolder();//���ļ��в���
		void openCamera();//������ͷ����
		void openPainter();//�򿪻������
		void openVideo();//�򿪲���������
		void openWeb();//����ҳ����
		void openDeskRecording();//������¼�Ʋ���
		void openQqProcess();//���������̲���
		void DllTest();//��̬����dll����
		//���ݿ����
		void DataBaseTest();

protected:
	void paintEvent(QPaintEvent * e);
		
};

