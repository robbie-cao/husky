#include "led.h"

void Led_Init(void)
{
  /* Set LED green ON and red OFF default */
  HalLedSet(LED_RED, HAL_LED_MODE_OFF);
  HalLedSet(LED_GREEN, HAL_LED_MODE_ON);
}

/* vim: set ts=2 sw=2 tw=0 list : */
