#ifdef DEBUG
# include <iostream>
#endif
#include <chrono>
#include <thread>

#include <csignal>
#include <cstdlib>

#include "consoleHandler.h"
#include "board.h"
#include "tetromino.h"

using namespace std::chrono_literals;

void sigintHandler(int signum);

int main() {
    std::signal(SIGINT, sigintHandler);

    // input handling thread => change state

    const int width = 10;
    const int height = 20;

    int x = 0;
    int y = 0;

    tetris::ConsoleHandler ch;
    tetris::Board board(width, height);
    tetris::Tetromino currentBlock;
    tetris::Tetromino nextBlock;

    // game loop
    while(true) {
        ch.clear();

        // block test
        nextBlock.resetAsRandomType();
        currentBlock.set(nextBlock.type);

        // (0, 3) offset으로 board에 set
        bool isBlock = false;
        for(y = 0; y < 4; ++y) {
            for(x = 0; x < 4; ++x) {
                isBlock = currentBlock.pStates[y * 4 + x];
                board.setCellColor(x + 3, y, isBlock ? currentBlock.color : tetris::Color_RESET);
            }
        }

        // draw
        for(y = 0; y < height; ++y) {
            for(x = 0; x < width; ++x) {
                ch.write("o", board.getCellColor(x, y));
            }
            ch.write("\n", tetris::Color_RESET);
        }
        std::this_thread::sleep_for(1000ms);
    }

    // never reach!
#ifdef DEBUG
    std::cout << "How..?\n";
#endif
    return 0;
}

void sigintHandler(int signum) {
#ifdef DEBUG
    std::cout << "Interrupt signal (" << signum << ") received.\n";
#endif
    std::exit(signum);
}