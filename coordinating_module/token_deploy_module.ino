/*-----------------------------Includes--------------------------------------*/
#include <Servo.h>

/*---------------------------Definitions-------------------------------------*/
#define DEPLOYMENT_SERVO_PIN            10
#define DEPLOYMENT_MAX_TOKENS           12

/*---------------------------Constants---------------------------------------*/
static uint8_t slots[DEPLOYMENT_MAX_TOKENS] = {88, 81, 73, 65, 58, 51, 44, 36, 29, 21, 14, 7};
Servo deployment_servo;

/*---------------------------Module Variables--------------------------------*/
uint8_t deployment_position_curr = 0;

/*----------------------------Public Functions-------------------------------*/
void init_deploy_tokens (void) {
  deployment_servo.attach(DEPLOYMENT_SERVO_PIN);
}

void deploy_tokens (uint8_t numTokensToDeploy) {
  if (numTokensToDeploy > deployment_tokens_remaining()) numTokensToDeploy = deployment_tokens_remaining();
  deployment_servo.write (slots [deployment_position_curr + numTokensToDeploy]);
  deployment_position_curr = deployment_position_curr + numTokensToDeploy;
}

uint8_t deployment_tokens_remaining (void) {
  return (DEPLOYMENT_MAX_TOKENS - deployment_position_curr - 1);
}

//Brings the deployment mechanism to its home position (in preparation for being filled up with more chips).
void deployment_home (void) {
  deployment_servo.write(slots[0]);
  deployment_position_curr = 0;
}
