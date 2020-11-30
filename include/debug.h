#ifndef H_DEBUG
#define H_DEBUG

#include <stdio.h>

#define dbg_printf printf
#define dbg_sprintf(ignore, ...) printf(__VA_ARGS__)

#endif
