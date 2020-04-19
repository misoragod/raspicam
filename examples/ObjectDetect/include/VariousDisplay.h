/*
 * VariousDisplay.h
 */
#pragma once
#include <opencv2/opencv.hpp>

class VariousDisplay {
private:
	double leftBorder;
	double rightBorder;
	double distanceLine;

	void setSignal(cv::Mat& img);
	void setDistanceLine(cv::Mat& img);
	void setMyLine(cv::Mat& img);

public:
	VariousDisplay();
	virtual ~VariousDisplay();
	void setTextMsg(cv::Mat& img, cv::String str);
	void setCenterMark(cv::Mat& img);
	void findCarBody(cv::Mat& img, cv::CascadeClassifier cascade);
	void myRoadMask(cv::Mat& mask);
};
