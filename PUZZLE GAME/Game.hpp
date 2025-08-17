#ifndef _GAME__HPP
#define _GAME__HPP

#include <iostream>
#include <array>
#include <conio.h>
#include <iomanip>

constexpr const char* ANSI_COLOR_RED     = "\x1b[31m";
constexpr const char* ANSI_COLOR_GREEN   = "\x1b[32m";
constexpr const char* ANSI_COLOR_YELLOW  = "\x1b[33m";
constexpr const char* ANSI_COLOR_BLUE    = "\x1b[34m";
constexpr const char* ANSI_COLOR_MAGNETA = "\x1b[35m";
constexpr const char* ANSI_COLOR_CYAN    = "\x1b[36m";
constexpr const char* ANSI_COLOR_RESET   = "\x1b[0m";

constexpr int PUZZLE_SIZE = 4;

class PuzzleGame
{
    friend std::ostream& operator<<(std::ostream&, const PuzzleGame&);

private:
    std::array<std::array<int, PUZZLE_SIZE>, PUZZLE_SIZE> arr;
    std::size_t emptyRow;
    std::size_t emptyCol;

    bool isSolvable() const;

public:
    PuzzleGame();
    void createMatrix();
    bool winner() const;
    bool shiftUp();
    bool shiftDown();
    bool shiftRight();
    bool shiftLeft();
    void gameRule();
    int readEnteredKey();
    bool operator==(const PuzzleGame& other) const;
    ~PuzzleGame() = default;
};

#endif
