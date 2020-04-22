/*
 * ImageControl.h
 */
#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>


class ImageControl {
public:
	ImageControl();
	virtual ~ImageControl();
	bool doWatchChange(cv::Mat &maskImg, int threshold);
	void setDateTime(cv::Mat &img);
};


