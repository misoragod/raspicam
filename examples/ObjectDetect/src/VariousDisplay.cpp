/*
 * VariousDisplay.cpp
*/

#include "VariousDisplay.h"

VariousDisplay::VariousDisplay() {
	leftBorder  = 0.3;
	rightBorder = 0.7;
	distanceLine = 0.8;
}

VariousDisplay::~VariousDisplay() {
}

void VariousDisplay::setTextMsg(cv::Mat& img, cv::String str){
	cv::Mat overlay, output;
	double alpha = 0.5;
	img.copyTo(overlay);
	cv::rectangle(overlay, cv::Rect(5, 5, 200, 30), cv::Scalar(255, 0, 0), -1);
	cv::addWeighted(overlay, alpha, img, 1-alpha, 0, img);
	cv::putText(img, str, cv::Point(10,25), CV_FONT_NORMAL, 0.5, cv::Scalar::all(255), 1, cv::LINE_AA);

}
void VariousDisplay::setSignal(cv::Mat& img){
	cv::Mat overlay, output;
	double alpha = 0.5;
	img.copyTo(overlay);
	cv::rectangle(overlay, cv::Rect(5, 5, 170, 30), cv::Scalar::all(0), -1);
	cv::rectangle(overlay, cv::Rect(8, 8, 164, 24), cv::Scalar::all(192), -1);
	cv::circle(img, cv::Point(20,19), 5, cv::Scalar(64,64,255),-1);
	cv::addWeighted(overlay, alpha, img, 1-alpha, 0, img);
	cv::putText(img, "approaching", cv::Point(40,24), CV_FONT_NORMAL, 0.5, cv::Scalar::all(32), 1, cv::LINE_AA);
}
void VariousDisplay::setDistanceLine(cv::Mat& img){
	int fiftyMetersLine = img.rows * distanceLine;
	cv::line(img, cv::Point(0, fiftyMetersLine), cv::Point(img.cols, fiftyMetersLine), cv::Scalar(0,255,255),1);
}
void VariousDisplay::setMyLine(cv::Mat& img){
	int leftLine  = img.cols * leftBorder;
	int rightLine = img.cols * rightBorder;
	cv::line(img, cv::Point(leftLine,  0), cv::Point(leftLine,  img.cols), cv::Scalar(0,255,255),1);
	cv::line(img, cv::Point(rightLine, 0), cv::Point(rightLine, img.cols), cv::Scalar(0,255,255),1);
}
void VariousDisplay::setCenterMark(cv::Mat& img){
	int centerX = img.cols/2;
	int height = img.rows;
	cv::Point pt[3];
	pt[0] = cv::Point(centerX, height - 10);
	pt[1] = cv::Point(centerX+5, height);
	pt[2] = cv::Point(centerX-5, height);
	cv::fillConvexPoly(img, pt, 3, cv::Scalar(0, 255, 255), 1);
}

void VariousDisplay::findCarBody(cv::Mat& img, cv::CascadeClassifier cascade){
	std::vector<cv::Rect> face;
	cv::Mat roi, grayImg;
	cv::Rect rect(cv::Point(img.cols * leftBorder ,0),cv::Size(img.cols - img.cols * rightBorder,img.rows));
	roi = img(rect);
	cv::cvtColor(roi, grayImg, CV_BGR2GRAY);
	cascade.detectMultiScale(grayImg, face, 1.1, 3, 0, cv::Size(50, 50), cv::Size(150, 150));
	for(std::vector<cv::Rect>::iterator ite = face.begin(); ite != face.end(); ite++){
		int border = ite->y + ite->height;
		if(img.rows * distanceLine < border){
			ite->x = ite->x + img.cols * leftBorder;
			cv::rectangle(img, *ite, cv::Scalar(0,255,255), 1, cv::LINE_AA);
			setSignal(img);
		}
	}
	setDistanceLine(img);
	setMyLine(img);
}
void VariousDisplay::myRoadMask(cv::Mat& mask){
	int width = mask.cols;
	int height = mask.rows;
	cv::Point pt[6];
	pt[0] = cv::Point(width*0.4 , height*0.50);
	pt[1] = cv::Point(width*0.6 , height*0.50);
	pt[2] = cv::Point(width*0.6 , height*0.68);
	pt[3] = cv::Point(width*0.9 , height*0.95);
	pt[4] = cv::Point(width*0.1 , height*0.95);
	pt[5] = cv::Point(width*0.4 , height*0.68);
	cv::fillConvexPoly(mask, pt, 6, cv::Scalar::all(255) , 1);
	mask =~ mask;
}
