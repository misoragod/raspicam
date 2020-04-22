/*
 * VariousConf.cpp
 */

#include "VariousConf.h"

VariousConf::VariousConf() {
}

VariousConf::~VariousConf() {
}

std::string VariousConf::getTimeNumStr(){
	std::ostringstream oss;
	time_t nowTime = time(nullptr);
	oss << nowTime;
	return oss.str();
}
std::string VariousConf::getDateTime(){
	//現在日時を取得する
	time_t nowTime = time(nullptr);
	//形式を変換する
	const tm* lTime = localtime(&nowTime);
	std::ostringstream oss;
	oss << 20
	   << lTime->tm_year-100
	   << "-"
	   << std::setw(2)
	   << std::setfill('0')
	   <<lTime->tm_mon+1
	   << "-"
	   << std::setw(2)
	   << std::setfill('0')
	   << lTime->tm_mday
	   << " "
	   << std::setw(2)
	   << std::setfill('0')
	   << lTime->tm_hour
	   << ":"
	   << std::setw(2)
	   << std::setfill('0')
	   << lTime->tm_min
	   << ":"
	   << std::setw(2)
	   << std::setfill('0')
	   <<lTime->tm_sec;
	return oss.str();
}


