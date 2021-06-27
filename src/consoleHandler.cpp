#include <unistd.h>
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
        // RawInputHandler rih(stop);
        // rih.run(h);
    }

    void ConsoleHandler::moveCursor(const int x, const int y) const {
        std::printf("\x1b[%d;%dH", y + 1, x + 1);
    }

    void ConsoleHandler::flushBuffer() {
        std::fflush(stdout);
    }

    RawInputHandler::RawInputHandler(const char stop)
        :pOldt(std::make_unique<termios>())
        ,pNewt(std::make_unique<termios>())
        ,stop(stop)
    {
        tcgetattr(STDIN_FILENO, this->pOldt.get());
        *(this->pNewt.get()) = *(this->pOldt.get());
        this->pNewt->c_lflag &= ~(ICANON);          
        tcsetattr(STDIN_FILENO, TCSANOW, this->pNewt.get());
    }

    RawInputHandler::~RawInputHandler() {
        this->restoreSetting();
    }

    void RawInputHandler::run(const std::function <HandlingCode(const char)> &f) const {
        HandlingCode status = HandlingCode::SUCCESS;
        char c = 0;
        while(true) {
            status = f(static_cast<char>(fgetc(stdin)));
            if(status != HandlingCode::SUCCESS) {
                break;
            }
        }
    }

    void RawInputHandler::restoreSetting() const {
        tcsetattr(STDIN_FILENO, TCSANOW, this->pOldt.get());
    }
}