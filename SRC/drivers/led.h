#ifndef __LED_H__
#define __LED_H__

#include "hal_led.h"

#define LED_RED                   HAL_LED_1
#define LED_GREEN                 HAL_LED_1     // Battery
#define LED_BLUE                  HAL_LED_2     // BLE

#define LED_BLINK_PERCENT         1       /* Duty cycle D% */
#define LED_BLINK_PERIOD_FAST     1000    /* 1/1 HZ */
#define LED_BLINK_PERIOD_MEDIUM   2000    /* 1/2 HZ */
#define LED_BLINK_PERIOD_SLOW     4000    /* 1/4 HZ */


#define LED_ON(C)              HalLedSet(LED_##C, HAL_LED_MODE_ON)
#define LED_OFF(C)             HalLedSet(LED_##C, HAL_LED_MODE_OFF)
#define LED_TOGGLE(C)          HalLedSet(LED_##C, HAL_LED_MODE_TOGGLE)
#define LED_BLINK_FAST(C)      do {                                        \
                                 HalLedSet(LED_##C, HAL_LED_MODE_BLINK);   \
                                 HalLedBlink(LED_##C,                      \
                                     0,  /* Continuous */                  \
                                     LED_BLINK_PERCENT,                    \
                                     LED_BLINK_PERIOD_FAST);               \
                               } while (0)
#define LED_BLINK_MEDIUM(C)    do {                                        \
                                 HalLedSet(LED_##C, HAL_LED_MODE_BLINK);   \
                                 HalLedBlink(LED_##C,                      \
                                     0,  /* Continuous */                  \
                                     LED_BLINK_PERCENT,                    \
                                     LED_BLINK_PERIOD_MEDIUM);             \
                               } while (0)
#define LED_BLINK_SLOW(C)      do {                                        \
                                 HalLedSet(LED_##C, HAL_LED_MODE_BLINK);   \
                                 HalLedBlink(LED_##C,                      \
                                     0,  /* Continuous */                  \
                                     LED_BLINK_PERCENT,                    \
                                     LED_BLINK_PERIOD_SLOW);               \
                               } while (0)


#define LED_SLEEP()            do {                                        \
                                 HalLedEnterSleep();                       \
                               } while (0)

#define LED_WAKEUP()           do {                                        \
                                 HalLedExitSleep();                        \
                               } while (0)


void Led_Init(void);

#endif /* __LED_H__ */

/* vim: set ts=2 sw=2 tw=0 list : */
