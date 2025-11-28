#ifndef __TOOL_H__
#define __TOOL_H__

#include <Adafruit_INA228.h>

void initValueFromEEPROM();

double getCompensation(Adafruit_INA228 *ina228);

#endif
