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
    m_btn=new QPushButton(tr("��ʼ����"));
	m_btnStop=new QPushButton(tr("ֹͣ����"));

	connect(m_btn,SIGNAL(clicked()),this,SLOT(startCamera()));
	connect(m_btnStop,SIGNAL(clicked()),this,SLOT(closeCamara()));
	m_MainLayout->addWidget(m_Canvas);
	m_MainLayout->addWidget(m_Label);
	m_MainLayout->addWidget(m_btn);
	m_MainLayout->addWidget(m_btnStop);

	cam     = NULL;  
	timer   = new QTimer(this);  
	imag    = new QImage();         //��ʼ��  

	/*�źźͲ�*/  
	connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // ʱ�䵽����ȡ��ǰ����ͷ��Ϣ  
	

}

/********************************* 
********* ��ȡ����ͷ��Ϣ *********** 
**********************************/  
void CameraDialog::readFarme()  
{  

#ifdef _OPENCV32_
	//frame = cvQueryFrame(cam);// ������ͷ��ץȡ������ÿһ֡  
	// ��ץȡ����֡��ת��ΪQImage��ʽ��QImage::Format_RGB888��ͬ������ͷ�ò�ͬ�ĸ�ʽ�� 
	if(capture.isOpened())
	{	
		capture >> videoframe;
		if(!videoframe.empty())
		{
			//imshow("�ɼ�����",videoframe);
			
				m_Label->setPixmap(QPixmap::fromImage(MatToQImage(videoframe)));  // ��ͼƬ��ʾ��label��  
			
		}	
	}
#else
	m_Label->setPixmap(QPixmap::fromImage(QImage("im.png")));  // ��ͼƬ��ʾ��label�� 
#endif	 
}  


/******************************* 
***�ر�����ͷ���ͷ���Դ�������ͷ�*** 
********************************/  
void CameraDialog::closeCamara()  
{  
	timer->stop();// ֹͣ��ȡ���ݡ�  
	if(capture.isOpened())
	{
			capture.release();
	}	
}  

void CameraDialog::startCamera()
{

#ifdef _OPENCV32_
	//cam = cvCreateCameraCapture(0);//������ͷ��������ͷ�л�ȡ��Ƶ  
	capture.open(0);
	timer->start(33);              // ��ʼ��ʱ����ʱ�򷢳�timeout()�ź�
#else
	timer->start(30);              // ��ʼ��ʱ����ʱ�򷢳�timeout()�ź�
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

