#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 200
#define MAX_PATH_LEN 50
#define MAX_PATH_DEPTH 20

void terminal(char* user, char* machine);
int get_names(char* user, char* machine);
int execute(char* command, char path[][MAX_PATH_LEN]);
char* path_to_string(char str[MAX_PATH_LEN * MAX_PATH_DEPTH],
                     char path[][MAX_PATH_LEN]);

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
    char path[MAX_PATH_DEPTH][MAX_PATH_LEN] = {"~"}, command[200],
            str[MAX_PATH_LEN * MAX_PATH_DEPTH];
    printf("\033[1;34m%s@%s-\033[32m[%s]\033[1;34m $ \033[0m",
           user, machine, path_to_string(str, path));
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';
    while (execute(command, path) == 0) {
        printf("\033[1;34m%s@%s-\033[32m[%s]\033[1;34m $ \033[0m",
               user, machine, path_to_string(str, path));
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';
    }
}

int execute(char* command, char path[][MAX_PATH_LEN]) {
    if (strcmp(command, "exit") == 0) {
        return 1;
    }
    if (strncmp(command, "bash", 4) == 0) {
        system(&command[5]);
    }
    return 0;
}

char* path_to_string(char* str, char path[][MAX_PATH_LEN]) {
    int index = 0;
    for (int i = 0; i < MAX_PATH_DEPTH; i++) {
        if (strlen(path[i]) == 0) {
            str[index] = '\0';
            return str;
        }
        strcpy(&str[index], path[i]);
        index += (int)strlen(path[i]);
        str[index] = '/';
        index++;
    }
    str[index] = '\0';
    return str;
}
