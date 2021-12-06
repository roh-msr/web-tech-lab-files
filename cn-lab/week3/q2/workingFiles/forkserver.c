#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define PORT 2021 // 21 not working in my system, so 2021
#define BUFSIZE 1024

int main()
{
    int sock, newSock;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addr_size;
    int yes = 1;

    char buffer[BUFSIZE];
    char newbuffer[BUFSIZE];
    pid_t childpid;

    // // MAKE CONNECTION!! // //
    // // //

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Socket: ");
        exit(-1);
    }

    // assign IP, port
    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    if ((bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) == -1)
    {
        perror("Bind: ");
        exit(-2);
    }

    if ((listen(sock, 5)) != 0)
    {
        perror("Listen: ");
        exit(-3);
    }
    // // //

    // // Function for server-client chatting!! //
    while (1)
    {
        newSock = accept(sock, (struct sockaddr *)&newAddr, &addr_size);
        if (newSock < 0)
        {
            exit(1);
        }
        printf("\nConnection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if ((childpid = fork()) == 0)
        {
            close(sock);

            while (1)
            {
                memset(buffer, '\0', BUFSIZE);
                memset(newbuffer, '\0', BUFSIZE);
                recv(newSock, buffer, BUFSIZE, 0);

                if (strncmp(":exit", buffer, 5) == 0)
                {
                    printf("\nDisconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                }
                else
                {
                    printf("\nFile requested by the client : %s", buffer);

                    // Slugify!
                    int i = 0;
                    int ni = 0;
                    while (buffer[i] != '\n')
                    {
                        char chr = buffer[i++];

                        if (chr == ' ')
                        {
                            if (newbuffer[ni - 1] != '-' && (buffer[i] != '\n' && buffer[i] != ' ' && isalnum(buffer[i])))
                            {
                                newbuffer[ni++] = '-';
                            }
                        }
                        else if (isalnum(chr))
                        {
                            newbuffer[ni++] = tolower(chr);
                        }
                    }

                    send(newSock, newbuffer, strlen(newbuffer), 0);
                    memset(buffer, '\0', BUFSIZE);
                    memset(newbuffer, '\0', BUFSIZE);
                }
            }
        }
    }
    // // //

    close(newSock);

    return 0;
}
