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

#define PORT 2021
#define MAX 1024

void serverChat(int sockfd)
{
    char msg[MAX];

    int n;

    while(1){
        memset(msg, '\0', MAX);

        n = 0;

        // store client message in msg buffer
        printf("Enter your message: ");
        while((msg[n++] = getchar()) != '\n' && n < MAX);

        // send the message to the server
        write(sockfd, msg, sizeof(msg));
        if(strncmp("exit", msg, 4) == 0){
            printf("Exited!\n");
            break;
        }

        memset(msg, '\0', MAX);

        // read the message from the server and copy it in the msg
        read(sockfd, msg, sizeof(msg));
        printf("From Server: %s\n", msg);
    }
}

int main(){
    int sock, conn_fd;
    struct sockaddr_in server, client;

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("Socket: ");
        exit(-1);
    }
    else
        printf("Socket successfully created...\n");

    // bzero() is deprecated, so memset() is used
    memset(&server.sin_zero, 0, sizeof(server.sin_zero));

    // assign IP, port
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    conn_fd = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if(conn_fd != 0){
        perror("Server connection: ");
        exit(-4);
    }
    else
        printf("Connected to the server...\n");

    // Function for server-client chatting!!
    serverChat(sock);

    close(sock);

    return 0;
}
