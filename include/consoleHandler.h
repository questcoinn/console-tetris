#ifndef TETRIS_CONSOLE_HANDLER_H
#define TETRIS_CONSOLE_HANDLER_H

#include <functional>
#include <memory>
#include <string>
#include <cstdio>
#include <termios.h>
#include "tetrisUtils.h"

namespace tetris {
    enum HandlingCode {
        SUCCESS = 0,
        FAIL,
        EXIT,
        UNSUPPORT_KEY,
    };

    typedef HandlingCode (*inputHandler)(const char key);

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

    class RawInputHandler {
    public:
        RawInputHandler(const char stop);
        ~RawInputHandler();

    public:
        void run(const std::function <HandlingCode(const char)> &f) const;
        void restoreSetting() const;

    private:
        std::unique_ptr<termios> pOldt;
        std::unique_ptr<termios> pNewt;
        const char stop;
    };
}

#endif