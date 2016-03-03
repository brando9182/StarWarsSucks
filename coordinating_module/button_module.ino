/*-----------------------------Includes--------------------------------------*/
#include <Timers.h>

/*---------------------------Definitions-------------------------------------*/
#define DEBOUNCE_LENGTH  2  //min stability period, measured in milliseconds
#define TIMER_DEBOUNCE   1

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
uint8_t button_state_reported = 0;
bool button_actively_debouncing = false;

/*-----------------------------Public Functions------------------------------*/
void init_button (void){
  pinMode(BUTTON_PIN, INPUT);
  TMRArd_SetTimer(TIMER_DEBOUNCE, DEBOUNCE_LENGTH);
}

void update_button (void) {
  if ((button_state_reported != digitalRead(BUTTON_PIN)) & !button_actively_debouncing) {
    TMRArd_InitTimer(TIMER_DEBOUNCE, DEBOUNCE_LENGTH);
    button_actively_debouncing = true;
  }
  if (TMRArd_IsTimerExpired(TIMER_DEBOUNCE)) {
    button_state_reported = !digitalRead(BUTTON_PIN);
    button_actively_debouncing = false;
  }
}

//added update button here for a simpler interface
uint8_t button_state_report (void) {
  update_button();
  return button_state_reported;
}


