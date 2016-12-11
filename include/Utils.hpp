//
// Created by dumitru on 16. 12. 6.
//

#pragma once

#include <map>
#include "Message.hpp"
#include "Socket.hpp"

/**
 * Utility namespace that contains all necessary function and constants
 */
namespace Utils {
    /**
     * Header size of message
     */
    const size_t HEADER_SIZE{12};

    /**
     * Method that transforms a byte array to 4 byte integer
     * @param it Vectors iterator
     * @return unsigned int value
     */
    uint32_t uint32_from_vec(std::vector<uint8_t>::const_iterator it);

    /**
     * Same as previous but does exactly the oposite action
     * @param val unsiged int
     * @return vector of bytes
     */
    std::vector<uint8_t> vec_from_uint32(uint32_t val);

    /**
     * Most used function in the app, it reads a Message from the socket
     * @param sock Constant socket reference
     * @param timeout Timeout of reading (required in the task), it has a default value
     * @return It return a Message instance
     */
    Message read_message(const Socket &sock, size_t timeout = 5000);

    /**
     * This method writes a Message into Socket
     * @param sock Constant Socket reference
     * @param msg
     */
    void write_message(const Socket &sock,Message &msg);

    /**
     * This function is invoken in Child and Super it parses command line
     * @param argc Number of arguments
     * @param argv Pointer to *char (arguments)
     * @return Returns a map of string(argument) -> string(value)
     */
    std::map<std::string, std::string> parse_cmd_args(int argc, char** argv);

}