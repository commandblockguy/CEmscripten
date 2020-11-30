#ifndef H_DEBUG
#define H_DEBUG

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define dbg_printf printf
#define dbg_sprintf(ignore, ...) printf(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
