#include <stdio.h>
#include <stdlib.h>

void print_terminal(char* user, char* machine);
void terminal();

int main() {
    #if defined(_WIN64)
        system(".\\ansicon\\x64\\ansicon.exe > NUL 2>&1");
    #endif
    #if defined(_WIN32)
    system(".\\ansicon\\x86\\ansicon.exe > NUL 2>&1");
    #endif
    terminal();
    return 0;
}

void terminal() {
    print_terminal("user", "machine");
}

void print_terminal(char* user, char* machine) {
    printf("\033[1;34m%s@m%s-\033[32m[path]\033[1;34m $ \033[0m", user, machine);
}