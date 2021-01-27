//
// Created by Keen on 26.01.2021.
//

#ifndef EVENTS_LOGGER_HPP
#define EVENTS_LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
public:
    static Logger& get_instance();
    void log(const std::string& l_message);
private:
    Logger();
    ~Logger();
    std::ofstream       m_file; // output filestream
};


#endif //EVENTS_LOGGER_HPP
