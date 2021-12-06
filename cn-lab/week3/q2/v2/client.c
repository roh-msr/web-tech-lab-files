#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define ROOT 9449
#define MAX 1025

int main()
{
    int sockfd, sin_size;
    struct sockaddr_in server;
    char domain_name[MAX];
    char MSG[MAX];

    server.sin_family = AF_INET;
    server.sin_port = htons(ROOT);
    server.sin_addr.s_addr = INADDR_ANY;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket not created!!!\n");
        exit(1);
    }

    memset(MSG, '\0', MAX);
    printf("Enter the domain:");
    scanf("%s", domain_name); //gets the domain name from the user

    sin_size = sizeof(server);
    sendto(sockfd, domain_name, strlen(domain_name), 0, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, (char *)MSG, MAX, 0, (struct sockaddr *)&server, &sin_size); //root server returns the port number of TLD

    printf("Root Server Response : (TLD Port, %s, NS)\n", MSG);

    server.sin_port = htons(atoi(MSG)); // connect to TLD port

    memset(MSG, '\0', MAX);

    sendto(sockfd, domain_name, strlen(domain_name), 0, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, MSG, MAX, 0, (struct sockaddr *)&server, &sin_size);

    if (strcmp(MSG, "Incorrect Domain Name") == 0)
    {
        printf("TLD Server Response: Web Page Not Found!!!\n");
    }
    else
    {
        printf("TLD Server Response: (%s, %s, A)\n", domain_name, MSG);
    }

    close(sockfd);
    return 0;
}