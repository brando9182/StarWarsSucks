//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
/*-----------------------------Includes--------------------------------------*/
#include <Timers.h>

/*---------------------------Definitions-------------------------------------*/
#define DEBOUNCE_LENGTH  2  //min stability period, measured in milliseconds
#define TIMER_DEBOUNCE   1

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
static uint8_t button_state_reported = 0;
static bool button_actively_debouncing = false;

/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_button (void){
  pinMode(BUTTON_PIN, INPUT);
  TMRArd_SetTimer(TIMER_DEBOUNCE, DEBOUNCE_LENGTH);
}

//CONFIRMED WORKING (3/3), NHS
uint8_t button_state (void) {
  updateButton();
  return button_state_reported;
}

/*-----------------------------Helper Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
static void updateButton (void) {
  if ((button_state_reported != digitalRead(BUTTON_PIN)) & !button_actively_debouncing) {
    TMRArd_InitTimer(TIMER_DEBOUNCE, DEBOUNCE_LENGTH);
    button_actively_debouncing = true;
  }
  if (TMRArd_IsTimerExpired(TIMER_DEBOUNCE)) {
    button_state_reported = !digitalRead(BUTTON_PIN);
    button_actively_debouncing = false;
  }
}
