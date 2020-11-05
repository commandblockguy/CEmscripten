#include <emscripten.h>

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

#define randInt(min, max) \
((unsigned)random() % ((max) - (min) + 1) + (min))

#define delay(ms) emscripten_sleep(ms)
uint32_t rtc_Time(void);

#define prgm_CleanUp()

#define os_GetCSC() kb_AnyKey()
