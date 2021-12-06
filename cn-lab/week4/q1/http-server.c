#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>

#define PORT 8091
#define MAX 1024
#define BACKLOG 5

int status_code = 0;

void getFile(char buff[], char data[])
{
    char *file_path;
    file_path = (char *)malloc(sizeof(char) * MAX);

    int i = 3;

    while (buff[i] != '\n' && buff[i] != '/')
    {
        i++;
    } //strip the leading whitespaces

    i++; //skip the '/'

    while (buff[i] != '.')
    { //'.' indicates the starting of the extension
        strncat(file_path, &buff[i], 1);
        i++;
    } //extract the file name

    while (buff[i] != ' ')
    {
        file_path = strncat(file_path, &buff[i], 1);
        i++;
    }

    FILE *fp = fopen(file_path, "r");

    if (fp == NULL)
    {
        status_code = 404; //incorrect file path(client error)
        printf("\nFile not found");
        free(file_path);
        return;
    }

    while (fgets(buff, MAX, fp))
    {
        strcat(data, buff);
    }

    fclose(fp);
    free(file_path);

    if (data == "\0")
    { //if the server can't able to extract data(Server error)
        status_code = 500;
    }
    else
    {
        status_code = 200; //success
    }
}

char *get_status_message()
{
    switch (status_code)
    {
    case 200:
        return "200 OK\0";
    case 404:
        return "404 File not found\0";
    case 500:
        return "500 Server Error\0";
    }

    return "Invalid Code!";
}

int main()
{

    char buff[MAX];
    char data[MAX];
    char responseString[MAX];

    time_t t;
    time(&t);

    int s_sock, c_sock;
    int yes = 1, childpid;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    // Create a socket
    s_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (s_sock == -1)
    {
        perror("Socket: ");
        exit(-1);
    }
    else
        printf("Socket successfully created...\n");

    // assign IP, port
    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    if ((bind(s_sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) == -1)
    {
        perror("Bind: ");
        exit(-2);
    }
    else
        printf("Socket succesfully binded...\n");

    if ((listen(s_sock, 5)) != 0)
    {
        perror("Listen: ");
        exit(-3);
    }
    else
        printf("Server listening...\n");
    // // //

    // // Function for server-client chatting!! //
    int count = 3;
    while (count--)
    {
        c_sock = accept(s_sock, (struct sockaddr *)&clientAddr, &addr_size);
        if (c_sock < 0)
        {
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        if ((childpid = fork()) == 0)
        {
            close(s_sock);

            while (1)
            {
                memset(buff, '\0', MAX);
                memset(data, '\0', MAX);
                memset(responseString, '\0', MAX);

                if (read(c_sock, buff, MAX) == -1)
                {
                    perror("\nRead error:");
                    exit(1);
                }

                if (strncmp(buff, "GET", 3) == 0)
                {

                    printf("\n\n%s", buff);
                    getFile(buff, data);

                    snprintf(responseString, MAX, "HTTP/1.1 %s\r\nDate:%sContent-type:text\\html\r\n", get_status_message(), ctime(&t));

                    if (status_code == 200)
                    {
                        strcat(responseString, data);
                    }
                    else{
                        strcat(responseString, get_status_message());
                    }

                    send(c_sock, responseString, strlen(responseString), 0);

                    printf("\nResponse sent\n");
                }
            }
        }
    }
    // // //
    close(c_sock);
    sleep(3);
    printf("Requests Limit Reached! Exiting...\n\n");

    return 0;
}