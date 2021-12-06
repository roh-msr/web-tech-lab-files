#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define PORT 6421
#define BUFSIZE 1024

int main()
{
    int c_sock;
    struct sockaddr_in serverAddr;
    char buffer[BUFSIZE];

    // // MAKE CONNECTION!! // //
    // // //

    // Create a socket
    c_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (c_sock < -1)
    {
        perror("Socket Error: ");
        exit(-1);
    }
    else
        printf("Socket successfully created...\n");

    // assign IP, port
    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(c_sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Connect Error: ");
        exit(1);
    }
    else
        printf("Connected to the server...\n");

    // // Function for server-client chatting!! //

    int n;
    while (1)
    {
        n = 0;
        memset(buffer, '\0', BUFSIZE);

        printf("Enter your message: ");
        while ((buffer[n++] = getchar()) != '\n' && n < BUFSIZE)
            ;
        send(c_sock, buffer, strlen(buffer), 0);

        if (strncmp(":exit", buffer, 5) == 0)
        {
            close(c_sock);
            printf("Disconnected from server.\n");
            exit(1);
        }

        n = 0;
        memset(buffer, '\0', BUFSIZE);

        if (recv(c_sock, buffer, BUFSIZE, 0) < 0)
        {
            printf("Error in receiving data.\n");
        }
        else
        {
            if (strncmp(":exit", buffer, 5) == 0)
            {
                close(c_sock);
                printf("Disconnected from server.\n");
                exit(1);
            }
            else
                printf("Server: \t%s\n", buffer);
        }
    }
    // // //

    return 0;
}
