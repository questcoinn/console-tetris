namespace tetris {
    enum HandlingCode {
        HANDLE_SUCCESS = 0,
        HANDLE_FAIL,
        HANDLE_UNSUPPORT_KEY,
    };

    typedef HandlingCode (*inputHandler)(char key);

    class ConsoleHandler {
    public:
        ConsoleHandler() = default;
        ~ConsoleHandler() = default;

    public:
        void clear();
        void write();
        void getInputs(char stop, inputHandler h);
    };
}