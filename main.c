#include <stdio.h>
#include <stdlib.h>

void terminal(char* user, char* machine);

int main() {
    system("clear");
    terminal("user", "machine");
    return 0;
}

void terminal(char* user, char* machine) {
    char* command;
    printf("\033[1;34m%s@%s-\033[32m[path]\033[1;34m $ \033[0m\n", user, machine);
}