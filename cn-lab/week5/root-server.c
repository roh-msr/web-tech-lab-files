#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MYPORT 9449
#define MAX 1025
#define BACKLOG 5
#define TLD_PORT 9556

int main()
{

    int sockfd, sin_size;
    char MSG[MAX];

    struct sockaddr_in my_addr, client;

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket not created:");
        exit(1);
    }

    if (bind(sockfd, (const struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        perror("\nSocket not Bound:");
        exit(1);
    }
    else
        printf("\nSocket Bound!!!\n");

    sin_size = sizeof(client);
    while (1)
    {
        memset(MSG, '\0', MAX);
        recvfrom(sockfd, MSG, MAX, MSG_WAITALL, (struct sockaddr *)&client, &sin_size);
        printf("Received: %s\n", MSG);

        memset(MSG, '\0', MAX);
        sprintf(MSG, "%d", TLD_PORT);

        sendto(sockfd, (char *)MSG, strlen(MSG), 0, (const struct sockaddr *)&client, sin_size); //it sends the port number of the TLD
    }

    close(sockfd);
    return 0;
}