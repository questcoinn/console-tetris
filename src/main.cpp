#ifdef DEBUG
# include <iostream>
#endif
#include <chrono>
#include <future>
#include <string>
#include <thread>

#include <csignal>
#include <cstdlib>

#include "consoleHandler.h"
#include "board.h"
#include "tetromino.h"

#define STOP_CHAR   'x'

using namespace std::chrono_literals;

void handleSigint(const int signum);

int main() {
    std::signal(SIGINT, handleSigint);

    // input handling thread => change state

    const int width = 10;
    const int height = 20;

    int x = 0;
    int y = 0;

    tetris::ConsoleHandler ch;
    tetris::Board board(width, height);
    tetris::Tetromino currentBlock;
    tetris::Tetromino nextBlock;

    auto threadAsync = std::async(std::launch::async, [&](const char stop) -> void {
        tetris::RawInputHandler rih(stop);
        rih.run([&](const char key) -> tetris::HandlingCode {
            tetris::HandlingCode status = tetris::HandlingCode::SUCCESS;
            switch(key) {
                case 'x':
                    status = tetris::HandlingCode::EXIT;
                    break;
                case 'a':
                    // todo: board::setBlockOffset()
                    break;
                case 'd':
                    break;
                default:
                    status = tetris::HandlingCode::SUCCESS;
            }
            return status;
        });
    }, STOP_CHAR);

    ch.clear();
    // game loop
    while(threadAsync.wait_for(0ms) == std::future_status::timeout) {
        // pre-process
        const bool keepCurrentBlock = board.updateBoard(currentBlock);

        // render
        for(y = 0; y < height; ++y) {
            ch.moveCursor(0, y);
            for(x = 0; x < width; ++x) {
                const tetris::Color color = board.getCellColor(x, y);
                const std::string s = color != tetris::Color::RESET ? "o" : ".";
                ch.write(s, color);
            }
        }
        for(y = 0; y < 4; ++y) {
            for(x = 0; x < 4; ++x) {
                if(currentBlock.pStates[y * 4 + x]) {
                    ch.moveCursor(board.blockOffsetX + x, board.blockOffsetY + y);
                    ch.write("o", currentBlock.color);
                }
            }
        }

        // post-process
        if(!keepCurrentBlock) {
            board.setCurrentBlock(currentBlock);
            currentBlock.set(nextBlock.type);
            nextBlock.resetAsRandomType();
        }
        ch.flushBuffer();
        std::this_thread::sleep_for(300ms);
    }

    threadAsync.get();
    return 0;
}

void handleSigint(const int signum) {
    std::printf("\rPress '%c' to exit\n", STOP_CHAR);
}