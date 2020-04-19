/*
 * VariousConf.h
 */
#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>

class VariousConf {
public:
	VariousConf();
	virtual ~VariousConf();
	std::string getTimeNumStr();
	std::string getDateTime();
};

