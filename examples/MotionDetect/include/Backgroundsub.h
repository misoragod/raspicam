/*
 * Backgroundsub.h
 */
#pragma once 
#include <iostream>
#include <opencv2/opencv.hpp>

class Backgroundsub {
private:
	cv::Ptr<cv::BackgroundSubtractor> bgSub;
public:
	Backgroundsub();
	virtual ~Backgroundsub();
	void createDiff(cv::Mat &img, cv::Mat &maskImg);
	void showImg(cv::Mat &img);
	bool doWatchChange(cv::Mat &mask, int threshold);
	void setTextMsg(cv::Mat &img, cv::String str);

};

