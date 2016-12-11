//
// Created by dumitru on 16. 12. 8.
//

#pragma once

#include <Socket.hpp>
#include "IOHandler.hpp"

class IOLoop {
    size_t MAX_CLIENTS {20};
    std::vector<std::shared_ptr<Socket>> clients_;
    Socket& listener_;
    IOHandler& handler_;

public:
    IOLoop() = delete;
    IOLoop(Socket&, IOHandler&);
    void start();
};
