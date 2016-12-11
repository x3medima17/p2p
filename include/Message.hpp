//
// Created by dumitru on 16. 12. 6.
//

#pragma once

#include <cstdint>
#include <vector>
#include <sstream>
/**
 * This is one the main classes in the application.
 * All data exchange on the network is done through Messages. \n
 * It has a header and a payload. Header is 12 bytes and payload has variable length.
 * All payload is sent in a raw format and then read as string streams, the only exceptions are
 * files that are being transmitted.
 */
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

    /**
     * Because payload is vector of bytes, it cannot be assigned by a string,
     * method set_payload takes a string and copies it byte by byte.
     * @param s payload as a string
     */
    void set_payload(std::string s);

    /**
     * Method that prints message in a pretty format.
     * Mainly used for debugging.
     */
    void print() const;

};
