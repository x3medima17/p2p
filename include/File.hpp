//
// Created by dumitru on 16. 12. 10.
//

#pragma once

/**
 * Child uses C++17 feature called FileSystem, in order to keep data close I use File class,
 * it stores filename and size.
 */
struct File {
    std::string fname_;
    size_t size_;

    /**
     * Standard file constructor
     * @param fname File name
     * @param size File size
     */
    File(std::string fname, size_t size);


    /**
     * Method that prints file data in a pretty format.
     * Mainly used for debugging.
     */
    void print() const;
};
