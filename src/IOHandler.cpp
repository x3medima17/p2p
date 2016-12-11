//
// Created by dumitru on 16. 12. 8.
//

#include <alloca.h>
#include <iostream>
#include "IOHandler.hpp"


//Stdin
void IOHandler::onRead(size_t fd, fd_set *readfd) {
    FD_CLR(fd, readfd);
}

//Socket
void IOHandler::onRead(std::shared_ptr <Socket> &client, fd_set *readfd) {
    FD_CLR(client->get_fd(), readfd);
    client = nullptr;
}
