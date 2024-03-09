#define MAX_COMMAND_LEN 100

#ifndef BUILT_INS_H
#define BUILT_INS_H

#include "hashmap.h"

void bash(char command[MAX_COMMAND_LEN], char path[][MAX_PATH_LEN]);


#endif