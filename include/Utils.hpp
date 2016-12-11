//
// Created by dumitru on 16. 12. 6.
//

#pragma once

#include <map>
#include "Message.hpp"
#include "Socket.hpp"

namespace Utils {
    const size_t HEADER_SIZE{12};

    uint32_t uint32_from_vec(std::vector<uint8_t>::const_iterator it);
    uint16_t uint16_from_vec(std::vector<uint8_t>::const_iterator it);

    std::vector<uint8_t> vec_from_uint32(uint32_t val);

    Message read_message(const Socket &sock, size_t timeout = 5000);

    void write_message(const Socket &sock,Message &msg);

    std::map<std::string, std::string> parse_cmd_args(int argc, char** argv);

}