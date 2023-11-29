#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_CON 5

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Not enough arguments provided\n");
        exit(-1);
    }

    int sckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(sckt == -1) {
        printf("Error creating socket\n");
        exit(-1);
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(atoi(argv[1]))
    };

    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int bind_res = bind(sckt, (struct sockaddr*)&addr, sizeof(addr));

    if(bind_res < 0) {
        printf("Error binding socket\n");
        exit(-1);
    }

    listen(sckt, MAX_CON);

    char *message = "HTTP/1.0\r\nContent-Type: text/html\r\n\r\n<p>Este mensaje es un <b>mensaje en vano</b></p>\0";
    char sckt_msg[5];

    while (1)
    {   
        struct sockaddr_in client_addr;
        socklen_t client_size = sizeof(client_addr);
        memset(&client_addr, 0, client_size);

        int conn_sckt = accept(sckt, (struct sockaddr*)&client_addr, &client_size);

        if(conn_sckt < 0) {
            printf("Error accepting socket connection\n");
            exit(-1);
        }

        char clntName[INET_ADDRSTRLEN];

        if(inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL) {
            printf("Handling client %s/%d\n", clntName, ntohs(client_addr.sin_port));
        }

        int send_status = send(conn_sckt, message, strlen(message), 0);

        if(send_status < 0) {
            fputs("Error sending socket info.", stderr);
        }

        close(conn_sckt);
    }   
    

    close(sckt);
    return 0;
}