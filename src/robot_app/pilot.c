#include <stdio.h>
#include "robot.h"
#include "pilot.h"

#define DISTANCE_FORWARD 200 // distance to move forward 
#define DISTANCE_TURN 232 // distance of the encoder to make 90°


static move_status_t robot_moving = MOVE_DONE;
static int target_pos; 
static wheel_t reference_wheel; 



void pilot_start_move(move_t a_move){
    static int compteur = 0;
    if(robot_moving == MOVE_DONE){
        fprintf(stdout,"Move started\n");
        switch(a_move.move_type){
            case FORWARD:
                
                reference_wheel = LEFT_WHEEL;
                target_pos = robot_get_wheel_position(reference_wheel)+ a_move.range.distance*DISTANCE_FORWARD;
                robot_set_speed(a_move.speed,a_move.speed);
                robot_moving = MOVE_FORWARD;
                compteur ++;
                fprintf(stdout,"Forward %d \n",compteur);
                break;
                
            case ROTATION:
            /*We define the target for the rotation in advance*/      
                switch(a_move.range.angle){
                    case RIGHT:
                        reference_wheel = LEFT_WHEEL;
                        target_pos = robot_get_wheel_position(reference_wheel) + DISTANCE_TURN;
                        robot_set_speed(a_move.speed,-a_move.speed);
                        robot_moving = MOVE_ROTATION;
                        compteur ++;
                        fprintf(stdout,"Right %d\n",compteur);
                        break;
                    case LEFT:
                        reference_wheel = RIGHT_WHEEL;
                        target_pos = robot_get_wheel_position(reference_wheel) + DISTANCE_TURN;
                        robot_set_speed(-a_move.speed,a_move.speed);
                        robot_moving = MOVE_ROTATION;
                        compteur ++;
                        fprintf(stdout,"Left %d\n",compteur);
                        break;
                    case U_TURN:
                        reference_wheel = RIGHT_WHEEL;
                        target_pos = robot_get_wheel_position(reference_wheel) + DISTANCE_TURN*2;
                        robot_set_speed(-a_move.speed,a_move.speed);
                        robot_moving = MOVE_ROTATION;
                        compteur ++;
                        fprintf(stdout,"U_turn %d\n",compteur);
                        break;
                    default:
                        fprintf(stdout,"Error of action rotation\n");
                        break;
                }break;
            default:
                fprintf(stdout,"Error of action move \n");
                break;
            
        }
    }
}

move_status_t pilot_get_status(){
    return robot_moving;
}


move_status_t pilot_stop_at_target(){
    int current_pos = robot_get_wheel_position(reference_wheel);
    if(current_pos >= target_pos){
        robot_set_speed(0,0);
        robot_moving = MOVE_DONE;
    }
    return robot_moving;
}