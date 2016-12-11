//
// Created by dumitru on 16. 12. 4.
//



/*! \mainpage KaZaA implementation
 *
 * \section intro_sec Introduction
 *
 * In the following project a p2p network has been implemented.
 * Here overall project structure is described, detailed description of each structure is present below.
 *
 *
 * \section install_sec Installation
 * First of all you need to clone project repository: https://github.com/x3medima17/p2p
 * Then you have to run cmake
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

#include <iostream>
#include <map>
#include <cassert>
#include <IOLoop.hpp>
#include <alloca.h>
#include <sstream>
#include <algorithm>

#include "Utils.hpp"
#include "File.hpp"


struct Node {
    uint32_t id_{0};
    uint16_t port_;
    std::string ip_;

    Node(uint32_t id, uint16_t port, std::string ip) :
            id_(id), port_(port), ip_(ip) {}

    Node() {}
};

class FileTable {
    struct Entry {
        size_t fsize_{0};
        std::string ip_{0};
        uint16_t port_{0};

        Entry(size_t fsize, std::string ip, uint16_t port) :
                fsize_(fsize),
                ip_(ip),
                port_(port) {}

        Entry() {}
    };

public:
    void insert(std::string fname, size_t fsize, std::string ip, uint16_t port) {
        Entry e(fsize, ip, port);

        table[fname] = e;
    }

    std::map<std::string, Entry>::const_iterator find(std::string fname) {
        return table.find(fname);
    }

    size_t size() {
        return table.size();
    }

    std::map<std::string, Entry>::const_iterator beign() {
        return table.begin();
    };

    std::map<std::string, Entry>::const_iterator end() {
        return table.end();
    };

    void print() {
        for (auto &item : table) {
            std::cout << item.first << " " << item.second.fsize_ << " " << item.second.ip_ << " ";
            std::cout << item.second.port_ << std::endl;
        }
    }

private:
    std::map<std::string, Entry> table;


};


FileTable fileTable;
std::vector<Node> SuperNodes, ChildNodes;

class SuperIOHandler : public IOHandler {
public:
    void onRead(size_t fd, fd_set *readfd) override {
//        char *buff = (char *) alloca(50);
//        int n = read(0, buff, 50);
//        std::cout << n << " --- " << std::string(buff) << std::endl;
        FD_CLR(fd, readfd);
    }

    void onRead(std::shared_ptr<Socket> &client, fd_set *readfd) override {
        auto msg = Utils::read_message(*client);
        uint32_t node_id = msg.id;
        std::string node_ip = client->get_remote_ip();

        Message::MSG_TYPES action = static_cast<Message::MSG_TYPES >(msg.msg_type);
        switch (action) {
            case Message::MSG_TYPES::CHILD_HELLO: {
                uint16_t port;
                msg.ss >> port;
                ChildNodes.emplace_back(Node(node_id, port, node_ip));
                std::cout<<"New child "<<port<<std::endl;
                Message out;
                out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::SUPER_HELLO);
                Utils::write_message(*client, out);
                break;
            }

            case Message::MSG_TYPES::SUPER_SUPER_HELLO: {
                uint16_t port;
                msg.ss >> port;
                Node curr(node_id, port, node_ip);
                SuperNodes.emplace_back(curr);
                std::cout<<"Connected supernodes: "<<SuperNodes.size()<<std::endl;
                break;
                /////////////////
                std::stringstream to_share;
                to_share << fileTable.size() << std::endl;
                for (auto it = fileTable.beign(); it != fileTable.end(); it++)
                    to_share << it->first << " " << it->second.fsize_ << " " << it->second.ip_ << " "
                             << it->second.port_ << std::endl;

                Socket s(curr.ip_, curr.port_);
                s.connect();
                Message tmp;
                tmp.msg_type = static_cast<uint16_t >(Message::MSG_TYPES::FILE_INFO_SHARE);
                tmp.set_payload(to_share.str());
                Utils::write_message(s, tmp);
                auto resp = Utils::read_message(s);
                if (resp.msg_type != static_cast<uint32_t >(Message::MSG_TYPES::FILE_INFO_SHARE_SUCCESS))
                    throw std::runtime_error("File info share error");

                break;
            }

            case Message::MSG_TYPES::FILE_INFO: {
                //Check if child is registered
                auto it = find_if(ChildNodes.begin(), ChildNodes.end(), [&node_id](const Node &obj) {
                    return obj.id_ == node_id;
                });
                if (it == ChildNodes.end()) {
                    Message out;
                    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::FILE_INFO_RECV_ERROR);
                    Utils::write_message(*client, out);
                    std::cout << "Child not registered" << std::endl;

                } else {
                    std::stringstream to_broadcast;
                    int N;
                    msg.ss >> N;
                    to_broadcast << N << std::endl;
                    for (int i = 0; i < N; i++) {
                        std::string fname;
                        size_t fsize;
                        msg.ss >> fname >> fsize;
                        fileTable.insert(fname, fsize, it->ip_, it->port_);
                        to_broadcast << fname << " " << fsize << " " << it->ip_ << " " << it->port_ << std::endl;
                    }

                    Message out;
                    out.msg_type = static_cast<uint16_t >(Message::MSG_TYPES::FILE_INFO_RECV_SUCCESS);
                    Utils::write_message(*client, out);

                    //Broadcast file info
                    std::cout<<"Broadcasting..."<<std::endl;
                    for (auto &node: SuperNodes) {
                        Socket s(node.ip_, node.port_);
                        std::cout<<"Connect to "<<node.port_<<std::endl;
                        s.connect();
                        std::cout<<"Done"<<std::endl;
                        Message tmp;
                        tmp.msg_type = static_cast<uint16_t >(Message::MSG_TYPES::FILE_INFO_SHARE);
                        tmp.set_payload(to_broadcast.str());
                        Utils::write_message(s, tmp);
                        auto resp = Utils::read_message(s);
                        if (resp.msg_type != static_cast<uint32_t >(Message::MSG_TYPES::FILE_INFO_SHARE_SUCCESS))
                            throw std::runtime_error("File info share error");

                    }
                    fileTable.print();
                }
                break;
            }

            case Message::MSG_TYPES::SEARCH_QUERY: {
                std::string fname;
                msg.ss >> fname;
                auto it = fileTable.find(fname);
                if (it == fileTable.end()) {
                    Message out;
                    out.msg_type = static_cast<uint32_t > (Message::MSG_TYPES::SEARCH_ANS_FAIL);
                    Utils::write_message(*client, out);
                    std::cout << "file " << fname << " not found" << std::endl;
                } else {
                    Message out;
                    std::stringstream payload;
                    std::string ip = it->second.ip_;
                    uint16_t port = it->second.port_;
                    payload << ip << " " << port;
                    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::SEARCH_ANS_SUCCESS);
                    out.set_payload(payload.str());
                    Utils::write_message(*client, out);

                }
                break;
            }
            case Message::MSG_TYPES::FILE_INFO_SHARE: {
                //Check if child is registered
                auto it = find_if(SuperNodes.begin(), SuperNodes.end(), [&node_id](const Node &obj) {
                    return obj.id_ == node_id;
                });
                if (it == SuperNodes.end()) {
                    Message out;
                    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::FILE_INFO_SHARE_ERROR);
                    Utils::write_message(*client, out);
                    std::cout << "Super not registered" << std::endl;

                } else {
                    int N;
                    msg.ss >> N;
                    for (int i = 0; i < N; i++) {
                        std::string fname, ip;
                        size_t fsize;
                        uint16_t port;
                        msg.ss >> fname >> fsize >> ip >> port;
                        fileTable.insert(fname, fsize, ip, port);
                    }

                    Message out;
                    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::FILE_INFO_SHARE_SUCCESS);
                    Utils::write_message(*client, out);
                    fileTable.print();

                }
                break;
            }
                // Messages not suitable for super nodes
            case Message::MSG_TYPES::SUPER_HELLO:
            case Message::MSG_TYPES::FILE_INFO_RECV_SUCCESS:
            case Message::MSG_TYPES::FILE_INFO_RECV_ERROR:
            case Message::MSG_TYPES::SEARCH_ANS_FAIL:
            case Message::MSG_TYPES::SEARCH_ANS_SUCCESS:
            case Message::MSG_TYPES::FILE_RES_SUCCESS:
            case Message::MSG_TYPES::FILE_RES_FAIL:
            case Message::MSG_TYPES::FILE_REQ:
            case Message::MSG_TYPES::FILE_INFO_SHARE_SUCCESS:
            case Message::MSG_TYPES::FILE_INFO_SHARE_ERROR:
                break;

        }

//        Utils::write_message(*client, msg);
        FD_CLR(client->get_fd(), readfd);
        client = nullptr;
    }
};


int main(int argc, char **argv) {
    auto M = Utils::parse_cmd_args(argc, argv);

    if (M.find("p") == M.end())
        throw std::runtime_error("No port supplied");

    if (M.find("s_ip") != M.end() && M.find("s_port") != M.end()) {
        std::string s_ip = M.find("s_ip")->second;
        uint16_t s_port = std::stoi(M.find("s_port")->second);
        //Register node (ask)
        Socket s(s_ip, s_port);
        s.connect();
        Message out;
        out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::SUPER_SUPER_HELLO);
        out.set_payload(M.find("p")->second);
        Utils::write_message(s, out);
        SuperNodes.emplace_back(Node(0, s_port, s_ip));

    } else
        std::cout << "NO NODES" << std::endl;

    int port = std::stoi(M.find("p")->second);
    std::cout << port << std::endl;
    Socket server(port);
    server.bind();
    server.listen(5);

    //IOLoop
    SuperIOHandler handler;
    IOLoop loop(server, handler);
    loop.start();
}