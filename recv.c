#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sockets/recv.h"

// We must think of the possibility of receiving data in chunks
// Using tcp with C sockets that might be a little bit difficult
// to get right
void recv_with_socket(int sckt, char *buffer, void (*f)(char*)) {
    int bytes_read;
    int full_bytes = 0;
    char *full_buffer = malloc(sizeof(buffer));

    while ( (bytes_read = recv(sckt, buffer, sizeof(buffer), 0)) != -1 )
    {   
        full_bytes += bytes_read;
        // memcpy sobreescribe los datos, por lo que memmove debe ser usado luego
        memcpy(full_buffer, buffer, bytes_read);
    }
    
    printf("BUFFER %s\r\n", full_buffer);
}