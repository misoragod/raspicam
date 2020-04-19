#include "VariousDisplay.h"

VariousDisplay::VariousDisplay(){

}
void VariousDisplay::setTextMsg(cv::Mat& img, cv::String str){
    cv::Mat overlay, output;
    double alpha = 0.5;
    img.copyTo(overlay);
    cv::rectangle(overlay, cv::Rect(5, 5, 200, 30), cv::Scalar(192, 192, 192), -1);
    cv::addWeighted(overlay, alpha, img, 1 - alpha, 0, img);
    cv::putText(img, str, cv::Point(10,25), CV_FONT_NORMAL, 0.5, cv::Scalar::all(32), 1, cv::LINE_AA);
}
void VariousDisplay::setRecSignal(cv::Mat& img){
    cv::Mat overlay, output;
    double alpha = 0.3;
    img.copyTo(overlay);
    cv::rectangle(overlay, cv::Rect(5, 5, 17, 30), cv::Scalar::all(0), -1);
    cv::rectangle(overlay, cv::Rect(8, 8, 64, 24), cv::Scalar::all(192), -1);
    cv::circle(img, cv::Point(20, 19), 5, cv::Scalar(64, 64, 255), -1);
    cv::addWeighted(overlay, alpha, img, 1 - alpha, 0, img);
    cv::putText(img, "REC", cv::Point(30,24), CV_FONT_NORMAL, 0.5, cv::Scalar::all(32), 1, cv::LINE_AA); 
}
VariousDisplay::~VariousDisplay(){
}