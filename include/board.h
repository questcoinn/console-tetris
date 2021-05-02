#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <vector>
#include "tetrisUtils.h"

namespace tetris {
    const int MAX_BOARD_WIDTH = 10;
    const int MAX_BOARD_HEIGHT = 20;

    class Board {
    public:
        Board(int width = MAX_BOARD_WIDTH, int height = MAX_BOARD_HEIGHT);
        ~Board() = default;

    public:
        Color getCellColor(int x, int y) const;
        void setCellColor(int x, int y, Color color);

    public:
        int width;
        int height;
        int limit;

    private:
        std::vector<Color> states;
    };
}

#endif