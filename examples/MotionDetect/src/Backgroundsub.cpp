/*
 * Backgroundsub.cpp
 */

#include "Backgroundsub.h"

Backgroundsub::Backgroundsub() {
	bgSub = cv::createBackgroundSubtractorMOG2();
}

Backgroundsub::~Backgroundsub() {
}

void Backgroundsub::createDiff(cv::Mat &img, cv::Mat &maskImg){
	cv::Mat outputImg;
	//重ねる背景色
	cv::Mat bgImg(cv::Size(img.cols, img.rows), CV_8UC3, cv::Scalar(255, 0, 250));

	bgSub->apply(img, maskImg, true ? -1 : 0);
	cv::medianBlur(maskImg, maskImg, 11);
	cv::threshold(maskImg, maskImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU );
	//差分画像を重ねる
	cv::bitwise_and(bgImg, img, outputImg, maskImg);
	outputImg.copyTo(img, maskImg);
}

void Backgroundsub::showImg(cv::Mat &img){
	//cv::imshow("OUTPUT", outputImg);
	//cv::imshow("BG", bgImg);
	//cv::imshow("MASK", maskImg);
}

bool Backgroundsub::doWatchChange(cv::Mat &maskImg, int threshold){
	int intensity, black=0, white=0;
	for(int y=0; y < maskImg.rows; y++){
		for(int x=0; x < maskImg.cols; x++){
			intensity = maskImg.at<unsigned char>(y, x);
			if(intensity == 0){
				black++;
			}
			else{
				white++;
			}
		}
	}
	bool result = ((double)white/black)*100 > threshold ? true : false;
	if(((double)white/black)*100 > 100) result = false;
	return result;
}
void Backgroundsub::setTextMsg(cv::Mat &img, cv::String str){
	cv::Mat overlay, output;
	double alpha = 0.5;
	img.copyTo(overlay);
	cv::rectangle(overlay, cv::Rect(5, 5, 200, 30), cv::Scalar(192, 192, 192), -1);
	cv::addWeighted(overlay, alpha, img, 1-alpha, 0, img);
	cv::putText(img, str, cv::Point(10,25), CV_FONT_NORMAL, 0.5, cv::Scalar::all(32), 1, cv::LINE_AA);
}

