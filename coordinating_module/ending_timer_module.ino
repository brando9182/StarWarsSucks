/*-----------------------------Includes--------------------------------------*/
#include <Timers.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

/*---------------------------Definitions-------------------------------------*/
#define TIMER_TIMEOUT   3
#define TIMEOUT_PULSE   120000  //2 minutes in ms

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
void init_ending_timer (void) {
  TMRArd_SetTimer(TIMER_TIMEOUT, TIMEOUT_PULSE);
}

void start_ending_timer (void) {
  TMRArd_InitTimer(TIMER_TIMEOUT, TIMEOUT_PULSE);
}

bool competition_ended (void) {
  if (TMRArd_IsTimerExpired(TIMER_TIMEOUT)) return true;
  return false;
}
