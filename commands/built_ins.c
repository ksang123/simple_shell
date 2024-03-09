#include <stdlib.h>
#include "hashmap.h"

void bash(char command[MAX_COMMAND_LEN], char path[][MAX_PATH_LEN]) {
    //TODO: deal with the working directory
    system(&command[5]);
}