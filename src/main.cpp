#ifdef DEBUG
# include <iostream>
#endif
#include <csignal>
#include <cstdlib>

void sigintHandler(int signum);

int main() {
    std::signal(SIGINT, sigintHandler);

    // input handling thread => change state
    // board
    // block

    // game loop
    while(true) {
        // render with interval
    }

    // never reach!
#ifdef DEBUG
    std::cout << "How..?\n";
#endif
    return 0;
}

void sigintHandler(int signum) {
#ifdef DEBUG
    std::cout << "Interrupt signal (" << signum << ") received.\n";
#endif
    std::exit(signum);
}