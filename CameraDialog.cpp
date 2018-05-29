#include "CameraDialog.h"
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <iostream>
#include <fstream>
using namespace std;
CameraDialog::CameraDialog(void)
{
	CameraDialogInit();
}

CameraDialog::~CameraDialog(void)
{
}

void CameraDialog::CameraDialogInit()
{
	QVBoxLayout* m_MainLayout=new QVBoxLayout(this);
	this->setLayout(m_MainLayout);
	m_Canvas=new QWidget(this);
    m_Label=new QLabel(this);
    m_btn=new QPushButton(tr("开始摄像"));
	m_btnStop=new QPushButton(tr("停止测试"));

	connect(m_btn,SIGNAL(clicked()),this,SLOT(startCamera()));
	connect(m_btnStop,SIGNAL(clicked()),this,SLOT(closeCamara()));
	m_MainLayout->addWidget(m_Canvas);
	m_MainLayout->addWidget(m_Label);
	m_MainLayout->addWidget(m_btn);
	m_MainLayout->addWidget(m_btnStop);

	cam     = NULL;  
	timer   = new QTimer(this);  
	imag    = new QImage();         //初始化  

	/*信号和槽*/  
	connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息  
	

}

/********************************* 
********* 读取摄像头信息 *********** 
**********************************/  
void CameraDialog::readFarme()  
{  

#ifdef _OPENCV32_
	//frame = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧  
	// 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。 
	if(capture.isOpened())
	{	
		capture >> videoframe;
		if(!videoframe.empty())
		{
			//imshow("采集摄像",videoframe);
			
				m_Label->setPixmap(QPixmap::fromImage(MatToQImage(videoframe)));  // 将图片显示到label上  
			
		}	
	}
#else
	m_Label->setPixmap(QPixmap::fromImage(QImage("im.png")));  // 将图片显示到label上 
#endif	 
}  


/******************************* 
***关闭摄像头，释放资源，必须释放*** 
********************************/  
void CameraDialog::closeCamara()  
{  
	timer->stop();// 停止读取数据。  
	if(capture.isOpened())
	{
			capture.release();
	}	
}  

void CameraDialog::startCamera()
{

#ifdef _OPENCV32_
	//cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频  
	capture.open(0);
	timer->start(33);              // 开始计时，超时则发出timeout()信号
#else
	timer->start(30);              // 开始计时，超时则发出timeout()信号
#endif
			
}
	
QImage CameraDialog::MatToQImage( const cv::Mat& mat )
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

