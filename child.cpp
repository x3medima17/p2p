//
// Created by dumitru on 16. 12. 4.
//

#include <iostream>
#include <experimental/filesystem>
#include <Socket.hpp>
#include <IOHandler.hpp>
#include <alloca.h>
#include <fstream>
#include <iterator>
#include <IOLoop.hpp>
#include <stdlib.h>
#include <malloc.h>

#include "Message.hpp"
#include "Utils.hpp"
#include "File.hpp"

namespace fs = std::experimental::filesystem;
using std::cout;
using std::endl;


uint32_t set_random_id()
{
    int x;
    int *p = &x;

    uint32_t  a = reinterpret_cast<uint64_t >( p );
    return a;
}

uint16_t S_PORT, PORT;
std::string S_IP;
const uint32_t ID = set_random_id();

auto scan() {
    Message msg;
    std::vector<File> V;
    for (auto &file : fs::directory_iterator("data")) {
        std::string fname = file.path();
        size_t pos = fname.length() - 1;
        while (fname.at(--pos) != '/' && pos > 0);
        fname = fname.substr(pos + 1);

        V.emplace_back(File{fname, fs::file_size(file)});
    }
    return V;
}

/**
 * This class extends IOHandler and implements its onRead functions
 * There are two `onRead` functions, one for stdin, another for sockets
 */
class ChildIOHandler : public IOHandler {
public:
    /**
     * This method is invoked when a certain data is available in stdin.
     * Using iostreams it reads three arguments: command (get), arg1 (input file), arg2 (output file)\n
     * If data is not valid it will tell that
     * @param fd File descriptor, it is 0 for stdin
     * @param readfd File descriptor set, that is used for `select()`
     */
    void onRead(size_t fd, fd_set *readfd) override {

        std::string cmd{""}, arg1{""}, arg2{""};
        std::cin >> cmd >> arg1 >> arg2;
        if (cmd != "get" || arg1.empty() || arg2.empty())
            cout << "Wrong argument" << std::endl;
        else {
            Message out;
            out.msg_type = static_cast<uint32_t>(Message::MSG_TYPES::SEARCH_QUERY);
            out.id = ID;
            out.set_payload(arg1);
            Socket s(S_IP, S_PORT);
            s.connect();
            Utils::write_message(s, out);
            auto resp = Utils::read_message(s);
            if (resp.msg_type == static_cast<uint32_t >(Message::MSG_TYPES::SEARCH_ANS_FAIL))
                std::cout << "File not found" << std::endl;
            else {
                uint16_t port;
                std::string ip;
                resp.ss >> ip >> port;
                std::cout << "File found here: " << ip << " " << port << std::endl;
                if (port == PORT)
                    std::cout << "This is local file" << std::endl;
                else {
                    out = Message();
                    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::FILE_REQ);
                    out.set_payload(arg1);
                    Socket s_req(ip, port);
                    s_req.connect();
                    Utils::write_message(s_req, out);
                    resp = Utils::read_message(s_req, 100000);

                    std::ofstream fout("download/" + arg2, std::ios::binary);
                    char *ptr = (char *) (&resp.payload[0]);
                    fout.write(ptr, resp.payload_length);
                }
            }
        }
        FD_CLR(fd, readfd);
    }

    /**
     * This method is invoked if there is something to read from a socket \n
     * A message is read using Utils namespace, then based on that message type a certain action will take place.
     * @param client A reference to shared poiter to client
     * @param readfd File descriptor set, that is used for `select()`
     */
    void onRead(std::shared_ptr<Socket> &client, fd_set *readfd) override {
        auto msg = Utils::read_message(*client);
        uint32_t node_id = ID;
        std::string node_ip = client->get_remote_ip();

        Message::MSG_TYPES action = static_cast<Message::MSG_TYPES >(msg.msg_type);
        switch (action) {

            case Message::MSG_TYPES::SUPER_HELLO:
            case Message::MSG_TYPES::FILE_INFO_RECV_SUCCESS:
            case Message::MSG_TYPES::FILE_INFO_RECV_ERROR:
            case Message::MSG_TYPES::SEARCH_ANS_FAIL:
            case Message::MSG_TYPES::SEARCH_ANS_SUCCESS:
            case Message::MSG_TYPES::FILE_RES_SUCCESS:
            case Message::MSG_TYPES::FILE_RES_FAIL:
            case Message::MSG_TYPES::FILE_INFO_SHARE_SUCCESS:
            case Message::MSG_TYPES::FILE_INFO_SHARE_ERROR:

                break;
            case Message::MSG_TYPES::FILE_REQ: {
                std::string fname;

                msg.ss >> fname;
                std::ifstream fin("data/" + fname, std::ios::binary);
                if (!fin.is_open()) {
                    Message out;
                    out.msg_type = static_cast<uint16_t >(Message::MSG_TYPES::FILE_RES_FAIL);
                    Utils::write_message(*client, out);
                } else {

                    //Optimized write
//                    fs::path p = fs::current_path() / "example.bin";
                    uint32_t fsize = fs::file_size("data/" + fname);
                    Message out;
                    out.msg_type = static_cast<uint16_t >(Message::MSG_TYPES::FILE_RES_SUCCESS);
//                    out.payload.resize(fsize);
                    char *buff = (char *) malloc(fsize);

                    uint32_t payload_size = fsize;
                    std::vector<uint8_t> header;

                    //OUT
                    uint32_t total_length = htonl(Utils::HEADER_SIZE + fsize);
                    uint32_t id = ID;
                    auto tmp = Utils::vec_from_uint32(total_length);
                    header.insert(header.end(), tmp.begin(), tmp.end());

                    tmp = Utils::vec_from_uint32(id);
                    header.insert(header.end(), tmp.begin(), tmp.end());

                    tmp = Utils::vec_from_uint32(out.msg_type);
                    header.insert(header.end(), tmp.begin(), tmp.end());

                    client->send(header);

                    fin.read(buff, fsize);
                    out.payload.insert(out.payload.begin(), buff, buff + fsize);
                    free(buff);
                    client->send(out.payload);
                }
            }
                // Messages not suitable for child nodes
            case Message::MSG_TYPES::CHILD_HELLO:
            case Message::MSG_TYPES::SUPER_SUPER_HELLO:
            case Message::MSG_TYPES::FILE_INFO:
            case Message::MSG_TYPES::SEARCH_QUERY:
            case Message::MSG_TYPES::FILE_INFO_SHARE:
                break;

        }

        FD_CLR(client->get_fd(), readfd);
        client = nullptr;
    }
};

