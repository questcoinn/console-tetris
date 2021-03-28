#include <array>
#include "tetrisUtils.h"

namespace tetris {
    enum BlockType {
        I, J, L, O, S, T, Z
    };

    class Tetromino {
    public:
        Tetromino(BlockType type, CellColor color);
        ~Tetromino() = default;

    public:
        void rotate();

    public:
        BlockType type;
        CellColor color;
        int rotation;
        std::array<bool, 16> states;
    };
}