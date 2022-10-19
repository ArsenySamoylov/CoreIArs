#ifndef ZAEBET_PARSIT_ETY_XYUNU
#define ZAEBET_PARSIT_ETY_XYUNU

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Config.h"
#include "Architecture.h"

cmd_code      CompareLineWithComands(const char* line);
reg_arg       IsReg (const char* line);

int stricmp (const char *s1, const char *s2 );

#endif