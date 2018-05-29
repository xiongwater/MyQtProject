#pragma once
#include "qdialog.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
//#include <opencv/highgui.h>  //����opencv��ͷ�ļ�  
//#include <opencv/cv.h>  
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QImage>
//using namespace cv;
class CameraDialog :
	public QDialog
{
	Q_OBJECT
private:

public:
	CameraDialog(void);
	~CameraDialog(void);
	void CameraDialogInit();
    QImage MatToQImage( const cv::Mat& mat );
	public slots:
		    void startCamera();     
			void readFarme();       // ��ȡ��ǰ֡��Ϣ  
			void closeCamara();     // �ر�����ͷ��  
private:  
	QLabel* m_Label;
	QWidget* m_Canvas;
	QPushButton* m_btn;
	QPushButton* m_btnStop;
	QTimer    *timer;  
	QImage    *imag;  
	CvCapture *cam;// ��Ƶ��ȡ�ṹ�� ������Ϊ��Ƶ��ȡ������һ������  
	IplImage  *frame;//����IplImage����ָ�룬���������ڴ�ռ������ÿһ֡ͼ��
	cv::Mat videoframe;
	cv::VideoCapture capture;
};

