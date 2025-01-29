#ifndef COPILOT_H
#define COPILOT_H

#include <stdbool.h>
#include "pilot.h"

/*Allow to describe the status of the full movement, if all of move_t[] is done or not*/
typedef enum{
    PATH_COMPLETE,
    PATH_MOVING, 
    PATH_ERROR
}path_status_t;


bool copilot_is_path_complete();
void copilot_start_path();
void setPath(move_t* a_path, int num_moves);
path_status_t copilot_stop_at_step_completion();

#endif // COPILOT_H