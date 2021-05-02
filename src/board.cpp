#include "board.h"

namespace tetris {
    Board::Board(int width, int height):
            width(width),
            height(height),
            limit(width * height) {
        this->states = std::vector<Color>();
        for(int i = 0; i < this->limit; i++) {
            this->states.push_back(Color_RESET);
        }
    }

    Color Board::getCellColor(int x, int y) const {
        const int idx = y * this->width + x;
        if(idx < 0 || idx >= this->limit) {
            return Color_RESET;
        }
        return this->states.at(idx);
    }

    void Board::setCellColor(int x, int y, Color color) {
        const int idx = y * this->width + x;
        if(idx < 0 || idx >= this->limit) {
            return;
        }
        this->states.at(idx) = color;
    }
}
