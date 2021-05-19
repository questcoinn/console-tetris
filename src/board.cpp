#include "board.h"

namespace tetris {
    Board::Board(const int width, const int height):
            width(width),
            height(height),
            limit(width * height) {
        this->resetOffsets();
        this->states = std::vector<Color>();
        for(int i = 0; i < this->limit; i++) {
            this->states.push_back(Color::RESET);
        }
    }

    Color Board::getCellColor(const int x, const int y) const {
        const int idx = y * this->width + x;
        if(idx < 0 || idx >= this->limit) {
            return Color::RESET;
        }
        return this->states.at(idx);
    }

    void Board::setCellColor(const int x, const int y, const Color color) {
        const int idx = y * this->width + x;
        if(idx < 0 || idx >= this->limit) {
            return;
        }
        this->states.at(idx) = color;
    }

    bool Board::updateBoard(const Tetromino &currentBlock) {
        this->blockOffsetY++;
        if(this->blockOffsetY >= this->height) {
            this->blockOffsetY--;
            return false;
        }

        // colision check
        for(int y = 0; y < 4; ++y) {
            for(int x = 0; x < 4; ++x) {
                if(currentBlock.pStates[y * 4 + x]) {
                    if(    this->getCellColor(this->blockOffsetX + x, this->blockOffsetY + y) != Color::RESET
                        || this->blockOffsetY + y >= this->height)
                    {
                        this->blockOffsetY--;
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void Board::setCurrentBlock(const Tetromino &currentBlock) {
        // 보드와 블록이 겹치지 않는다고 가정
        for(int y = 0; y < 4; ++y) {
            for(int x = 0; x < 4; ++x) {
                if(currentBlock.pStates[y * 4 + x]) {
                    this->setCellColor(this->blockOffsetX + x, this->blockOffsetY + y, currentBlock.color);
                }
            }
        }
        this->resetOffsets();
    }

    void Board::resetOffsets() {
        this->blockOffsetX = 3;
        this->blockOffsetY = -3;
    }
}
