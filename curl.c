#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "sockets/send.h"

#define BUFFER_SIZE 500


int main(int argc, char *argv[])
{
    FILE *file = fopen("./google.html", "r");
    FILE *doc = fopen("./doc.html", "a");
    char buffer[BUFFER_SIZE] = "GET /users HTTP/1.0\r\nContent-Type: text/plain\r\n\r\n";       
    struct hostent *host = gethostbyname("si-voy-mock.onrender.com");
    int sckt = socket(AF_INET, SOCK_STREAM, 0);
    char buffer_recv[BUFFER_SIZE];
    
    send_by_socket(sckt, BUFFER_SIZE, buffer, host);
    recv(sckt, buffer_recv, BUFFER_SIZE, 0);    
    
    close(sckt);
    fclose(file);
    fclose(doc);

    return 0;
}
