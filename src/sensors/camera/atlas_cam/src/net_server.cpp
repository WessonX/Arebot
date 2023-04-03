#include "atlas_cam/net_server.h"

int Server::Start() {
    // create socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cerr << "socket create fail" << std::endl;
        return -1;
    }

    // bind
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port=htons(7004);
    if (bind(listen_fd, (sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "bind failed" << std::endl;
        return -1;
    }

    // listen
    if (listen(listen_fd, 10) == -1) {
        std::cerr << "listen fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // accept
    int len = sizeof(sockaddr_in);
    sockaddr_in client_addr;
    client_fd = accept(listen_fd, (sockaddr *)&client_addr, (socklen_t *)&len);
    if (client_fd == -1) {
        std::cerr << "accept fail" << std::endl;
        return -1;
    }
    else {
        std::cerr << inet_ntoa(client_addr.sin_addr) << " has connected" << std::endl;
    }

    return 0;
}

int Server::Close() {
    close(listen_fd);
    close(client_fd);

    return 0;
}

int Server::Response(std::string status) {
    assert(status.size() <= 1023);
    char msg[1024];
    memset(msg, 0, sizeof(msg));
    strcpy(msg, status.c_str());

    // response to client
    strcpy(msg, "success");
    if (send(client_fd, msg, sizeof(msg), 0) == -1) {
        return -1;
    }

    return 0;
}


int Server::GetSize() {
    char msg[1024];
    memset(msg, 0, sizeof(msg));

    // wait for size msg
    if (recv(client_fd, msg, sizeof(msg), 0) == -1) {
        std::cerr << "received size failed" << std::endl;
        return -1;
    }

    // response to client
    if (Response("success") == -1) {
        std::cout << "response failed after received size" << std::endl;
        return -1;
    }

    return strtol(msg, nullptr, 10);
}

int Server::Receive(unsigned char *buf, int size) {
    // receive data
    while (size > 0) {
        int recv_size = recv(client_fd, buf, size, 0);
        if (recv_size == -1) {
            std::cerr << "received data failed" << std::endl;
            return -1;
        }
        size -= recv_size;
        buf += recv_size;

        // int recv_size = std::min<int>(1024, size - cnt);
        // if (recv(client_fd, buf + cnt, recv_size, 0) == -1) {
        //     std::cerr << "received data failed" << std::endl;
        //     return -1;
        // }
        // cnt += recv_size;
    }

    // response to client
    if (Response("success") == -1) {
        std::cout << "response failed after received data" << std::endl;
        return -1;
    }

    return 0;
}
