//
// Created by dumitru on 16. 12. 8.
//

#include <Socket.hpp>
#include <IOLoop.hpp>
#include <assert.h>
#include <iostream>
#include <Utils.hpp>
#include <alloca.h>


IOLoop::IOLoop(Socket &listener, IOHandler &handler) :
        clients_(MAX_CLIENTS),
        listener_(listener),
        handler_(handler) {}

void IOLoop::start() {
    fd_set readfds;
    std::vector<std::shared_ptr<Socket>> clients(5);
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(listener_.get_fd(), &readfds);
        //stdin
        FD_SET(0, &readfds);
        int max_fd = listener_.get_fd();

        for (const auto &client : clients) {
            if (client != nullptr) {
                int fd = client->get_fd();
                if (fd > 0)
                    FD_SET(fd, &readfds);
                else
                    assert(false);

                if (fd > max_fd)
                    max_fd = fd;
            }
        }

        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0)
            perror("select");
        //Listen socket bit is set, new connection
        if (FD_ISSET(listener_.get_fd(), &readfds)) {
            auto ptr = listener_.accept();

            for (auto &item : clients)
                if (item == nullptr) {
                    item = ptr;
                    break;
                }

            std::cout << "Established connection with " << ptr->get_remote_ip() << " on port "
                      << ptr->get_remote_port() << std::endl;
        }
        if (FD_ISSET(0, &readfds)) {
            handler_.onRead(0, &readfds);
        }
        //check read from clients
        for (auto &client : clients) {
            if (client == nullptr)
                continue;
            if (FD_ISSET(client->get_fd(), &readfds)) {
                handler_.onRead(client, &readfds);
            }
        }
    }

}
