#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MYPORT 13456
#define MAX 500
#define BACKLOG 5
#define nums_IP 4

void Map_Ip_addresses();
char *Retrieve_IP_Address(char *);

struct IP_struct
{
    char *IP;
    char *Name;
};

struct IP_struct IP_Map[MAX]; //arr of Ip_structures

int main()
{

    int sockfd, client_sockfd, sin_size;
    struct sockaddr_in my_addr, client_addr;
    char *IP_addr;
    char *Domain_name;
    char *Msg;

    Map_Ip_addresses();

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    Domain_name = (char *)malloc(sizeof(char) * MAX);
    Msg = (char *)malloc(sizeof(char) * MAX);
    IP_addr = (char *)malloc(sizeof(char) * MAX);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("\nSocket not created:");
        exit(1);
    }

    if (bind(sockfd, (const struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("\nNot Bound");
        exit(1);
    }

    printf("\nSocket bound");

    sin_size = sizeof(client_addr);

    while (1)
    {
        recvfrom(sockfd, (char *)Domain_name, MAX, 0, (struct sockaddr *)&client_addr, &sin_size);
        IP_addr = "\0";
        IP_addr = Retrieve_IP_Address(Domain_name);

        if (strcmp(IP_addr, "\0") == 0)
        {
            strcpy(Msg, "Incorrect Domain Name");
            sendto(sockfd, Msg, strlen(Msg), 0, (struct sockaddr *)&client_addr, sin_size);
            printf("\nIncorrect Domain Name!!!");
        }
        else
        {
            sendto(sockfd, (char *)IP_addr, strlen(IP_addr), 0, (struct sockaddr *)&client_addr, sin_size);
            printf("\nIP address sent!!!");
        }

        memset(IP_addr, '\0', MAX);
        memset(Domain_name, '\0', MAX);
    }

    close(sockfd);

    return 0;
}

void Map_Ip_addresses()
{

    for (int i = 0; i < nums_IP; i++)
    {
        IP_Map[i].IP = (char *)malloc(sizeof(char) * MAX);
        IP_Map[i].Name = (char *)malloc(sizeof(char) * MAX);
    }

    strcpy(IP_Map[0].IP, "208.98.192.170");
    strcpy(IP_Map[0].Name, "google.com");

    strcpy(IP_Map[1].IP, "118.15.240.85");
    strcpy(IP_Map[1].Name, "yahoo.com");

    strcpy(IP_Map[2].IP, "51.204.60.59");
    strcpy(IP_Map[2].Name, "annauniv.edu.in");

    strcpy(IP_Map[3].IP, "45.205.90.67");
    strcpy(IP_Map[3].Name, "wikipedia.com");
}

char *Retrieve_IP_Address(char *Domain_Name)
{

    char *IP_temp = (char *)malloc(sizeof(char) * MAX);

    for (int i = 0; i < nums_IP; i++)
    {
        if (strcmp(Domain_Name, (char *)(IP_Map[i].Name)) == 0)
        {
            IP_temp = IP_Map[i].IP;
            break;
        }
    }

    return IP_temp;
}