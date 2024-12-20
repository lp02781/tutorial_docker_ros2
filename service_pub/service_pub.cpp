#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void daemonize() {
    pid_t pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE); // failed to fork
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS); // parent process exits
    }

    if (setsid() < 0) {
        exit(EXIT_FAILURE); // create a new session and detach from terminal
    }

    umask(0); // set file mode creation mask

    // Change the current working directory to root
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }

    // Close all open file descriptors
    for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close(x);
    }

    // Redirect stdin, stdout, stderr to /dev/null
    open("/dev/null", O_RDWR); // stdin
    dup(0);  // stdout
    dup(0);  // stderr
}

void print_hello() {
    int counter = 1;
    while (true) {
        std::cout << "Hello " << counter << std::endl;
        counter++;  // Increment the counter
        std::this_thread::sleep_for(std::chrono::seconds(1)); // wait for 1 second
    }
}

int main() {
    daemonize(); // Detach and run as a background service
    print_hello(); // Call the print_hello function
    return 0;
}
