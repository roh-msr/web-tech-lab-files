#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define PORT 1222
#define MAX 10000

void clientChat(int sockfd)
{
    char msg[MAX];
    int n;
    time_t t;

    while(1){
        memset(msg, '\0', MAX);

        // read the message from the client
        // and copy it in the msg
        read(sockfd, msg, sizeof(msg));

        if(strncmp("exit", msg, 4) == 0){
            printf("Client left the chat...!\n");

            write(sockfd, "exit", 4);

            break;
        }
        else if(strncmp("datetime", msg, 8) == 0){
            time(&t);

            char str1[80];
            sprintf(str1, "Current Time : %s", ctime(&t));

            write(sockfd, str1, sizeof(str1));
        }
        else{
            char str2[] = "Invalid Request!";
            write(sockfd, str2, sizeof(str2));
        }
    }
}

int main(){
    int sock, conn_fd;
    struct sockaddr_in server, client;
    int len;

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
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(struct sockaddr_in);

    if((bind(sock, (struct sockaddr *)&server, len)) == -1){
        perror("Bind: ");
        exit(-2);
    }
    else
        printf("Socket succesfully binded...\n");

    if ((listen(sock, 5)) != 0) {
        perror("Listen: ");
        exit(-3);
    }
    else
        printf("Server listening...\n");

    conn_fd = accept(sock, (struct sockaddr *)&client, &len);
    if(conn_fd < 0){
        perror("Server: ");
        exit(-4);
    }
    else
        printf("Server accepted the client...\n");

    // Function for server-client chatting!!
    clientChat(conn_fd);

    close(sock);

    return 0;
}
