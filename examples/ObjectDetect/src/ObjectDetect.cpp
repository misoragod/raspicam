/*
*    ObjectDetect
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "VariousDisplay.h"
#include "VariousConf.h"

int main() {
	const cv::String windowName = "OBJECT DETECT";
	int width=480, height=320;

	cv::Mat srcImg, dstImg, grayImg, maskImg, backImg;

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
	cv::String fileName = "/media/pi/VIDEOS/" + vConf.getTimeNumStr() + ".avi";
	int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
	writer.open(fileName, fourcc, 30, cv::Size(width, height), true);

	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO);
	cv::moveWindow(windowName, 0, -28);
	std::string cascadeName = "/home/pi/raspicam/examples/ObjectDetect/Cascade/haarcascade_car_1.xml";
	cv::CascadeClassifier cascade;
	if (!cascade.load(cascadeName)) {
		std::cout << "Caecade File Read Err" << std::endl;
		return 1;
	}

	VariousDisplay vDis;
	while(true){

		cCap.grab();
		cCap.retrieve(srcImg);
		dstImg = srcImg.clone();
		vDis.findCarBody(dstImg, cascade);
		vDis.setTextMsg(dstImg, (cv::String)vConf.getDateTime());
		writer << srcImg;
		vDis.setCenterMark(dstImg);
		cv::imshow(windowName, dstImg);

		if (cv::waitKey(1) >= 0) break;
	}
	return 0;
}
