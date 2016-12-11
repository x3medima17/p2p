//
// Created by dumitru on 16. 12. 8.
//

#pragma once


#include "Socket.hpp"

class IOHandler {
public:
    //Stdin
    virtual void onRead(size_t fd, fd_set* readfd);

    //Socket
    virtual void onRead(std::shared_ptr<Socket>& client, fd_set* readfd);

};

