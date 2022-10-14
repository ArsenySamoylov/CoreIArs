#ifndef ZAEBET_PARSIT_ETY_XYUNU
#define ZAEBET_PARSIT_ETY_XYUNU

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Config.h"

comands      CompareLineWithComands(const char* line);
int          CompareWithRegister   (const char* reg);
cpu_register IsReg (const char* line);

#endif