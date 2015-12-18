#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED
bool undoErrorPrint;
bool redoErrorPrint;
void saveGame(void);
bool undo();
void loadGame(void);
void redo();
#endif // SAVE_H_INCLUDED
