#pragma once
#include "qmainwindow.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
class FaceRecognitionWindow :
	public QMainWindow
{
	Q_OBJECT
public:
//	FaceRecognitionWindow(void);
	~FaceRecognitionWindow(void);
private:  
	int minDist;  
	cv::Vec3b target;  
	cv::Mat result;  
	cv::Mat image;  
	FaceRecognitionWindow();  
	static FaceRecognitionWindow *singleton;  
public:  
	static FaceRecognitionWindow * getInstance(); 

	static void destory();  
	void setColorDistanceThreshold(int);  
	int getColorDistanceThreshold() const;  
	void setTargetColor(unsigned char, unsigned char, unsigned char);  
	void setTargetColor(cv::Vec3b);  
	cv::Vec3b getTargetColor() const;  
	void process();  
	int getDistance(const cv::Vec3b&) const;  
	cv::Mat getResult() const;  
	bool setInputImage(std::string);  
	cv::Mat getInputImage() const;  
	void runrunrun();
};

