
#ifndef PROJECT_MINESWEEPERBOARD_H
#define PROJECT_MINESWEEPERBOARD_H
#include "field.h"
enum GameMode  { DEBUG, EASY=1, NORMAL=2, HARD=3 };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };
class MinesweeperBoard
{
public:
    MinesweeperBoard(int width=10, int height=10, GameMode mode=DEBUG);
    ~MinesweeperBoard();
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int x, int y) const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    char getFieldInfo(int x, int y) const;
    GameState getGameState() const;

private:
    Field board_[100][100];
    int width_;
    int height_;
    int number_of_mines_;
    GameState game_status;
    GameMode mode_;
    bool isFirstMove();
    bool whenWin() const;

};
#endif //PROJECT_MINESWEEPERBOARD_H
