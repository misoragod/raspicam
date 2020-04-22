/*
 * VariousConf.h
 */
#pragma once 
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>


class VariousConf {
public:
	VariousConf();
	virtual ~VariousConf();
	std::string getTimeNumStr();
	std::string getDateTime();
};
