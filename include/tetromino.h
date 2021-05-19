#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <array>
#include <memory>
#include <random>
#include <unordered_map>
#include "tetrisUtils.h"

namespace tetris {
    using uidist = std::uniform_int_distribution<int>;
    using rotatingTetrominoArray = std::array<bool *, 4>;

    enum TetrominoType {
        TetrominoType_I = 0,
        TetrominoType_J,
        TetrominoType_L,
        TetrominoType_O,
        TetrominoType_S,
        TetrominoType_T,
        TetrominoType_Z
    };
    const int BLOCK_TYPE_SIZE = 7;

    class TetrominoFactory {
    public:
        TetrominoFactory();
        ~TetrominoFactory() = default;

    public:
        bool *get(TetrominoType type, int rotation);

    private:
        void setTetromino(TetrominoType type, int rotation, int pos1, int pos2, int pos3, int pos4);
        void setTetrominos();

    public:
        std::unordered_map<TetrominoType, Color> typeColorMap;

    private:
        std::array<rotatingTetrominoArray, 7> tetrominos;
    };

    class Tetromino {
    public:
        Tetromino();
        ~Tetromino();

    public:
        void resetAsRandomType();
        void set(TetrominoType type);
        void rotate();

    public:
        int rotation;
        Color color;
        bool *pStates;
        TetrominoType type;

    private:
        std::unique_ptr<TetrominoFactory> pFactory;
        std::unique_ptr<std::mt19937> pGenerator;
        std::unique_ptr<uidist> pDistribution;
    };
}

#endif