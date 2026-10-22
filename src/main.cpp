#include <iostream>
#include <windows.h>

#include "../include/Pokemon.h"
#include "../include/Box.h"
#include "../include/ConsoleUI.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    );
    HomeMenuLoad();
    return 0;
}