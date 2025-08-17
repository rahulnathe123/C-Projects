#include "Game.hpp"
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

constexpr int KEY_UP    = 72;
constexpr int KEY_DOWN  = 80;
constexpr int KEY_LEFT  = 75;
constexpr int KEY_RIGHT = 77;

PuzzleGame::PuzzleGame() : emptyRow(PUZZLE_SIZE - 1), emptyCol(PUZZLE_SIZE - 1)
{
    static bool seeded = false;
    if(!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

std::ostream& operator<<(std::ostream& os, const PuzzleGame& pg)
{
    os << "\n------------------\n";
    for (std::size_t i = 0; i < PUZZLE_SIZE; ++i) {
        os << ANSI_COLOR_YELLOW << "| " << ANSI_COLOR_RESET;
        for (std::size_t j = 0; j < PUZZLE_SIZE; ++j) {
            if(pg.arr[i][j] != 0)
                os << ANSI_COLOR_YELLOW << std::setw(2) << pg.arr[i][j] << " | " << ANSI_COLOR_RESET;
            else
                os << ANSI_COLOR_YELLOW << "   | " << ANSI_COLOR_RESET;
        }
        os << "\n";
    }
    os << "------------------\n";
    return os;
}

void PuzzleGame::createMatrix()
{
    std::array<int, PUZZLE_SIZE * PUZZLE_SIZE - 1> nums;
    for(std::size_t i = 0; i < nums.size(); ++i) nums[i] = i + 1;

    std::random_device rd;
    std::mt19937 g(rd());

    do {
        std::shuffle(nums.begin(), nums.end(), g);

        std::size_t idx = 0;
        for(std::size_t i = 0; i < PUZZLE_SIZE; ++i) {
            for(std::size_t j = 0; j < PUZZLE_SIZE; ++j) {
                if(i == PUZZLE_SIZE - 1 && j == PUZZLE_SIZE - 1) {
                    arr[i][j] = 0;
                    emptyRow = i;
                    emptyCol = j;
                } else {
                    arr[i][j] = nums[idx++];
                }
            }
        }
    } while(!isSolvable());
}

bool PuzzleGame::isSolvable() const
{
    std::vector<int> flat;
    for(auto& row : arr)
        for(int x : row)
            if(x != 0) flat.push_back(x);

    int inversions = 0;
    for(size_t i = 0; i < flat.size(); ++i)
        for(size_t j = i + 1; j < flat.size(); ++j)
            if(flat[i] > flat[j]) ++inversions;

    int blankRowFromBottom = PUZZLE_SIZE - emptyRow;
    return (PUZZLE_SIZE % 2 == 0) ?
           ((blankRowFromBottom % 2 == 0) != (inversions % 2 == 0)) :
           (inversions % 2 == 0);
}

bool PuzzleGame::winner() const
{
    int k = 1;
    for(std::size_t i = 0; i < PUZZLE_SIZE; ++i) {
        for(std::size_t j = 0; j < PUZZLE_SIZE; ++j, ++k) {
            if(i == PUZZLE_SIZE - 1 && j == PUZZLE_SIZE - 1) break;
            if(arr[i][j] != k) return false;
        }
    }
    return arr[PUZZLE_SIZE - 1][PUZZLE_SIZE - 1] == 0;
}

int PuzzleGame::readEnteredKey()
{
    char ch = _getch();
    if(ch == 0 || ch == -32) ch = _getch();
    return ch;
}

bool PuzzleGame::shiftUp()
{
    if(emptyRow == 0) 
        return false;
    std::swap(arr[emptyRow][emptyCol], arr[emptyRow - 1][emptyCol]);
    --emptyRow;
    return true;
}

bool PuzzleGame::shiftDown()
{
    if(emptyRow == PUZZLE_SIZE - 1)
        return false;
    std::swap(arr[emptyRow][emptyCol], arr[emptyRow + 1][emptyCol]);
    ++emptyRow;
    return true;
}

bool PuzzleGame::shiftLeft()
{
    if(emptyCol == 0) 
        return false;
    std::swap(arr[emptyRow][emptyCol], arr[emptyRow][emptyCol - 1]);
    --emptyCol;
    return true;
}

bool PuzzleGame::shiftRight()
{
    if(emptyCol == PUZZLE_SIZE - 1) 
        return false;
    std::swap(arr[emptyRow][emptyCol], arr[emptyRow][emptyCol + 1]);
    ++emptyCol;
    return true;
}

void PuzzleGame::gameRule()
{
    system("cls");
    std::cout << "\n\t\tMATRIX PUZZLE\n\n";
    std::cout << ANSI_COLOR_RED << "\t\tRULES OF THE GAME" << ANSI_COLOR_RESET << "\n";
    std::cout << "\t1. Move only one step at a time using arrow keys.\n";
    std::cout << "\t2. Move number into empty space only.\n";
    std::cout << "\t3. Each valid move decreases your moves left by 1.\n";
    std::cout << "\t4. Winning condition: numbers in order 1-15.\n";
    std::cout << "\t5. Exit anytime by pressing 'E' or 'e'.\n\n";

    std::cout << "\tWinning Situation Example:\n";
    std::cout << ANSI_COLOR_YELLOW << "-------------------------\n" << ANSI_COLOR_RESET;
    for(std::size_t i = 0; i < PUZZLE_SIZE; ++i){
        std::cout << ANSI_COLOR_YELLOW << "| " << ANSI_COLOR_RESET;
        for(std::size_t j = 0; j < PUZZLE_SIZE; ++j){
            int val = 4 * i + j + 1;
            std::cout << ANSI_COLOR_YELLOW << std::setw(2) << val << " | " << ANSI_COLOR_RESET;
        }
        std::cout << "\n";
    }
    std::cout << ANSI_COLOR_YELLOW << "-------------------------\n" << ANSI_COLOR_RESET;

    std::cout << "\nPress any key to start...";
    this->readEnteredKey();
}

bool PuzzleGame::operator==(const PuzzleGame& other) const
{
    return arr == other.arr;
}
