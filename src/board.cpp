#include "board.h"

namespace tetris {
    Board::Board(int width, int height):
            width(width),
            height(height),
            limit(width * height) {
        this->states = std::vector<Color>();
        for(int i = 0; i < width * height; i++) {
            this->states.push_back(Color_RESET);
        }
    }

    Color Board::getCellColor(int i, int j) const {
        const int idx = i * this->width + j;
        if(idx < 0 || idx >= this->limit) {
            return Color_RESET;
        }
        return this->states.at(idx);
    }

    void Board::setCellColor(int i, int j, Color color) {
        const int idx = i * this->width + j;
        if(idx < 0 || idx >= this->limit) {
            return;
        }
        this->states.at(idx) = color;
    }
}
