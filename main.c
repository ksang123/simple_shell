#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "commands/hashmap.h"
#include "commands/built_ins.h"
#include <sys/stat.h>

#define MAX_STRING 200
#define MAX_PATH_LEN 50
#define MAX_PATH_DEPTH 20

void terminal(char* user, char* machine);
int get_names(char* user, char* machine);
int execute(HashMap* map, char* command, char path[][MAX_PATH_LEN]);
char* path_to_string(char str[MAX_PATH_LEN * MAX_PATH_DEPTH],
                     char path[][MAX_PATH_LEN]);
HashMap* create_command_map();
void get_input(char input[MAX_INPUT]);

int main(void) {
    char user[MAX_STRING], machine[MAX_STRING];
    if (get_names(user, machine) == 1) {
        return 1;
    }
    system("clear");
    terminal(user, machine);
    return 0;
}

int get_names(char* user, char* machine) {
    DIR* dir = opendir("./info");
    if (!dir) {
        if (mkdir("./info", 0777) != 0) {
            printf("Failed to create directory.\n");
            return 1;
        }
        printf("Directory created.\n");
    }
    FILE *host_info = fopen("./info/host_info.txt", "r");
    if (host_info == NULL) {
        system("echo $(whoami) > ./info/host_info.txt");
        system("hostname  >> ./info/host_info.txt");
        host_info = fopen("./info/host_info.txt", "r");
    }
    if (fgets(user, MAX_STRING, host_info) == NULL ||
        fgets(machine, MAX_STRING, host_info) == NULL) {
        fclose(host_info);
        system("echo $(whoami) > ./info/host_info.txt");
        system("hostname  >> ./info/host_info.txt");
        host_info = fopen("./info/host_info.txt", "r");
        if (fgets(user, MAX_STRING, host_info) == NULL ||
            fgets(machine, MAX_STRING, host_info) == NULL) {
            printf("\033[0;31mError reading User's and Machine's name\n");
            return 1;
        }
    }
    user[strcspn(user, "\n")] = '\0';
    machine[strcspn(machine, "\n")] = '\0';
    fclose(host_info);
    return 0;
}

void terminal(char* user, char* machine) {
    HashMap* map = create_command_map();
    char path[MAX_PATH_DEPTH][MAX_PATH_LEN] = {"~"}, command[MAX_INPUT],
            str[MAX_PATH_LEN * MAX_PATH_DEPTH];
    printf("\033[1;34m%s@%s-\033[0;32m[%s]\033[1;34m $ \033[0m",
           user, machine, path_to_string(str, path));
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';
    while (execute(map, command, path) == 0) {
        printf("\033[1;34m%s@%s-\033[0;32m[%s]\033[1;34m $ \033[0m",
               user, machine, path_to_string(str, path));
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';
    }
    free_map(map);
}

int execute(HashMap* map, char* command, char path[][MAX_PATH_LEN]) {
    if (strcmp(command, "exit") == 0) {
        return 1;
    }
    char* cmd = strtok(command, " ");;
    void (*func_ptr)(char command[MAX_INPUT], char path[][MAX_PATH_LEN]) = get(map, cmd);
    if (func_ptr == NULL) {
        printf("\033[0;31mError: \033[1;36m%s \033[0;31mdoes not exist\n", cmd);
        return 0;
    }
    (func_ptr)(command, path);
    return 0;
}


char* path_to_string(char* str, char path[][MAX_PATH_LEN]) {
    int index = 0;
    for (int i = 0; i < MAX_PATH_DEPTH; i++) {
        if (strlen(path[i]) == 0) {
            if (index > 0) {
                // Remove the last '/' if the path is not empty
                str[index - 1] = '\0';
            } else {
                str[index] = '\0';
            }
            return str;
        }
        strcpy(&str[index], path[i]);
        index += (int)strlen(path[i]);
        str[index] = '/';
        index++;
    }
    str[index - (index > 0 ? 1 : 0)] = '\0';
    printf("%s", str);
    return str;
}

HashMap* create_command_map() {
    HashMap *map = new_map();
    char cmd[MAX_INPUT] = "bash";
    insert(map, cmd, bash);
    strcpy(cmd, "clear");
    insert(map, cmd, clear);
    return map;
}

void get_command(char command[MAX_INPUT]) {

}

//TODO:
//get commands using ncurses
//add default commands:
//rm-rmdir will require confirmation / [y/N] type
//add external commands
