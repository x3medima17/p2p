//
// Created by dumitru on 16. 12. 6.
//

#include <iostream>
#include "Message.hpp"

void Message::print() const {
    std::cout<<"Length: "<<total_length<<'\n';
    std::cout<<"ID: "<<id<<'\n';
    std::cout<<"Type: "<<msg_type<<'\n';
    std::cout<<"Payload length: "<<payload_length<<std::endl;
    for(auto& byte:payload){
//        std::cout<<std::hex<<(int)byte<<' ';
        std::cout<<(char)byte;
    }
    std::cout<<std::endl;
    std::cout<<std::dec;
}

void Message::set_payload(std::string s) {
    payload = std::vector<uint8_t >(s.begin(), s.end());
}
