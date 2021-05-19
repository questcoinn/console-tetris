#ifndef TETRIS_CONSOLE_HANDLER_H
#define TETRIS_CONSOLE_HANDLER_H

#include <string>
#include <cstdio>
#include "tetrisUtils.h"

namespace tetris {
    enum HandlingCode {
        HANDLE_SUCCESS = 0,
        HANDLE_FAIL,
        HANDLE_UNSUPPORT_KEY,
    };

    typedef HandlingCode (*inputHandler)(char key);

    class ConsoleHandler {
    public:
        ConsoleHandler();
        ~ConsoleHandler() = default;

    public:
        void clear();
        void write(const std::string str, const Color color = Color::UNSET) const;
        void getInputs(const char stop, const inputHandler h) const;
        void moveCursor(const int x, const int y) const;
        void flushBuffer();

    private:
        void setColor(const Color color) const;
    };
}

#endif