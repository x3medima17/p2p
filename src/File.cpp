//
// Created by dumitru on 16. 12. 10.
//

#include <iostream>

#include "File.hpp"

File::File(std::string fname, size_t size) :
        fname_(fname),
        size_(size) {}

void File::print() const {
    std::cout << fname_ << " " << size_ << std::endl;
}