int main(int argc, char **argv) {
    auto M = Utils::parse_cmd_args(argc, argv);

    if (M.find("p") == M.end())
        throw std::runtime_error("No port supplied");

    if (M.find("s_ip") == M.end())
        throw std::runtime_error("No supernode ip supplied");

    if (M.find("s_port") == M.end())
        throw std::runtime_error("No supernode port supplied");

    PORT = std::stoi(M.find("p")->second);
    S_PORT = std::stoi(M.find("s_port")->second);
    S_IP = M.find("s_ip")->second;

    Socket s(S_IP, S_PORT);
    s.connect();

    //Hello
    Message out;
    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::CHILD_HELLO);
    out.id = ID;
    out.set_payload(std::to_string(PORT));

    Utils::write_message(s, out);
    auto resp = Utils::read_message(s);
    resp.print();

    //File info
    std::stringstream ss;
    std::vector<File> Files = scan();
    ss << Files.size() << std::endl;
    for (const auto &file : Files) {
        file.print();
        ss << file.fname_ << " " << file.size_ << std::endl;
    }
    std::cout << ss.str() << std::endl;

    Socket s2(S_IP, S_PORT);
    s2.connect();
    out = Message();
    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::FILE_INFO);
    out.id = ID;
    out.set_payload(ss.str());
    Utils::write_message(s2, out);
    resp = Utils::read_message(s2);
    resp.print();


    //IOLoop
    Socket listener(PORT);
    listener.bind();
    listener.listen(50);
    ChildIOHandler handler;
    IOLoop loop(listener, handler);
    loop.start();

    return 0;
    //Query
    Socket s3(S_IP, S_PORT);
    s3.connect();

    out = Message();
    out.msg_type = static_cast<uint32_t >(Message::MSG_TYPES::SEARCH_QUERY);
    out.set_payload("1.txt");
    Utils::write_message(s3, out);
    resp = Utils::read_message(s3);
    resp.print();

    return 0;

}