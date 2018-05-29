#pragma once
#include "qdialog.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
//#include <opencv/highgui.h>  //包含opencv库头文件  
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
			void readFarme();       // 读取当前帧信息  
			void closeCamara();     // 关闭摄像头。  
private:  
	QLabel* m_Label;
	QWidget* m_Canvas;
	QPushButton* m_btn;
	QPushButton* m_btnStop;
	QTimer    *timer;  
	QImage    *imag;  
	CvCapture *cam;// 视频获取结构， 用来作为视频获取函数的一个参数  
	IplImage  *frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
	cv::Mat videoframe;
	cv::VideoCapture capture;
};

