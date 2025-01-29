// robot.c

#include "robot.h"
#include "mrpiz.h"
#include <errno.h>
#include <stdio.h>

int robot_start(void) {
  int result = 0;
  mrpiz_init();

  // @todo

  return result;
}

//Setting the speed of the robot for the wheels
void robot_set_speed(speed_pct_t left, speed_pct_t right) {
  // @todo
  /*On vérifie que la valeur de speed est comprise entre -100 et 100*/
  if(left<-100 || left>100 || right<-100 || right>100){
    printf("Speed left is %d and right is %d, please chose between -100 and 100\n.",left,right);
  }
  mrpiz_motor_set(MRPIZ_MOTOR_LEFT,left);
  mrpiz_motor_set(MRPIZ_MOTOR_RIGHT,right);
}

//We give the wheel's value depending on the encoder of left or right motor
/*Allow to give the encoder position with a upper machine language*/ 
int robot_get_wheel_position(wheel_t wheel_id) {
  // @todo
  int position =0; 
  switch(wheel_id){
    case LEFT_WHEEL: 
      position = mrpiz_motor_encoder_get(MRPIZ_MOTOR_LEFT);
      break; 
    case RIGHT_WHEEL:
      position = mrpiz_motor_encoder_get(MRPIZ_MOTOR_RIGHT);
      break;
    default : 
      position = -1; 
      break; 
  }
  return position;

}

//We reset the position of the wheels 
void robot_reset_wheel_pos(void) {
  // @todo
  mrpiz_motor_encoder_reset(MRPIZ_MOTOR_LEFT);
  mrpiz_motor_encoder_reset(MRPIZ_MOTOR_RIGHT);
}

robot_status_t robot_get_status(void) {
  // @todo 
  robot_status_t robot_status; 
  robot_status.left_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
  robot_status.right_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);
  robot_status.center_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER);
  robot_status.center_left_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER_LEFT);
  robot_status.center_right_sensor= mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER_RIGHT);
  robot_status.left_encoder = mrpiz_proxy_sensor_get(MRPIZ_MOTOR_LEFT);
  robot_status.right_encoder = mrpiz_proxy_sensor_get(MRPIZ_MOTOR_RIGHT);
  robot_status.battery = mrpiz_battery_level();
  
  return robot_status;
}

void robot_signal_event(notification_t event) {
  // @todo
  switch(event){
    case ROBOT_OK: 
      mrpiz_led_rgb_set(MRPIZ_LED_GREEN); 
      break; 
    case ROBOT_OBSTACLE:
      mrpiz_led_rgb_set(MRPIZ_LED_RED); 
      break; 
    case ROBOT_PROBLEM:
      mrpiz_led_rgb_set(MRPIZ_LED_BLUE); 
      break;
    case ROBOT_OFF:
      mrpiz_led_rgb_set(MRPIZ_LED_OFF); 
      break;
  }
}

void robot_close(void) {
  robot_set_speed(0, 0);
  mrpiz_close();
}
