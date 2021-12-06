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

#define FTP_CONNECTION_PORT 2021 // 21 not working in my system, so 2021
#define BUFSIZE 1024

void writeToFile(char file_name[], char contents[]){
    FILE *fptr;
    char file_path[150];

    sprintf(file_path, "./downloads/%s", file_name);

    fptr = fopen(file_path, "w");

    if (fptr == NULL) {
        printf("Write Error!");
        fclose(fptr);
        return;
    }

    fprintf(fptr, "%s", contents);
    fclose(fptr);
}

void make_connection(int *c_sock, int OUR_PORT)
{
    struct sockaddr_in serverAddr;

    // Create a socket
    *c_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*c_sock < -1)
    {
        perror("Socket Error: ");
        exit(-1);
    }

    // assign IP, port
    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(OUR_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(*c_sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Connect Error: ");
        exit(1);
    }
    else
        printf("\nConnected to the server...\n");
}

int main()
{
    int c_sock, data_c_sock;
    char filename[100];
    char buffer[BUFSIZE];
    char rec_buffer[BUFSIZE];

    // ESTABLISH CONTROL CONNECTION //
    make_connection(&c_sock, FTP_CONNECTION_PORT);
    printf("CONTROL CONNECTION\n\n");

    // Send filename to fetch
    printf("Enter the filename: ");
    scanf("%s", filename);
    send(c_sock, filename, strlen(filename), 0);

    // RECEIVE THE PORT OF DATA CONNECTION / ERROR MSG
    memset(buffer, '\0', BUFSIZE);
    if (recv(c_sock, buffer, BUFSIZE, 0) < 0)
    {
        printf("Error in receiving data.\n");
    }
    else
    {
        printf("\nServer: %s\n\n", buffer);
    }

    if (strncmp(buffer, "ERROR=404", 9) != 0)
    {
        // CONNECT TO THE DATA PORT
        char *DATA_PORT_STRING = strtok(buffer, "=");
        DATA_PORT_STRING = strtok(NULL, "=");
        int DATA_PORT = atoi(DATA_PORT_STRING);

        make_connection(&data_c_sock, DATA_PORT);
        printf("DATA CONNECTION\n\n");

        // Send filename to fetch
        send(data_c_sock, filename, strlen(filename), 0);

        // Fetch file contents!
        memset(rec_buffer, 0, BUFSIZE);
        if (recv(data_c_sock, rec_buffer, BUFSIZE, 0) < 0)
        {
            printf("Error in receiving data.\n");
        }
        else
        {
            // printf("\nServer: \n%s\n\n", rec_buffer);
            printf("Enter the name of the file: ");
            scanf("%s", filename);
            writeToFile(filename, rec_buffer);
        }

        // CLOSE THE DATA CONNECTION
        memset(buffer, '\0', BUFSIZE);
        sprintf(buffer, "exit");
        send(data_c_sock, buffer, strlen(buffer), 0);

        close(data_c_sock);
        printf("\nDisconnected from server (DATA CONTROL).\n\n");
    }

    // CLOSE THE CONTROL CONNECTION
    memset(buffer, '\0', BUFSIZE);
    sprintf(buffer, "exit");
    send(c_sock, buffer, strlen(buffer), 0);

    close(c_sock);
    printf("Disconnected from server (CONTROL CONNECTION).\n\n");

    return 0;
}
