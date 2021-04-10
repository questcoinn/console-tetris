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
        void write(std::string str, Color color = Color_UNSET);
        void getInputs(char stop, inputHandler h);

    private:
        void setColor(Color color);
    };
}