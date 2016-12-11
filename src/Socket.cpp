//
// Created by dumitru on 16. 12. 4.
//

#include "Socket.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <fcntl.h>

#include <cassert>
#include <vector>
#include <memory>
#include <thread>

//void error(std::string msg) {
//    std::cout << (msg) << '\n';
//    exit(1);
//}

void error(const char *msg) {
    perror(msg);
    exit(0);
}


void Socket::create_base() {
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);


//    this->port = port;

    if (this->sockfd < 0)
        throw std::runtime_error("ERROR opening socket");
}

Socket::Socket(int port) {
    this->port_ = port;
    this->socket_type = Socket::SERVER;
    this->create_base();
    bzero((char *) &(this->serv_addr), sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = INADDR_ANY;
    this->serv_addr.sin_port = htons(this->port_);
}

Socket::Socket() {
    this->socket_type = Socket::CLIENT;
}

Socket::Socket(std::string host, int port) {
    this->port_ = port;
    this->socket_type = Socket::CLIENT;
    this->create_base();


    this->server = gethostbyname((char *) host.c_str());
    if (this->server == NULL)
        throw std::runtime_error("ERROR, no such host");

    bzero((char *) &(this->serv_addr), sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    bcopy((char *) (this->server->h_addr),
          (char *) &(this->serv_addr.sin_addr.s_addr),
          this->server->h_length);
    this->serv_addr.sin_port = htons(port);

}


void Socket::bind() {
    if (this->socket_type != Socket::SERVER)
        throw std::runtime_error("Only server can invoke bind()");

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");

    if (::bind(this->sockfd, (struct sockaddr *) &(this->serv_addr),
               sizeof(this->serv_addr)) < 0)
        throw std::runtime_error("ERROR on binding");
}


void Socket::listen(int n) {
    if (this->socket_type != Socket::SERVER)
        throw std::runtime_error("Only server can invoke listen()");
    ::listen(this->sockfd, n);
}

void Socket::connect() {
    if (this->socket_type != Socket::CLIENT)
        throw std::runtime_error("Only client can invoke connect()");

    if (::connect(this->sockfd, (struct sockaddr *) &(this->serv_addr), sizeof(this->serv_addr)) < 0)
//        throw std::runtime_error("ERROR connecting");
        error("ERROR connecting");
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);

}

std::shared_ptr<Socket> Socket::accept() const {

    if (this->socket_type != Socket::SERVER)
        throw std::runtime_error("Only server can invoke accept()");

    std::shared_ptr<Socket> client_socket(new Socket);

    socklen_t clilen;
    clilen = sizeof(this->cli_addr);

    client_socket->sockfd = ::accept(this->sockfd,
                                     (struct sockaddr *) &(this->cli_addr),
                                     &clilen);
    client_socket->cli_addr = this->cli_addr;

    if (client_socket->sockfd < 0)
        throw std::runtime_error("ERROR on accept");

    return client_socket;

}

std::pair<size_t, std::vector<uint8_t >> Socket::recvall(size_t length, size_t timeout) const {
    assert(length > 0);
    size_t done = 0;
    size_t remaining = length;
    std::vector<uint8_t> buff;

    size_t tmp = timeout;
    size_t wait_ms = 10;
    while (done != length && timeout > 0) {
        auto curr = recv(remaining);
        remaining -= curr.first;
        done += curr.first;
        assert(done + remaining == length);
        buff.insert(buff.end(), curr.second.begin(), curr.second.end());
//        std::cout<<timeout<<" "<<curr.first<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
        timeout -= wait_ms;
    }

    if (timeout <= 0)
    {

        std::cout << tmp << std::endl;
        throw std::runtime_error("Recvall timed out");
    }

    if (done != length)
        throw std::runtime_error("Broken message");

    assert(done == length);
    assert(remaining == 0);
    return std::make_pair(done, buff);
}

std::pair<size_t, std::vector<uint8_t >> Socket::recv(size_t length) const {
    assert(length > 0);

    std::vector<uint8_t> buff(length);
    ssize_t n = ::recv(this->sockfd, buff.data(), length, 0);

    //Non-blocking
    //TODO: handle connection close
    if (n < 0) {
//        throw std::runtime_error("ERROR reading from socket");
        n = 0;
    }

    return std::make_pair(n, std::vector<uint8_t>(buff.begin(), buff.begin() + n));

}

ssize_t Socket::send(const std::vector<uint8_t> &msg) const {
    if (msg.size() == 0)
        return 0;
    auto ptr = &(msg.at(0));
    uint8_t *const buffer = const_cast<uint8_t *>(ptr);

    ssize_t n = ::write(this->sockfd, buffer, msg.size());
    if (n < 0) {
        throw std::runtime_error("ERROR writing to socket");
    }
    return n;
}

std::string Socket::get_remote_ip() const {

    struct sockaddr_in *pV4Addr = (struct sockaddr_in *) &cli_addr;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
    return std::string(str);
}

int Socket::get_remote_port() const {
    int port_c = (int) ntohs(cli_addr.sin_port);
    return port_c;
}

int Socket::get_fd() const { return sockfd; }

void Socket::close() {
    std::cout << "Socket closed" << std::endl;
    ::close(this->sockfd);
}

Socket::~Socket() {
    this->close();
}
