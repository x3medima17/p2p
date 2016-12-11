//
// Created by dumitru on 16. 12. 6.
//

#pragma once

#include <cstdint>
#include <vector>
#include <sstream>

struct Message {

    /**
     * Enum designed to work safely with Message types
     * No raw flags are used, only encapsulated enum
     */
    enum class MSG_TYPES : std::uint32_t {
        CHILD_HELLO = 0x10,
        SUPER_HELLO = 0x11,
        SUPER_SUPER_HELLO = 0x12,

        FILE_INFO = 0x20,
        FILE_INFO_RECV_SUCCESS = 0x21,
        FILE_INFO_RECV_ERROR = 0x22,

        SEARCH_QUERY = 0x30,
        SEARCH_ANS_SUCCESS = 0x31,
        SEARCH_ANS_FAIL = 0x32,

        FILE_REQ = 0x40,
        FILE_RES_SUCCESS = 0x41,
        FILE_RES_FAIL = 0x42,

        FILE_INFO_SHARE = 0x50,
        FILE_INFO_SHARE_SUCCESS = 0x51,
        FILE_INFO_SHARE_ERROR = 0x52
    };

    uint32_t total_length{0};
    uint32_t payload_length{0};
    uint32_t id{0};
    uint32_t msg_type{0};
    std::vector<uint8_t> payload;
    std::stringstream ss;

    void set_payload(std::string s);

    void print() const;

};
