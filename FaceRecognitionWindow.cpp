#include "FaceRecognitionWindow.h"
#include<iostream>  
#include "opencv2\objdetect\objdetect.hpp"  

using namespace std;  
using namespace cv;  


FaceRecognitionWindow* FaceRecognitionWindow::singleton=nullptr;
FaceRecognitionWindow::FaceRecognitionWindow(void)
	:minDist(100)
{  
	target[0] = target[1] = target[2] = 0;  
}  


FaceRecognitionWindow::~FaceRecognitionWindow(void)
{
}

void FaceRecognitionWindow::destory(){  
	if(singleton!=0){  
		delete singleton;  
	}  
	singleton = 0;  
}  


void FaceRecognitionWindow::setColorDistanceThreshold(int distance){  
	if(distance < 0){  
		distance = 0;  
	}  
	minDist = distance;  
}  


int FaceRecognitionWindow::getColorDistanceThreshold() const{  
	return minDist;  
}  


void FaceRecognitionWindow::setTargetColor(unsigned char red,  
	unsigned char green, unsigned char blue){  
		target[2] = red;  
		target[1] = green;  
		target[0] = blue;  
}  


void FaceRecognitionWindow::setTargetColor(cv::Vec3b color){  
	target = color;  
}  


cv::Vec3b FaceRecognitionWindow::getTargetColor() const{  
	return target;  
}  


int FaceRecognitionWindow::getDistance(const cv::Vec3b& color) const{  
	return abs(color[0]-target[0])+abs(color[1]-target[1])+abs(color[2]-target[2]);  
}  

void FaceRecognitionWindow::process(){  
	result.create(image.rows, image.cols, CV_8U);  
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();  
	cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();  
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();  
	for(; it!=itend; ++it, ++itout){  
		if(getDistance(*it) < minDist){  
			*itout = 255;  
		}else{  
			*itout = 0;  
		}  
	}  
}  


cv::Mat FaceRecognitionWindow::getResult() const{  
	return result;  
}  


bool FaceRecognitionWindow::setInputImage(std::string filename){  
	image = cv::imread(filename);  
	if(!image.data){  
		return false;  
	}  
	return true;  
}  


cv::Mat FaceRecognitionWindow::getInputImage() const{  
	return image;  
}  

FaceRecognitionWindow * FaceRecognitionWindow::getInstance()
{
	if(singleton == 0){  
		singleton = new FaceRecognitionWindow;  
	}  
	return singleton;
}

void FaceRecognitionWindow::runrunrun()
{
	VideoCapture cap(0);    //打开默认摄像头  
	if (!cap.isOpened())  
	{  
		return ;  
	}  
	Mat frame;  
	Mat edges;  
	Mat gray;  

	CascadeClassifier cascade;  
	bool stop = false;  
	//训练好的文件名称，放置在可执行文件同目录下  
	//cascade.load("haarcascade_frontalface_alt.xml");  

	//Ptr<FaceRecognizer> modelPCA = createEigenFaceRecognizer();  
	//modelPCA->load("MyFacePCAModel.xml");  

	while (!stop)  
	{  
		cap >> frame;  

		//建立用于存放人脸的向量容器  
		vector<Rect> faces(0);  

		//cvtColor(frame, gray, CV_BGR2GRAY);  
		//改变图像大小，使用双线性差值  
		//resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);  
		//变换后的图像进行直方图均值化处理  
	//	equalizeHist(gray, gray);  

		//cascade.detectMultiScale(gray, faces,  
		//	1.1, 2, 0  
		//	//|CV_HAAR_FIND_BIGGEST_OBJECT  
		//	//|CV_HAAR_DO_ROUGH_SEARCH  
		//	| CV_HAAR_SCALE_IMAGE,  
		//	Size(30, 30));  

		Mat face;  
		Point text_lb;  

		for (size_t i = 0; i < faces.size(); i++)  
		{  
			if (faces[i].height > 0 && faces[i].width > 0)  
			{  
				face = gray(faces[i]);  
				text_lb = Point(faces[i].x, faces[i].y);  

				rectangle(frame, faces[i], Scalar(255, 0, 0), 1, 8, 0);  
			}  
		}  

		Mat face_test;  

		int predictPCA = 0;  
		if (face.rows >= 120)  
		{  
			//resize(face, face_test, Size(92, 112));  

		}  
		//Mat face_test_gray;  
		//cvtColor(face_test, face_test_gray, CV_BGR2GRAY);  

		if (!face_test.empty())  
		{  
			//测试图像应该是灰度图  
		//	predictPCA = modelPCA->predict(face_test);  
		}  

		cout << predictPCA << endl;  
		if (predictPCA == 40)  
		{  
			string name = "LiuXiaoLong";  
			putText(frame, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));  
		}  

		imshow("face", frame);  
		if (waitKey(50) >= 0)  
			stop = true;  
	}
}


//#include<opencv2\opencv.hpp>  
//#include<iostream>  
//
//using namespace std;  
//using namespace cv;  
//
//int main()  
//{  
//	VideoCapture cap(0);    //打开默认摄像头  
//	if (!cap.isOpened())  
//	{  
//		return -1;  
//	}  
//	Mat frame;  
//	Mat edges;  
//	Mat gray;  
//
//	CascadeClassifier cascade;  
//	bool stop = false;  
//	//训练好的文件名称，放置在可执行文件同目录下  
//	cascade.load("haarcascade_frontalface_alt.xml");  
//
//	Ptr<FaceRecognizer> modelPCA = createEigenFaceRecognizer();  
//	modelPCA->load("MyFacePCAModel.xml");  
//
//	while (!stop)  
//	{  
//		cap >> frame;  
//
//		//建立用于存放人脸的向量容器  
//		vector<Rect> faces(0);  
//
//		cvtColor(frame, gray, CV_BGR2GRAY);  
//		//改变图像大小，使用双线性差值  
//		//resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);  
//		//变换后的图像进行直方图均值化处理  
//		equalizeHist(gray, gray);  
//
//		cascade.detectMultiScale(gray, faces,  
//			1.1, 2, 0  
//			//|CV_HAAR_FIND_BIGGEST_OBJECT  
//			//|CV_HAAR_DO_ROUGH_SEARCH  
//			| CV_HAAR_SCALE_IMAGE,  
//			Size(30, 30));  
//
//		Mat face;  
//		Point text_lb;  
//
//		for (size_t i = 0; i < faces.size(); i++)  
//		{  
//			if (faces[i].height > 0 && faces[i].width > 0)  
//			{  
//				face = gray(faces[i]);  
//				text_lb = Point(faces[i].x, faces[i].y);  
//
//				rectangle(frame, faces[i], Scalar(255, 0, 0), 1, 8, 0);  
//			}  
//		}  
//
//		Mat face_test;  
//
//		int predictPCA = 0;  
//		if (face.rows >= 120)  
//		{  
//			resize(face, face_test, Size(92, 112));  
//
//		}  
//		//Mat face_test_gray;  
//		//cvtColor(face_test, face_test_gray, CV_BGR2GRAY);  
//
//		if (!face_test.empty())  
//		{  
//			//测试图像应该是灰度图  
//			predictPCA = modelPCA->predict(face_test);  
//		}  
//
//		cout << predictPCA << endl;  
//		if (predictPCA == 40)  
//		{  
//			string name = "LiuXiaoLong";  
//			putText(frame, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));  
//		}  
//
//		imshow("face", frame);  
//		if (waitKey(50) >= 0)  
//			stop = true;  
//	}  
//
//	return 0;  
//}  