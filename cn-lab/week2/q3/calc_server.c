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

#define PORT 1222
#define MAX 10000

void clientChat(int sockfd)
{
    char msg[MAX];
    int n;
    time_t t;
    char * opr;
    char * x;
    char * y;

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

        char* token = strtok(msg, " ");
        opr = token;
        int counter = 1;
        while(token != NULL){
            if(counter > 2){
                break;
            }
            else if(counter == 1){
                token = strtok(NULL, " ");
                x = token;
            }
            else if(counter == 2){
                token = strtok(NULL, " ");
                y = token;
            }
            counter++;
        }

        printf("Operation = %s, NUM-1 = %s, NUM-2 = %s\n", opr, x, y);

        if(strncmp("add", opr, 3) == 0){
            sprintf(msg, "Result = %d", atoi(x) + atoi(y));
            write(sockfd, msg, sizeof(msg));
        }
        else if(strncmp("sub", opr, 3) == 0){
            sprintf(msg, "Result = %d", atoi(x) - atoi(y));
            write(sockfd, msg, sizeof(msg));
        }
        else if(strncmp("mul", opr, 3) == 0){
            sprintf(msg, "Result = %d", atoi(x) * atoi(y));
            write(sockfd, msg, sizeof(msg));
        }
        else if(strncmp("div", opr, 3) == 0){
            if(atoi(y) == 0){
                sprintf(msg, "Cannot divide by %d", atoi(y));
            }
            else{
                sprintf(msg, "Result = %d", atoi(x) / atoi(y));
            }

            write(sockfd, msg, sizeof(msg));
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
