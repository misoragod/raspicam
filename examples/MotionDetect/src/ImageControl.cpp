/*
 * ImageControl.cpp
 */

#include "ImageControl.h"

ImageControl::ImageControl() {

}

ImageControl::~ImageControl() {
}

bool ImageControl::doWatchChange(cv::Mat &maskImg, int threshold){
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
	return result;
}

void ImageControl::setDateTime(cv::Mat &img){

}
