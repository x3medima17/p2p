//
// Created by dumitru on 16. 12. 8.
//

#pragma once

#include <Socket.hpp>
#include "IOHandler.hpp"

/**
 * Class that does all server's job, it listens for incoming data using `select()` and invokes the right functions.
 */
class IOLoop {
    size_t MAX_CLIENTS {20};
    std::vector<std::shared_ptr<Socket>> clients_;
    Socket& listener_;
    IOHandler& handler_;

public:
    /*
     * IOLoop must have socket and IOHandler refference, so standard constructor is not allowed
     */
    IOLoop() = delete;
    /**
     * IOLoop constructor, takes Socket and IOHandler refference.
     */
    IOLoop(Socket&, IOHandler&);

    /*
     * A blocking function that will run an infinite loop, waiting for data.
     */
    void start();
};
