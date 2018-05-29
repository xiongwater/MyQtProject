#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QDesktopWidget>
#include <QLabel>
class DeskVideoWnd :
	public QMainWindow
{
	Q_OBJECT
public:
	DeskVideoWnd(void);
	~DeskVideoWnd(void);

	QDesktopWidget* m_Desk;
	QPixmap mPix;
	QImage mImg;
	QTimer mTimer;
	QLabel* m_Label;
	QWidget* m_CentralWidget;
    bool isRecording;
	public slots:
		void startRecording();
		void stopRecording();
		void Recording();
};

