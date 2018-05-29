#include "VideoDialog.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QFile>
VideoDialog::VideoDialog(void)
{
	InitVideoDialog();
}


VideoDialog::~VideoDialog(void)
{
	delete videowidget;
	delete audiooutput;
}

void VideoDialog::InitVideoDialog()
{

	b_IsPlaying=false;
	QVBoxLayout* m_MainLayout=new QVBoxLayout(this);
	this->setLayout(m_MainLayout);
	m_Canvas=new QWidget(this);
	m_Label=new QLabel(this);
	m_btn=new QPushButton(tr("Opencv播放"));
	m_btnStop=new QPushButton(tr("Qt播放"));
	m_btnPause=new QPushButton(tr("Opencv暂停"));
	connect(m_btnStop,SIGNAL(clicked()),this,SLOT(QtVideo()));
	connect(m_btn,SIGNAL(clicked()),this,SLOT(startVideo()));
	connect(m_btnPause,SIGNAL(clicked()),this,SLOT(pauseVideo()));
	m_MainLayout->addWidget(m_Canvas);
	m_MainLayout->addWidget(m_Label);
	m_MainLayout->addWidget(m_btn);
	m_MainLayout->addWidget(m_btnStop);
	m_MainLayout->addWidget(m_btnPause);
	timer   = new QTimer(this);  
	connect(timer,SIGNAL(timeout()),this,SLOT(showVideoFrame()));
	b_IsPlaying=false;
	
	capture.open("D:/code/MyProduction/MyProduction/Resources/dota.avi");//opencv无法像Qt一样打开编译好的资源文件，原因不祥
	double rate = capture.get(CV_CAP_PROP_FPS);
	m_delay = 1000/rate;
	m_Movie=Phonon::createPlayer(Phonon::VideoCategory,Phonon::MediaSource(":/Resources/dota.avi"));  
    videowidget = new Phonon::VideoWidget;
	Phonon::createPath(m_Movie,videowidget);
	audiooutput = new Phonon::AudioOutput(Phonon::VideoCategory);
	Phonon::createPath(m_Movie,audiooutput);


	
	
}

void VideoDialog::startVideo()
{

	//b_IsPlaying=false;
	//capture.open("dota.avi");
	//double rate = capture.get(CV_CAP_PROP_FPS);
	//int delay = 1000/rate;
	timer->start(m_delay);
	//while(!b_IsPlaying)
	//{
	//	capture>>videoframe;
	//	if(!videoframe.empty())
	//	{

	//		QImage image=MatToQImage(videoframe);  
	//		m_Label->setScaledContents(true);  
	//		QSize qs = m_Label->rect().size();  
	//		m_Label->setPixmap(QPixmap::fromImage(image).scaled(qs));  
	//		m_Label->repaint();  
	//		//cv::waitKey(10000);
	//		//cv::imshow("看大片",videoframe);  //显示当前帧
	//	}	
	//	cv::waitKey(10000);
	//	QApplication::processEvents();
	//}
	//capture.release();
}

void VideoDialog::QtVideo()
{
	if(m_Movie->state()==Phonon::State::PlayingState)
	{
       m_btnStop->setText(tr("Qt暂停"));
	   m_Movie->pause();
	}
	else if(m_Movie->state()==Phonon::State::PausedState)
	{
		m_btnStop->setText(tr("Qt继续"));
	   m_Movie->play();
	}
	else if(m_Movie->state()==Phonon::State::StoppedState)
	{
		m_btnStop->setText(tr("Qt播放"));
		m_Movie->play();
		videowidget->show();
	}
	

}

QImage VideoDialog::MatToQImage( const cv::Mat& mat )
{
	// 8-bits unsigned, NO. OF CHANNELS = 1      
	if (mat.type() == CV_8UC1)  
	{  
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);  
		// Set the color table (used to translate colour indexes to qRgb values)      
		image.setColorCount(256);  
		for (int i = 0; i < 256; i++)  
		{  
			image.setColor(i, qRgb(i, i, i));  
		}  
		// Copy input Mat      
		uchar *pSrc = mat.data;  
		for (int row = 0; row < mat.rows; row++)  
		{  
			uchar *pDest = image.scanLine(row);  
			memcpy(pDest, pSrc, mat.cols);  
			pSrc += mat.step;  
		}  
		return image;  
	}  
	// 8-bits unsigned, NO. OF CHANNELS = 3      
	else if (mat.type() == CV_8UC3)  
	{  
		// Copy input Mat     
		const uchar *pSrc = (const uchar*)mat.data;  
		// Create QImage with same dimensions as input Mat      
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);  
		return image.rgbSwapped();  
	}  
	else if (mat.type() == CV_8UC4)  
	{  
		// Copy input Mat      
		const uchar *pSrc = (const uchar*)mat.data;  
		// Create QImage with same dimensions as input Mat      
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);  
		return image.copy();  
	}  
	else  
	{  
		return QImage();  
	}
}

void VideoDialog::showVideoFrame()
{
	capture>>videoframe;
	if(!videoframe.empty())
	{

		QImage image=MatToQImage(videoframe);  
		m_Label->setScaledContents(true);  
		QSize qs = m_Label->rect().size();  
		m_Label->setPixmap(QPixmap::fromImage(image).scaled(qs));  
		m_Label->repaint();  
		//cv::waitKey(10000);
		//cv::imshow("看大片",videoframe);  //显示当前帧
	}	
}

void VideoDialog::pauseVideo()
{
	timer->stop();
}
