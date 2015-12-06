#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define interfaceScreenSize 8
#define gameOptionSize  4
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
void printGameOption(void);
int getGameOption(void);
int getMove(char *moveType);

#endif // GAME_H_INCLUDED
