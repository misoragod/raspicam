#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "VariousConf.h"
#include "VariousDisplay.h"

int main(){
    const cv::String windowName = "FACE DETECT";
    int width=480, height=320;

    cv::Mat srcImg, dstImg, grayImg;
    cv::Mat blankImg(cv::Size(width, height), CV_8UC3, cv::Scalar::all(64));
    
    cv::VideoWriter writer;
    raspicam::RaspiCam_Cv cCap;
    cCap.set(cv::CAP_PROP_FORMAT, CV_8UC3);
    cCap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cCap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    if (!cCap.open()){
        std::cout << "Error opning the camera"<< std::endl;
        return -1;
    }
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO);
    cv::moveWindow(windowName, 0, -28);
    std::string cascadeName = "/home/pi/raspicam/examples/FaceDetect/Cascade/haarcascade_frontalface_alt2.xml";
                                                                             
    cv::CascadeClassifier cascade;
    if (!cascade.load(cascadeName)){
        std::cout << "Cascade File Read Error" << std::endl;
        return 1;
    }
    VariousConf vConf;
    cv::String fileName =  "/media/pi/FCE3-D608/" + vConf.getTimeNumStr() + ".avi";
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    int timeNum = std::atoi(vConf.getTimeNumStr().c_str());
    std::vector<cv::Rect> face;
    int fps = 5;
    writer.open(fileName, fourcc, fps, cv::Size(width, height), true);
    VariousDisplay vDis;
    while(true){
        cCap.grab();
        cCap.retrieve(srcImg);
        dstImg = srcImg.clone();
        cv::cvtColor(dstImg, grayImg, CV_BGR2GRAY);
        cascade.detectMultiScale(grayImg, face, 1.11, 3, 0, cv::Size(100, 100), cv::Size(300, 300));
        for(std::vector<cv::Rect>::iterator ite = face.begin(); ite != face.end(); ite++){
            timeNum = std::atoi(vConf.getTimeNumStr().c_str());
            cv::rectangle(dstImg,  *ite, cv::Scalar(0,255,255), 1, cv::LINE_AA);
        }
        int progTime = atoi(vConf.getTimeNumStr().c_str());
        if (timeNum + 5 > progTime) {
            vDis.setRecSignal(dstImg);
            vDis.setTextMsg(srcImg, (cv::String)vConf.getDateTime());
            writer << srcImg;
        }else if (timeNum + 7 > progTime) {
            writer << blankImg;
        }
        cv::imshow(windowName, dstImg);
        if (cv::waitKey(1) >= 0) break;
    }
    return 0;
}