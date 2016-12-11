//
// Created by dumitru on 16. 12. 8.
//


#include "Utils.hpp"

namespace Utils {

    uint32_t uint32_from_vec(std::vector<uint8_t>::const_iterator it) {
        uint32_t res = *(it+3) | (*(it + 2) << 8) | (*(it + 1) << 16) | (*(it + 0) << 24);
        return res;
    }

    uint16_t uint16_from_vec(std::vector<uint8_t>::const_iterator it) {
        uint16_t res = *it | (*(it + 1) << 8);
        return res;
    }

    std::vector<uint8_t> vec_from_uint32(uint32_t value) {
        std::vector<uint8_t> buffer(4);
        buffer[0] = (value >> 24) & 0xFF;
        buffer[1] = (value >> 16) & 0xFF;
        buffer[2] = (value >> 8) & 0xFF;
        buffer[3] = value & 0xFF;
        return buffer;
    }

    Message read_message(const Socket &sock) {
        Message msg;
        auto tmp = sock.recvall(HEADER_SIZE);
        auto header = tmp.second;
        msg.total_length = ntohl(uint32_from_vec(header.begin()));
        msg.id = ntohl(uint32_from_vec(header.begin() + 4));
        msg.msg_type = ntohl(uint32_from_vec(header.begin() + 8));
        msg.payload_length = msg.total_length - HEADER_SIZE;
        if(msg.payload_length > 0)
        {
            tmp = sock.recvall(msg.payload_length, 1000000);
            msg.payload = tmp.second;
        }

        std::string raw(msg.payload.begin(), msg.payload.end());
        msg.ss.str(raw);

        return msg;
    }

    void write_message(const Socket &sock, Message &msg) {
        std::vector<uint8_t> buff;

        msg.payload_length = msg.payload.size();
        msg.total_length = HEADER_SIZE + msg.payload_length;

        uint32_t total_length = htonl(msg.total_length);
        uint32_t id = htonl(msg.id);
        uint32_t msg_type = htonl(msg.msg_type);

        auto tmp = vec_from_uint32(total_length);
        buff.insert(buff.end(), tmp.begin(), tmp.end());

        tmp = vec_from_uint32(id);
        buff.insert(buff.end(), tmp.begin(), tmp.end());

        tmp = vec_from_uint32(msg_type);
        buff.insert(buff.end(), tmp.begin(), tmp.end());

        buff.insert(buff.end(), msg.payload.begin(), msg.payload.end());
        sock.send(buff);
    }


    std::map<std::string, std::string> parse_cmd_args(int argc, char **argv) {
        if (argc % 2 == 0)
            throw std::runtime_error("Wrong number of arguments");
        std::map<std::string, std::string> M;
        for (int i = 1; i < argc; i += 2) {
            auto key = std::string(argv[i]);
            if(key.substr(0,2) == "--")
                key.erase(0,2);
            else if(key.substr(0,1) == "-")
                key.erase(0,1);
            else
                throw std::runtime_error("Wrong format");
            auto val = std::string(argv[i + 1]);
            M.emplace(key, val);

        }
        return M;
    }

}