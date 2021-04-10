#include "consoleHandler.h"

namespace tetris {
    ConsoleHandler::ConsoleHandler() {
        this->setColor(Color_RESET);
    }

    void ConsoleHandler::clear() {
        std::printf("\x1b[2J");
    }

    void ConsoleHandler::write(std::string str, Color color) {
        if(color != Color_UNSET) {
            this->setColor(color);
        }
        std::printf("%s", str.c_str());
    }

    void ConsoleHandler::setColor(Color color) {
        if(color == Color_RESET) {
            std::printf("\x1b[0m");
        }
        else if(color == Color_CYAN) {
            std::printf("\x1b[96m");
        }
        else if(color == Color_BLUE) {
            std::printf("\x1b[94m");
        }
        else if(color == Color_ORANGE) {
            std::printf("\x1b[38;5;208m");
        }
        else if(color == Color_YELLOW) {
            std::printf("\x1b[93m");
        }
        else if(color == Color_GREEN) {
            std::printf("\x1b[92m");
        }
        else if(color == Color_PURPLE) {
            std::printf("\x1b[95m");
        }
        else if(color == Color_RED) {
            std::printf("\x1b[91m");
        }
    }

    void ConsoleHandler::getInputs(char stop, inputHandler h) {
        // TODO
    }
}