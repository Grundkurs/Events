//
// Created by Keen on 26.01.2021.
//

#include "Logger.hpp"
#include <iostream>
#include <chrono>

Logger::Logger() {
    m_file.open("Logfile.txt", std::ofstream::trunc);
    if(!m_file.is_open()){
        std::cout << "Error in Logger::Logger: could not create Logfile.txt\n";
    }
}

Logger::~Logger() {
    m_file.close();
}


Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string &l_message) {
    const auto p1 = std::chrono::system_clock::now();

    m_file << std::chrono::duration_cast<std::chrono::milliseconds>(
            p1.time_since_epoch()).count() << ": " << l_message << "\n" << std::flush;
}
