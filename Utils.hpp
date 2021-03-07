//
// Created by Keen on 28.01.2021.
//

#ifndef EVENTS_UTILS_HPP
#define EVENTS_UTILS_HPP

#include <string>

namespace Utils{
    std::string get_source_dir();
    void retrieve_quoted_text(std::stringstream& l_ss, std::string& l_text);
}


#endif //EVENTS_UTILS_HPP
