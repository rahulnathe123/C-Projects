#include <iostream>
#include <limits>
#include "Game.hpp"


constexpr int KEY_UP    = 72;
constexpr int KEY_DOWN  = 80;
constexpr int KEY_LEFT  = 75;
constexpr int KEY_RIGHT = 77;

int main() {
    std::size_t maxTry = 10;
    std::string name;

    std::cout << "\n\nENTER PLAYER NAME: ";
    std::cin >> name;

    bool playAgain = true;

    while(playAgain) {
        PuzzleGame PG;
        PG.createMatrix();
        PG.gameRule();

        std::size_t movesLeft = maxTry;

        while(!PG.winner()) {
            system("cls");

            if(movesLeft == 0) break;

            std::cout << "\n" << ANSI_COLOR_BLUE
                      << "\tPLAYER NAME: " << name 
                      << "  MOVES REMAINING: " << movesLeft << "\n"
                      << ANSI_COLOR_RESET;

            std::cout << PG << std::endl;

            int key = PG.readEnteredKey();

            switch(key) {
                case 'E':
                case 'e':
                    std::cout << ANSI_COLOR_CYAN << "\n\tTHANKS FOR PLAYING !!!" << ANSI_COLOR_RESET << std::endl;
                    return 0;

                case KEY_UP:
                    if(PG.shiftUp()) movesLeft--;
                    break;
                case KEY_DOWN:
                    if(PG.shiftDown()) movesLeft--;
                    break;
                case KEY_RIGHT:
                    if(PG.shiftRight()) movesLeft--;
                    break;
                case KEY_LEFT:
                    if(PG.shiftLeft()) movesLeft--;
                    break;
                default:
                    std::cout << ANSI_COLOR_RED << "\n\t\aINVALID KEY!\a" << ANSI_COLOR_RESET << std::endl;
            }
        }

        if(movesLeft == 0)
            std::cout << ANSI_COLOR_RED << "\n\tYOU LOSE THE GAME!!!\n" << ANSI_COLOR_RESET;
        else
            std::cout << ANSI_COLOR_GREEN << "\n\tCONGRATULATIONS " << name << " FOR WINNING THIS GAME!\n" << ANSI_COLOR_RESET;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << ANSI_COLOR_MAGNETA << "\nWant to Play Again? (y/n): " << ANSI_COLOR_RESET;
        char check;
        std::cin >> check;

        playAgain = (check == 'y' || check == 'Y');
    }

    return 0;
}
