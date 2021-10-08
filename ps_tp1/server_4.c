/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
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

bool running(true);

void stop_handler(int sig) //Stop handler
{
    printf("Received: signal %d \n", (sig));
    running = false;
}

void exit_message() //Function adding an exit message
{
    printf("Ending the program.... Goodbye, see you soon, take care ! :) \n");
}

int main()
{
    int pipefd[2];
    int buf;
    if (pipe(pipefd) == -1)
    {
        exit(EXIT_FAILURE);
    }

    //Structure for sigaction
    struct sigaction s;
    s.sa_handler = &stop_handler;
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);
    atexit(exit_message);

    pid_t c_pid = fork();
    if (c_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (c_pid == 0) //Entering the child process
    {
        printf("Child process, Pid: %d \n", getpid());
        close(pipefd[1]);

        while (running && read(pipefd[0], &buf, sizeof(int)) > 0)
        {
            //Lecture du nombre aléatoire puis affichage du message
            printf("\n Le nombre aléatoire récupéré par le fils: %d", buf);
        }   
        close(pipefd[0]);
    }
    else
    {
        printf("Father process, Pid: %d \n", getpid());

        close(pipefd[0]);
        while (running)
        {
            // boucle infine
            int pid(getpid());
            int fatherpid(getppid());

            int random_nub(rand() % 100);
            if (!write(pipefd[1], &random_nub, sizeof(int))) {
                return EXIT_FAILURE;
            }
            sleep(1);
        }
        close(pipefd[1]);
        int child_status;
        wait(&child_status);
        printf("Child terminated with status %d\n", child_status);
    }

    return EXIT_SUCCESS;
}
