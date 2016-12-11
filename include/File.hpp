//
// Created by dumitru on 16. 12. 10.
//

#pragma once


struct File {
    std::string fname_;
    size_t size_;

    File(std::string fname, size_t size);

    void print() const;
};
