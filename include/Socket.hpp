//
// Created by dumitru on 16. 12. 4.
//

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <utility>
#include <memory>
#include <vector>

class Socket {
private:
    enum socket_types {CLIENT, SERVER};
    socket_types socket_type;
    int port_;
    sockaddr_in serv_addr, cli_addr;
    hostent* server;
    int sockfd;

    static const size_t timeout_ms {100};

    void create_base();

public:

    Socket(int port);
    Socket(std::string host, int port);
    Socket();
    void bind();
    void listen(int n);
    void connect();
    std::shared_ptr<Socket> accept() const;
    std::pair<size_t, std::vector<uint8_t >> recv(size_t length) const;
    std::pair<size_t, std::vector<uint8_t >> recvall(size_t length, size_t timeout = timeout_ms) const;

    ssize_t send(const std::vector<uint8_t>& msg) const;

    std::string get_remote_ip() const;
    int get_remote_port() const;
    int get_fd() const;

    void close();

    ~Socket();

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
};


