#include <iostream>
#include <unistd.h>
#include <termios.h>

void initSettings();
void restoreSettings();
char getKey();