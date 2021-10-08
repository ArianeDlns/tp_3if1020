/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
// For signal management
#include <signal.h>
// For wait
#include <sys/wait.h>
// For strlen
#include <string.h>
// For fifo
#include <fcntl.h>

bool running(true);

void stop_handler(int sig) //Stop handler
{
    printf("Received: signal %d \n", (sig));
    running = false;
}

void exit_message() //Function adding an exit message
{
    printf("Ending the program: %d... Goodbye, see you soon, take care ! :) \n", getpid());
}

int main()
{
    //Structure for sigaction
    struct sigaction s;
    s.sa_handler = &stop_handler;
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);
    atexit(exit_message);

    int read_fifo = open("fifo_ps", O_WRONLY);

    while (running)
    {
    }
    return EXIT_SUCCESS;
}
