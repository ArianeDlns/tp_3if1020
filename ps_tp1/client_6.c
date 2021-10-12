/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_6.c
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
#include <sys/stat.h>
#include <sys/types.h>
// For TCP
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>	

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

int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");

        //Structure for sigaction
    struct sigaction s;
    s.sa_handler = &stop_handler;
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);
    sigaction(SIGPIPE, &s, NULL);
    
    while (running)
    {
        printf("[Client process], Pid: %d \n", getpid());

        int number_received{};
        if (read(sock, &number_received, 1)==0){
            stop_handler(2);
        }
        printf("Random number received : %d\n", number_received);
        sleep(1);
    }

    atexit(exit_message);
    close(sock);
    return EXIT_SUCCESS;	
}