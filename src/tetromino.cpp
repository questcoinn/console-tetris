#include "tetromino.h"

namespace tetris {
    TetrominoFactory::TetrominoFactory() {
        this->tetrominos = std::array<rotatingTetrominoArray, 7>();
        for(int type = 0; type < BLOCK_TYPE_SIZE; ++type) {
            this->tetrominos[type] = rotatingTetrominoArray();
            for(int r = 0; r < 4; ++r) {
                this->tetrominos[type][r] = new bool[16];
                for(int pos = 0; pos < 16; ++pos) {
                    this->tetrominos[type][r][pos] = false;
                }
            }
        }
        this->typeColorMap = std::unordered_map<TetrominoType, Color>();

        this->setTetrominos();
        this->typeColorMap[TetrominoType_I] = Color_CYAN;
        this->typeColorMap[TetrominoType_J] = Color_BLUE;
        this->typeColorMap[TetrominoType_L] = Color_ORANGE;
        this->typeColorMap[TetrominoType_O] = Color_YELLOW;
        this->typeColorMap[TetrominoType_S] = Color_GREEN;
        this->typeColorMap[TetrominoType_T] = Color_PURPLE;
        this->typeColorMap[TetrominoType_Z] = Color_RED;
    }

    bool *TetrominoFactory::get(TetrominoType type, int rotation) {
        return this->tetrominos[static_cast<int>(type)][rotation];
    }

    void TetrominoFactory::setTetromino(TetrominoType type, int rotation, int pos1, int pos2, int pos3, int pos4) {
        this->tetrominos[static_cast<int>(type)][rotation][pos1] = true;
        this->tetrominos[static_cast<int>(type)][rotation][pos2] = true;
        this->tetrominos[static_cast<int>(type)][rotation][pos3] = true;
        this->tetrominos[static_cast<int>(type)][rotation][pos4] = true;
    }

    void TetrominoFactory::setTetrominos() {
        // ccw
        this->setTetromino(TetrominoType_I, 0,  4,  5,  6,  7);
        this->setTetromino(TetrominoType_I, 1,  1,  5,  9, 13);
        this->setTetromino(TetrominoType_I, 2,  4,  5,  6,  7);
        this->setTetromino(TetrominoType_I, 3,  1,  5,  9, 13);

        this->setTetromino(TetrominoType_J, 0,  5,  9, 10, 11);
        this->setTetromino(TetrominoType_J, 1,  6, 10, 13, 14);
        this->setTetromino(TetrominoType_J, 2,  5,  6,  7, 11);
        this->setTetromino(TetrominoType_J, 3,  5,  6,  9, 13);

        this->setTetromino(TetrominoType_L, 0,  7,  9, 10, 11);
        this->setTetromino(TetrominoType_L, 1,  5,  6, 10, 14);
        this->setTetromino(TetrominoType_L, 2,  5,  6,  7,  9);
        this->setTetromino(TetrominoType_L, 3, 11, 13, 14, 15);

        this->setTetromino(TetrominoType_O, 0,  5,  6,  9, 10);
        this->setTetromino(TetrominoType_O, 1,  5,  6,  9, 10);
        this->setTetromino(TetrominoType_O, 2,  5,  6,  9, 10);
        this->setTetromino(TetrominoType_O, 3,  5,  6,  9, 10);

        this->setTetromino(TetrominoType_S, 0,  6,  7,  9, 10);
        this->setTetromino(TetrominoType_S, 1,  5,  9, 10, 14);
        this->setTetromino(TetrominoType_S, 2,  6,  7,  9, 10);
        this->setTetromino(TetrominoType_S, 3,  5,  9, 10, 14);

        this->setTetromino(TetrominoType_T, 0, 10, 13, 14, 15);
        this->setTetromino(TetrominoType_T, 1,  6,  9, 10, 14);
        this->setTetromino(TetrominoType_T, 2,  9, 10, 11, 14);
        this->setTetromino(TetrominoType_T, 3,  6, 10, 11, 14);

        this->setTetromino(TetrominoType_Z, 0,  5,  6, 10, 11);
        this->setTetromino(TetrominoType_Z, 1,  6,  9, 10, 13);
        this->setTetromino(TetrominoType_Z, 2,  5,  6, 10, 11);
        this->setTetromino(TetrominoType_Z, 3,  6,  9, 10, 13);
    }

    Tetromino::Tetromino():
            rotation(0) {
        this->pStates = nullptr;

        this->pFactory = std::unique_ptr<TetrominoFactory>(new TetrominoFactory());

        std::random_device RandomDev;
        this->pGenerator = std::unique_ptr<std::mt19937>(new std::mt19937(RandomDev()));
        this->pDistribution = std::unique_ptr<uidist>(new uidist(0, BLOCK_TYPE_SIZE - 1));

        this->resetAsRandomType();
    }

    Tetromino::~Tetromino() {
        if(this->pStates != nullptr) {
            this->pStates = nullptr;
        }
    }

    void Tetromino::resetAsRandomType() {
        TetrominoType type = static_cast<TetrominoType>((*(this->pDistribution))(*(this->pGenerator)));
        this->set(type);
    }

    void Tetromino::set(TetrominoType type) {
        this->type = type;
        this->rotation = 0;
        auto foundColor = this->pFactory->typeColorMap.find(type);
        this->color = foundColor != this->pFactory->typeColorMap.end() ? foundColor->second : Color_RESET;
        this->pStates = this->pFactory->get(type, 0);
    }

    void Tetromino::rotate() {
        this->rotation = (this->rotation + 1) % 4;
        this->pStates = this->pFactory->get(this->type, this->rotation);
    }
}