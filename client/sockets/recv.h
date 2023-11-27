#ifndef RECV_H_
#define RECV_H_

void recv_with_socket(int sckt, char *buffer, void(*f)(char*));

#endif