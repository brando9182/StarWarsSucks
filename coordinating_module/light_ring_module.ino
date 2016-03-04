//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
/*-----------------------------Includes--------------------------------------*/
#include <Timers.h>
#include <Adafruit_NeoPixel.h>

/*---------------------------Definitions-------------------------------------*/
#define INDICATOR_LED_NUM   16
#define INDICATOR_PULSE     5
#define TIMER_INDICATOR     0

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
static uint8_t indicator_pulse_dir = 0;
static uint8_t indicator_pulse_curr = 10;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(INDICATOR_LED_NUM, INDICATOR_PIN, NEO_GRBW + NEO_KHZ800);

/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_light_ring (void) {
  pixels.begin();
  TMRArd_InitTimer(TIMER_INDICATOR, INDICATOR_PULSE);
}

//CONFIRMED WORKING (3/3), NHS
void indicator_LED_on(uint8_t LED_num){
  pixels.setPixelColor(LED_num, pixels.Color(0,0,0,50));
  pixels.show();
}

//CONFIRMED WORKING (3/3), NHS
void indicator_blanket_set (uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for (int i = 0; i < INDICATOR_LED_NUM; i++) {
    pixels.setPixelColor(i, pixels.Color(r,g,b,w));
  }
  pixels.show();
}

//CONFIRMED WORKING (3/3), NHS
void indicator_pulse (void) {
  if (TMRArd_IsTimerExpired(TIMER_INDICATOR)) {
    if (indicator_pulse_curr >= 250) {
      indicator_pulse_dir = 1;
    }
    if (indicator_pulse_curr <= 4) {
      indicator_pulse_dir = 0;
    }
    if (indicator_pulse_dir) {
      indicator_pulse_curr--;
    } else {
      indicator_pulse_curr++;
    }
    indicator_blanket_set(indicator_pulse_curr, 0, indicator_pulse_curr, 0);
    TMRArd_ClearTimerExpired(TIMER_INDICATOR);
  }
}

//CONFIRMED WORKING (3/3), NHS
void indicator_clear (void) {
  indicator_blanket_set(0, 0, 0, 0);
  pixels.show();
}
