#include "../includes/terminalSetting.h"

struct termios oldSettings, newSettings;

void initSettings()
{
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
}

void restoreSettings()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}

char getKey()
{
    char in;
    std::cin >> in;
    return in;
}