/**
 * main program with pilot and robot modules
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "robot_app/copilot.h"
#include "robot_app/robot.h"
#include "utils.h"

/**
 * @mainpage Robot application mission 2.
 * This projects aims to move a robot along a predefined trajectory.
 */

/**
 * @enum process_state_t
 * @brief indicate the process state management for the application.
 */
typedef enum {
  STOPPED = 0, /**< Process is stopped */
  ALIVE,      /**< Process is running */
} process_state_t;

/** @brief Waiting time between two encoder's scans (in microseconds).
 * Adapt according to your cpu and simulator.
 */
#define DELAY 1000000

/** @brief Max scanning's attempt to check if a move is finished.
 * Adapt according your move
 */
#define ENCODERS_SCAN_NB 1000

#define STEPS_NUMBER 6 /**< number of steps (or moves) in the path */

/*Number of moves*/

move_t path[] = {
    {FORWARD,{5},17.24 },
    {ROTATION,{RIGHT},20 },
    {FORWARD,{5},50 },
    {ROTATION,{RIGHT},20 },
    {FORWARD,{5},50 },
    {ROTATION,{LEFT},20 }      
};



move_t* p_path = NULL;

// declaration of private functions
static void app_loop(void);

/**
 * @brief Global variable used for program clean exit
 */
static process_state_t running = ALIVE;

/**
 * @brief Function for CTRL+C signal management
 */
static void sigint_handler(int dummy) { running = STOPPED; }

int main(void)
{
  /*Initialisation of the number of move*/
  int num_moves = (int)(sizeof(path) / sizeof(move_t));

  /*Initialisation of the path*/
  p_path = (move_t*)calloc(num_moves,sizeof(move_t));

  if(p_path == NULL){
    fprintf(stdout,"Error of allocation");
    return EXIT_FAILURE;
  }
  p_path = memcpy(p_path,path,num_moves*sizeof(move_t));

  /* start the robot simulator and check its good starting */
  int status = robot_start();
  if (status != 0)
  {
    printf("Pb lancement mrPizz\n");
    fflush(stdout);
    return EXIT_FAILURE;
  }
  
  printf("**** Version démo RM2 **** \n");
  printf("**** par JDL **** \n");
  printf("Ctrl+C pour quitter\n");
  fflush(stdout);

  /* Ctrl+C to stop the program. */
  signal(SIGINT, sigint_handler);

  /*Initialisation of the path*/
  setPath(p_path,num_moves);

  app_loop();
  /* close the robot simulator */
  robot_close();
  return EXIT_SUCCESS;
}

/**
 * @brief Main loop for the application.
 * Send commands to the pilot and display robot's status with a specific period.
 */

static void app_loop()
{
  /*Start running the path that we programmed in copilot*/
  copilot_start_path();
  robot_status_t my_status;
  /*Have to define the random path from copilot*/
  while (running){

    /*Check if the value of the sensors*/
    my_status = robot_get_status();
    /* fprintf(stdout, "codeurs: g = %d, d = %d\n", my_status.left_encoder,
            my_status.right_encoder);
    fprintf(stdout, "proxy: g = %d, c = %d, d = %d\n", my_status.left_sensor,
            my_status.center_sensor, my_status.right_sensor);
    fprintf(stdout, "batterie: %d %%\n", my_status.battery); */
    /* Encoders polling */
    for (int i = 0; i < ENCODERS_SCAN_NB; i++){
      usleep(DELAY);
      path_status_t statut_path = copilot_stop_at_step_completion();
      if(statut_path == PATH_COMPLETE){
        free(p_path);  
        running = STOPPED;
        fprintf(stdout,"J'ai fait tout le chemin");
        break; 
      }
    }
   
  
  }
}
