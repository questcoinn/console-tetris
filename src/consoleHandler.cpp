#include "consoleHandler.h"

namespace tetris {
    ConsoleHandler::ConsoleHandler() {
        this->setColor(Color::RESET);
    }

    void ConsoleHandler::clear() {
        this->flushBuffer();
        std::printf("\x1b[2J");
    }

    void ConsoleHandler::write(const std::string str, const Color color) const {
        if(color != Color::UNSET) {
            this->setColor(color);
        }
        std::printf("%s", str.c_str());
    }

    void ConsoleHandler::setColor(const Color color) const {
        if(color == Color::RESET) {
            std::printf("\x1b[0m");
        }
        else if(color == Color::CYAN) {
            std::printf("\x1b[96m");
        }
        else if(color == Color::BLUE) {
            std::printf("\x1b[94m");
        }
        else if(color == Color::ORANGE) {
            std::printf("\x1b[38;5;208m");
        }
        else if(color == Color::YELLOW) {
            std::printf("\x1b[93m");
        }
        else if(color == Color::GREEN) {
            std::printf("\x1b[92m");
        }
        else if(color == Color::PURPLE) {
            std::printf("\x1b[95m");
        }
        else if(color == Color::RED) {
            std::printf("\x1b[91m");
        }
    }

    void ConsoleHandler::getInputs(const char stop, const inputHandler h) const {
        // TODO
    }

    void ConsoleHandler::moveCursor(const int x, const int y) const {
        std::printf("\x1b[%d;%dH", y + 1, x + 1);
    }

    void ConsoleHandler::flushBuffer() {
        std::fflush(stdout);
    }
}