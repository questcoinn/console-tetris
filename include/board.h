#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <vector>

#include "tetrisUtils.h"
#include "tetromino.h"

namespace tetris {
    class Board {
    public:
        Board(const int width = 10, const int height = 20);
        ~Board() = default;

    public:
        Color getCellColor(const int x, const int y) const;
        void setCellColor(const int x, const int y, const Color color);
        bool updateBoard(const Tetromino &currentBlock);
        void setCurrentBlock(const Tetromino &currentBlock);
        void resetOffsets();

    public:
        int width;
        int height;
        int limit;
        int blockOffsetX;
        int blockOffsetY;

    private:
        std::vector<Color> states;
    };
}

#endif