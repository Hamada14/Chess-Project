#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define interfaceScreenSize 8
#define gameOptionSize  4
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
/*#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif*/
enum Turn {     firstPlayer,
                          secondPlayer,
};
char *interfaceScreen[] = {" ________   ___  ___   _______    ________    ________ ",
                                                "|\\   ____\\ |\\  \\|\\  \\ |\\  ___ \\  |\\   ____\\  |\\   ____\\",
                                                "\\ \\  \\___| \\ \\  \\\\\\  \\\\ \\   __/| \\ \\  \\___|_ \\ \\  \\___|_",
                                                " \\ \\  \\     \\ \\   __  \\\\ \\  \\_|/__\\ \\_____  \\ \\ \\_____  \\",
                                                "  \\ \\  \\____ \\ \\  \\ \\  \\\\ \\  \\_|\\ \\\\|____|\\  \\ \\|____|\\  \\",
                                                "   \\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\ ____\\_\\  \\  ____\\_\\  \\",
                                                "    \\|_______| \\|__|\\|__| \\|_______||\\_________\\|\\_________\\",
                                                "                                    \\|_________|\\|_________|"};
char *gameOption[] ={"Start a new Game",
                                        "Load last Game",
                                        "Help",
                                        "Setting",
};

void printInterface(void);
void printLogo(void);
void clearScreen(void);
void printGameOption(void);
int getGameOption(void);
int getMove(char *moveType);

#endif // GAME_H_INCLUDED
