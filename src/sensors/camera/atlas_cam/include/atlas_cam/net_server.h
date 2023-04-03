#ifndef ASCENDDK_ASCENDCAMERA_NET_SERVER_H_
#define ASCENDDK_ASCENDCAMERA_NET_SERVER_H_

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <assert.h>

class Server {
public:
    int listen_fd;
    int client_fd;

public:
    int Start();

    int Close();

    int Response(std::string status);

    int GetSize();

    int Receive(unsigned char *buf, int size);
};


#endif /* ASCENDDK_ASCENDCAMERA_NET_SERVER_H_ */