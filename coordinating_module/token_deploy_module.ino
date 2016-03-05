//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
/*-----------------------------Includes--------------------------------------*/
#include <Servo.h>

/*---------------------------Definitions-------------------------------------*/
#define DEPLOYMENT_MAX_TOKENS       12

/*---------------------------Constants---------------------------------------*/
//not zero indexed
static uint8_t slots[DEPLOYMENT_MAX_TOKENS+1] = {120, 114, 106, 98, 91, 85, 78, 70, 64, 21, 14, 7, 0};
static Servo deployment_servo;

/*---------------------------Module Variables--------------------------------*/
uint8_t deployment_position_curr = 0;

/*----------------------------Public Functions-------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_token_deploy (void) {
  deployment_servo.attach(DEPLOYMENT_SERVO_PIN);
}

//CONFIRMED WORKING (3/3), NHS
void deploy_tokens (uint8_t numTokensToDeploy) {
  if (numTokensToDeploy > deployment_tokens_remaining()) numTokensToDeploy = deployment_tokens_remaining();
  deployment_servo.write (slots [deployment_position_curr + numTokensToDeploy]);
  deployment_position_curr = deployment_position_curr + numTokensToDeploy;
}

//CONFIRMED WORKING (3/3), NHS
uint8_t deployment_tokens_remaining (void) {
  return (DEPLOYMENT_MAX_TOKENS - deployment_position_curr);
}

//CONFIRMED WORKING (3/3), NHS
void deployment_home (void) {
  deployment_servo.write(slots[0]);
  deployment_position_curr = 0;
}
