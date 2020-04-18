#pragma once

#include <string>
#include <iomanip>
#include <time.h>


class VariousConf
{
public:
    VariousConf();
    virtual ~VariousConf();
    std::string getTimeNumStr();
    std::string getDateTime();
};
