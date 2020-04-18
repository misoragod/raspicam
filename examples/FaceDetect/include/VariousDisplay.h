#pragma once
#include <opencv2/opencv.hpp>
#include <string>


class VariousDisplay
{
public:
    VariousDisplay();
    virtual ~VariousDisplay();
    void setTextMsg(cv::Mat&, cv::String);
    void setRecSignal(cv::Mat& );
};
