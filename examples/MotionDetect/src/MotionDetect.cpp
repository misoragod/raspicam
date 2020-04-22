/*
* Name        : OpenCVCameraSample.cpp
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "Backgroundsub.h"
#include "VariousConf.h"

int main(int argc, const char* argv[]) {

	const cv::String windowName = "MOTION DETECT";
	int width=480, height=320;

	cv::Mat srcImg, dstImg, maskImg;
	cv::Mat blankImg(cv::Size(width, height), CV_8UC3, cv::Scalar::all(64));

	cv::VideoWriter writer;
	raspicam::RaspiCam_Cv cCap;
	cCap.set(cv::CAP_PROP_FORMAT, CV_8UC3);
	cCap.set(cv::CAP_PROP_FRAME_WIDTH, width);
	cCap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
	if (!cCap.open()){
		std::cout << "Error opening the camera" << std::endl;
		return -1;
	}

	VariousConf vConf;
	cv::String fileName = "/media/pi/FCE3-D6081/" + vConf.getTimeNumStr() + ".avi";
	int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

	Backgroundsub bgsub;
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO);
	cv::moveWindow(windowName, 0 , -28);
	int thMax=100, th=10;
	cv::createTrackbar("Thresholds:", windowName, &th, thMax);

	int timeNum = std::atoi(vConf.getTimeNumStr().c_str());

	int fps = 5;
	int flag_detect = 0;
	writer.open(fileName, fourcc, fps, cv::Size(width, height), true);
	while(true){
		cCap.grab();
		cCap.retrieve(srcImg);
		dstImg = srcImg.clone();
		bgsub.createDiff(dstImg, maskImg);
		bgsub.setTextMsg(srcImg, (cv::String)vConf.getDateTime());
		if(bgsub.doWatchChange(maskImg, th)){
			timeNum = std::atoi(vConf.getTimeNumStr().c_str());
			writer << srcImg;
			if (flag_detect == 0) { 
				system("nohup ../scripts/notify.sh detected object&");
				flag_detect = 1;
			}
		}else{
			flag_detect = 0;
		}
		//最後の判定から５秒間記録
		int progTime = atoi(vConf.getTimeNumStr().c_str());
		if(timeNum + 5 > progTime){
			writer << srcImg;
			std::cout << "Write" << " " << timeNum + 5 << " " << vConf.getTimeNumStr() << std::endl;
		}
		else if(timeNum + 7 > progTime){
			writer << blankImg;
		}
		cv::imshow(windowName, dstImg);
		if(cv::waitKey(1) >=0) break;
	}
	writer.release();
	return 0;
}

