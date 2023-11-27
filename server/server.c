#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
        .sin_port = htons(3500)
    };

    addr.sin_addr.s_addr = INADDR_ANY;

    int bind_res = bind(sckt, (struct sockaddr*)&addr, sizeof(addr));

    if(bind_res < 0) {
        printf("Error binding socket\n");
        exit(-1);
    }

    listen(sckt, 1);

    while (1)
    {   
        struct sockaddr_in client_addr;
        socklen_t client_size = sizeof(client_addr);

        int conn_sckt = accept(sckt, (struct sockaddr*)&client_addr, &client_size);

        if(conn_sckt < 0) {
            printf("Error accepting socket connection\n");
            exit(-1);
        }

        close(conn_sckt);
        break;
    }   
    

    close(sckt);
    return 0;
}