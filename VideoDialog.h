#pragma once
#include <QDialog>
//#include <opencv/highgui.h>  //包含opencv库头文件  
//#include <opencv/cv.h>  

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QImage>
#include <phonon/mediaobject.h>  
#include <phonon/VideoWidget>
#include <phonon/AudioOutput>
class VideoDialog :
	public QDialog
{
	Q_OBJECT
public:
	QTimer    *timer;  
	QLabel* m_Label;
	QWidget* m_Canvas;
	QPushButton* m_btn;
	QPushButton* m_btnPause;
	QPushButton* m_btnStop;
	bool b_IsPlaying;
	cv::Mat videoframe;
	cv::VideoCapture capture;
	int m_delay;
	Phonon::MediaObject *m_Movie;
	Phonon::VideoWidget *videowidget;
	Phonon::AudioOutput *audiooutput;
	VideoDialog(void);
	~VideoDialog(void);
	void InitVideoDialog();
	QImage MatToQImage(const cv::Mat& mat);  
	public slots:
		void startVideo();
		void pauseVideo();
		void QtVideo();
		void showVideoFrame();
};

