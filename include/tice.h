#ifndef H_TICE
#define H_TICE

#include <emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

#define randInt(min, max) \
((unsigned)random() % ((max) - (min) + 1) + (min))

#define delay(ms) emscripten_sleep(ms)
uint32_t rtc_Time(void);

#define prgm_CleanUp()

#define os_GetCSC() kb_AnyKey()

bool set_timer_Control(int x);
uint32_t get_timer_Control(void);
#define timer_Control for(int dummy_timer_Control = -1; dummy_timer_Control == -1 ? 1 : set_timer_Control(dummy_timer_Control);) dummy_timer_Control

#define TIMER1_ENABLE            (1<<0)  /* Enables Timer 1                                        */
#define TIMER1_DISABLE           (0<<0)  /* Disables Timer 1                                       */
#define TIMER1_32K               (1<<1)  /* Use the 32K clock for timer 1                          */
#define TIMER1_CPU               (0<<1)  /* Use the CPU clock rate for timer 1                     */
#define TIMER1_0INT              (1<<2)  /* Enable an interrupt when 0 is reached for the timer 1  */
#define TIMER1_NOINT             (0<<2)  /* Disable interrupts for the timer 1                     */
#define TIMER1_UP                (1<<9)  /* Timer 1 counts up                                      */
#define TIMER1_DOWN              (0<<9)  /* Timer 1 counts down                                    */

#define TIMER2_ENABLE            (1<<3)  /* Enables Timer 2                                        */
#define TIMER2_DISABLE           (0<<3)  /* Disables Timer 2                                       */
#define TIMER2_32K               (1<<4)  /* Use the 32K clock for timer 2                          */
#define TIMER2_CPU               (0<<4)  /* Use the CPU clock rate for timer 2                     */
#define TIMER2_0INT              (1<<5)  /* Enable an interrupt when 0 is reached for the timer 2  */
#define TIMER2_NOINT             (0<<5)  /* Disable interrupts for the timer 2                     */
#define TIMER2_UP                (1<<10) /* Timer 2 counts up                                      */
#define TIMER2_DOWN              (0<<10) /* Timer 2 counts down                                    */

#define TIMER3_ENABLE            (1<<6)  /* Enables Timer 3                                        */
#define TIMER3_DISABLE           (0<<6)  /* Disables Timer 3                                       */
#define TIMER3_32K               (1<<7)  /* Use the 32K clock for timer 3                          */
#define TIMER3_CPU               (0<<7)  /* Use the CPU clock rate for timer 3                     */
#define TIMER3_0INT              (1<<8)  /* Enable an interrupt when 0 is reached for the timer 3  */
#define TIMER3_NOINT             (0<<8)  /* Disable interrupts for the timer 3                     */
#define TIMER3_UP                (1<<11) /* Timer 3 counts up                                      */
#define TIMER3_DOWN              (0<<11) /* Timer 3 counts down                                    */

/* These defines can be used to check the status of the timer */
#define TIMER1_MATCH1            (1<<0)  /* Timer 1 hit the first match value                      */
#define TIMER1_MATCH2            (1<<1)  /* Timer 1 hit the second match value                     */
#define TIMER1_RELOADED          (1<<2)  /* Timer 1 was reloaded (Needs TIMER1_0INT enabled)       */

#define TIMER2_MATCH1            (1<<3)  /* Timer 2 hit the first match value                      */
#define TIMER2_MATCH2            (1<<4)  /* Timer 2 hit the second match value                     */
#define TIMER2_RELOADED          (1<<5)  /* Timer 2 was reloaded (Needs TIMER2_0INT enabled)       */

#define TIMER3_MATCH1            (1<<6)  /* Timer 3 hit the first match value                      */
#define TIMER3_MATCH2            (1<<7)  /* Timer 3 hit the second match value                     */
#define TIMER3_RELOADED          (1<<8)  /* Timer 3 was reloaded (Needs TIMER3_0INT enabled)       */

uint32_t get_timer_Counter(uint8_t n);
void set_timer_Counter(uint8_t n, uint32_t x);
void set_timer_ReloadValue(uint8_t n, uint32_t x);
#define timer_1_Counter get_timer_Counter(1)
#define timer_2_Counter get_timer_Counter(2)
#define timer_3_Counter get_timer_Counter(3)

#define TIMER_32K               1  /**< Use the 32K clock for timer                         */
#define TIMER_CPU               0  /**< Use the CPU clock rate for timer                    */
#define TIMER_0INT              1  /**< Enable an interrupt when 0 is reached for the timer */
#define TIMER_NOINT             0  /**< Disable interrupts for the timer                    */
#define TIMER_UP                1  /**< Timer counts up                                     */
#define TIMER_DOWN              0  /**< Timer counts down                                   */

#define TIMER_MATCH1            (1<<0)  /**< Timer hit the first match value                */
#define TIMER_MATCH2            (1<<1)  /**< Timer hit the second match value               */
#define TIMER_RELOADED          (1<<2)  /**< Timer was reloaded (Needs TIMER_0INT enabled)  */

#define timer_Enable(n, rate, int, dir) (set_timer_Control(get_timer_Control() & ~(0x7 << 3 * ((n) - 1) | 1 << (n) + 8) | (1 | (rate) << 1 | (int) << 2 | (dir) << 9) << 3 * ((n) - 1)))
#define timer_Disable(n) (set_timer_Control(get_timer_Control() & ~(1 << 3 * ((n) - 1))))
void timer_AckInterrupt(uint8_t n, uint8_t type);
uint8_t timer_CheckInterrupt(uint8_t n, uint8_t type);

#ifdef __cplusplus
}
#endif

#endif
