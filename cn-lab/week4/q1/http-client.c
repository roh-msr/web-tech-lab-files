#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8091
#define MAX 1024

int main()
{
    int c_sock;
    struct sockaddr_in serverAddr;
    char buffer[MAX];

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
    {
        char *file_path = (char *)malloc(sizeof(char) * MAX);
        char *requestString = (char *)malloc(sizeof(char) * MAX);
        char *responseString = (char *)malloc(sizeof(char) * MAX);

        printf("Connected to the server...\n");

        printf("\nEnter the URL:");
		scanf("%[^\n]s",file_path);

        snprintf(requestString, MAX, "GET /%s HTTP/1.1\r\nContent-Type:text/html\r\n", file_path);
        printf("\n%s", requestString);

        send(c_sock, requestString, strlen(requestString), 0);
        printf("\nGET Request sent\n");

        read(c_sock, responseString, MAX);
        printf("\n\n\n%s\n", responseString);
    }

    printf("\n");
    close(c_sock);
}
