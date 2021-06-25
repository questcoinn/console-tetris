#include <chrono>
#include <future>
#include <memory>
#include <thread>

#include <csignal>
#include <cstdio>

#include <termios.h>
#include <unistd.h>

#define STOP_CHAR   'x'

template <typename Running_Type, typename ...Args> void _run(Args ...args);
void sigintHandler(int signum);

class TermInput;

// main
int main() {
    using namespace std::chrono_literals;

    std::signal(SIGINT, sigintHandler);

    auto threadEnded = std::async(std::launch::async, _run<TermInput, char>, STOP_CHAR);
    while(threadEnded.wait_for(0ms) == std::future_status::timeout) {
        std::printf("loop\n");
        std::this_thread::sleep_for(1000ms);
    }
    threadEnded.get();
    return 0;
}

class TermInput {
public:
    TermInput(const char stop)
        :pOldt(std::make_unique<termios>())
        ,pNewt(std::make_unique<termios>())
        ,stop(stop)
    {
        std::printf("\rinit!\n");
        /*tcgetattr gets the parameters of the current terminal
        STDIN_FILENO will tell tcgetattr that it should write the settings
        of stdin to oldt*/
        tcgetattr(STDIN_FILENO, this->pOldt.get());
        /*now the settings will be copied*/
        *(this->pNewt.get()) = *(this->pOldt.get());

        /*ICANON normally takes care that one line at a time will be processed
        that means it will return if it sees a "\n" or an EOF or an EOL*/
        this->pNewt->c_lflag &= ~(ICANON);          

        /*Those new settings will be set to STDIN
        TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr(STDIN_FILENO, TCSANOW, this->pNewt.get());
    }

    ~TermInput() {
        std::printf("\rdelete!\n");
        this->restoreSetting();
    }

public:
    void operator()() const {
        this->run();
    }

public:
    void run() const {
        char c = 0;
        while(true) {
            c = static_cast<char>(fgetc(stdin));
            if(c == this->stop) {
                break;
            }
            std::printf("\rinput: '%c'\n", c);
        }
    }

    void restoreSetting() const {
        tcsetattr(STDIN_FILENO, TCSANOW, this->pOldt.get());
    }

private:
    std::unique_ptr<termios> pOldt;
    std::unique_ptr<termios> pNewt;
    const char stop;
};

template <typename Running_Type, typename ...Args>
void _run(Args ...args) {
    Running_Type ti(args...);
    ti();
}

void sigintHandler(int signum) {
    std::printf("\rPress '%c' to exit\n", STOP_CHAR);
}