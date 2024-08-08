#ifndef TCP_H
#define TCP_H
#include <sys/socket.h>

struct sockaddr_in create_server_address(int port);

#endif  // !TCP_H
